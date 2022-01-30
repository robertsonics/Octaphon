// **************************************************************************
//     Filename: Mixer.h
// Date Created: 1/23/2022
//
// This module is part of the Robertsonics Octaphon project
//
// COPYRIGHT (c) 2022 Robertsonics
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// **************************************************************************

#pragma once

#include <JuceHeader.h>
#include "/usr/include/alsa/asoundlib.h"
#include "VoiceManager.h"
#include "PitchBend.h"


// We need an 8 channel mix buffer, with each buffer being 1/4 the size in samples
//  of the alsa output buffer
#define MIX_BUFFER_SAMPLES     ((ALSA_PERIOD_FRAMES * 2) / 4)

// We also need a final hardware output buffer to hold the actual 16-bit audio output
//  for the alsa driver.

#define HW_BUFFER_SAMPLES      (ALSA_PERIOD_FRAMES * 2)

typedef struct {
    float frameMsAve;
    float frameMsMax;
    int underruns;
} MIXER_STATS_STRUCTURE;

#define PITCH_UP_MAX    32657
#define PITCH_DN_MAX    21796


// **************************************************************************
class Rmixer : public Thread,
               public ChangeBroadcaster
{

public:
	Rmixer() : Thread ("Rogue Mixer Thread") {
		m_changePendingFlag = false;
		syncModeEnabled = true;
		statsEnabledFlag = false;
		statsRequestFlag = false;
		resetStatsFlag = false;
		dspFrameMsMax = 0.0f;
		dspFrameMsAve = 0.0f;
		dspUnderruns = 0;
	}
	~Rmixer();
	void setVoiceManager(VoiceManager * vm)         { voiceManager = vm; }
	bool startAudio(String sndDevName);
	void stopAudio();
	void setPitchBend(int pb);
	void run();

	void setStatsEnabled(bool newState)             { statsEnabledFlag = newState; }
	void requestStats(void)                         { statsRequestFlag = true; }
	void getStats(MIXER_STATS_STRUCTURE * stats);
	void resetStats(void)                           { resetStatsFlag = true; }
	bool getChangePending()						    { return m_changePendingFlag; }
	void clearChangePending()					    { m_changePendingFlag = false; }

private:

    snd_pcm_t * m_sndDeviceOut;
    snd_pcm_uframes_t m_numframes;
    int m_numsamples;

    uint32_t m_sampleIncrement;

    bool syncModeEnabled;
    int m_qId;

	bool m_changePendingFlag;
    Time *time;
    bool statsEnabledFlag;
    bool statsRequestFlag;
    bool resetStatsFlag;
	float dspFrameMsMax;
	float dspFrameMsAve;
	int dspUnderruns;

    std::unique_ptr<PitchBend> pitchBend;
    //std::unique_ptr<Rverb> rverb;

    // Our voice manager
    VoiceManager * voiceManager;

    // Voice mixing and is done in a non-interleaved stereo juce AudioBuffer. This
    //  buffer needs to be large enough to handle at least 2X the nominal number of
    //  frames to account for pitch bending up to 1 octave.
    juce::AudioBuffer<float> mixBuffer {8, (MIX_BUFFER_SAMPLES * 2)};

    // The sample rate conversion results in a nominal buffer ready for any dsp
    //  to be applied to the main stereo output
    juce::AudioBuffer<float> mainsBuffer {8, MIX_BUFFER_SAMPLES};

    // We need a single channel buffer to hold the special sync data when we start up
    juce::AudioBuffer<float> syncBuffer {1, MIX_BUFFER_SAMPLES};

    // Our 16-bit interleaved audio device output buffer
    int16_t hwBuff[HW_BUFFER_SAMPLES];

}; // end class Rmixer

