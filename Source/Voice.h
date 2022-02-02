// **************************************************************************
//     Filename: Voice.h
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
#include "Config.h"
#include "DspUtils.h"
#include "PitchBend.h"
#include "Fader.h"

// We need an output audio buffer large enough to hold twice the number of
//  samples in an alsa period, because the mixer could be doing sample-rate
//  conversion of up to 2X.

#define DSP_BUFFER_SAMPLES      (ALSA_PERIOD_FRAMES * 4)

// This structure is use to prepare the voice for playing a particular sound.
typedef struct {

    bool enabled;
    uint8_t midiNote;
    uint16_t soundIndex;
    int64 numSamples;
    const float * pSoundBase;
    float * gain_dB;

} VOICE_PLAY_STRUCTURE;


// *************************************************************************
class Voice : public ChangeBroadcaster
{

public:
	Voice(int v);
	~Voice();

	uint8_t getState()                          { return state; }
	void setState(int newState)                 { state = newState; }
	void setDspUtils(DspUtils * gu)             { dspUtils = gu; }
	uint8_t getMidiNote()                       { return midiNote; }

    bool prepare(VOICE_PLAY_STRUCTURE * play);
    void start();
    void stop();
	void reset();
    uint16_t getFrames(AudioBuffer<float> * mixBuff, uint16_t reqFrames);

	void clearChangePending()				    { m_changePendingFlag = false; }
	bool getChangePending()					    { return m_changePendingFlag; }

private:

    uint16_t voiceNum;                          // This voice number
    uint16_t soundNum;                          // Current sound if prepared
    uint8_t midiNote;                           // MIDI Note number
    uint8_t state;                              // Current voice state
    bool loopFlag;                              // Loop flag

    const float * soundBuffer;                        // pointer to sound buffer base
    float * readPointer;                        // sample buffer read pointer
    uint64_t totalSamples;                      // length in samples of sound
    uint64_t samplesPlayed;                     // samples played if playing

    DspUtils *dspUtils;

    std::unique_ptr<PitchBend> pitchBend;
    std::unique_ptr<Fader> fader;

    bool firstBufferFlag;
    float voiceGain_dB[NUM_OUTPUTS];
    float targGain[NUM_OUTPUTS];
    float currGain[NUM_OUTPUTS];

    bool m_changePendingFlag;

    float dspBuffer[DSP_BUFFER_SAMPLES];

    // Create two buffers for our de-interleaved stereo channels.
    //float dspLeftBuff[DSP_BUFFER_SAMPLES];
    //float dspRightBuff[DSP_BUFFER_SAMPLES];

    // Along with a pointer array to them for creating our virtual juce AudioBuffer
    //float * dspBuff[2] { &dspLeftBuff[0], &dspRightBuff[0] };

    // Now create an instance of an AudioBuffer that points to the channel arrays
    //juce::AudioBuffer<float> proxyBuff { &dspBuff[0], 2, DSP_BUFFER_SAMPLES };

}; // end class Voice

