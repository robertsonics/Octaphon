// **************************************************************************
//     Filename: Voice.cpp
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

#include <unistd.h>
#include "Voice.h"
#include "SoundManager.h"


// **************************************************************************
// Voice
// **************************************************************************
Voice::Voice(int v) {

    voiceNum = (uint16_t)v;
    m_changePendingFlag = false;
    state = VOICE_STATE_READY;
    loopFlag = false;
    //pitchBend.reset(new PitchBend(m_numframes / 4));
    fader.reset(new Fader(voiceNum));

}

// **************************************************************************
// ~Voice
// **************************************************************************
Voice::~Voice() {

}

// **************************************************************************
// assignSound
// **************************************************************************
bool Voice::prepare(VOICE_PLAY_STRUCTURE * play) {

/*
    String vMsg("Voice ");
    vMsg += voiceNum;
    vMsg += ", Sound ";
    vMsg += play->soundIndex;
    vMsg += ", Note ";
    vMsg += play->midiNote;
    for (int o = 0; o < NUM_OUTPUTS; o++) {
       vMsg += ", ";
        vMsg += String(play->gain_dB[o]);
    }
    DBG(vMsg);
*/
    state = VOICE_STATE_EMPTY;
    soundNum = play->soundIndex;
    totalSamples = play->numSamples;
    midiNote = play->midiNote;
    soundBuffer = play->pSoundBase;
    readPointer = (float *)soundBuffer;
    for (int n = 0; n < NUM_OUTPUTS; n++)
        voiceGain_dB[n] = play->gain_dB[n];

    state = VOICE_STATE_READY;
    return true;
}

// **************************************************************************
// reset
// **************************************************************************
void Voice::reset() {

}

// **************************************************************************
// start
// **************************************************************************
void Voice::start() {

    if (state == VOICE_STATE_READY) {
        samplesPlayed = 0;
        readPointer = (float *)soundBuffer;
        firstBufferFlag = true;
        state = VOICE_STATE_PLAYING;
    }
}

// **************************************************************************
// stop
// **************************************************************************
void Voice::stop() {

    if (state == VOICE_STATE_PLAYING) {

        state = VOICE_STATE_READY;
    }
}

// **************************************************************************
// getFrames
// **************************************************************************
// Since we are only supporting mono files for now, frames is the same as
//  samples. Fetch the requested number of samples from the sound buffer and
//  add (mix) them to the target mix buffer.

uint16_t Voice::getFrames(AudioBuffer<float> * mixbuff, uint16_t reqFrames) {

int s, n;
uint64_t remainingSamples;
uint16_t numSamples;

float * dspPtr = &dspBuffer[0];

    numSamples = reqFrames;

    // Figure out how many samples left in the file
    remainingSamples = totalSamples - samplesPlayed;

    // If we're not looping, and we've reached the end of the file, then
    //  only process the samples remaining in the file.
    if (remainingSamples < numSamples)
        numSamples = remainingSamples;

    // Silence our local dsp buffer - Do we need to do this?
    memset(dspBuffer, 0, reqFrames * sizeof(float));

    // Copy samples from the wav buffer to our dsp buffer
    for (s = 0; s < numSamples; s++) {
        *dspPtr++ = *readPointer++;
    }

    // Bump the number of samples played from this file
    samplesPlayed += numSamples;

    // Calculate gain adjustments here. If different than the current gain, we'll
    //  need to ramp this buffer from the current to the target.
    for (n = 0; n < NUM_OUTPUTS; n++) {
        targGain[n] = dspUtils->dBToLinear(voiceGain_dB[n]);
    }

/*
    // If our ADSR is active, then we need to modify the target gain accordingly
    if (adsrMode == ADSR_MODE_RELEASE) {
        if (adsrCurrGain_dB <= adsrTargGain_dB) {
            adsrMode = ADSR_MODE_INACTIVE;
            return 0;
        }
        else {
            // Temporarily do the shortest release
            //adsrCurrGain_dB -= adsrDeltaGain_dB;
            adsrCurrGain_dB = adsrTargGain_dB;
            targGain *= dspUtils->dBToLinear(adsrCurrGain_dB);
        }
    }
*/
    // If this is the first buffer fetch we don't want to be doing any ramping, but
    //  should start with the current gain value from the get-go.
    if (firstBufferFlag) {
        firstBufferFlag = false;
        for (n = 0; n < NUM_OUTPUTS; n++)
            currGain[n] = targGain[n];
    }

    // Now transfer the voice data to the target mix buffer with any necessary
    //  gain adjustments
    for (n = 0; n < NUM_OUTPUTS; n++) {
        if (voiceGain_dB[n] > MIN_GAIN_DB) {
            if (currGain[n] != targGain[n]) {
                mixbuff->addFromWithRamp(n, 0, &dspBuffer[0], numSamples, currGain[n], targGain[n]);
                currGain[n] = targGain[n];
            }
            else {
                mixbuff->addFrom(n, 0, &dspBuffer[0], numSamples, currGain[n]);
            }
        }
    }

    return numSamples;
}
