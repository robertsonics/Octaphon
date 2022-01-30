// **************************************************************************
//     Filename: VoiceManager.cpp
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

#include "VoiceManager.h"
#include <unistd.h>


// **************************************************************************
// VoiceManager
// **************************************************************************
VoiceManager::VoiceManager() {

    dspUtils = nullptr;
    for (int v = 0; v < NUM_VOICES; v++) {
        voice[v] = new Voice(v);
    }
}

// **************************************************************************
// ~VoiceManager
// **************************************************************************
VoiceManager::~VoiceManager() {

    for (int v = 0; v < NUM_VOICES; v++) {
        voice[v]->stop();
        delete voice[v];
        voice[v] = nullptr;
    }
}

// **************************************************************************
// setDspUtils
// **************************************************************************
void VoiceManager::setDspUtils(DspUtils * gu) {

    dspUtils = gu;
    for (int v = 0; v < NUM_VOICES; v++)
        voice[v]->setDspUtils(dspUtils);
}

// **************************************************************************
// startSounds
// **************************************************************************
bool VoiceManager::play(VM_PLAY_STRUCTURE * ps) {

int n, v;

    for (n = 0; n < NUM_OUTPUTS; n++) {
        if (ps->vp[n].enabled == false)
            break;
        v = allocateVoice();
        if ((v >= 0) && (v < NUM_VOICES)) {
            voice[v]->prepare((VOICE_PLAY_STRUCTURE *) &ps->vp[n]);
            voice[v]->start();
        }
    }
    return true;
}

// **************************************************************************
// stopSounds
// **************************************************************************
void VoiceManager::stop(uint8_t midiNote) {

    for (int v = 0; v < NUM_VOICES; v++) {
        if ((voice[v]->getState() == VOICE_STATE_PLAYING) &&
            (voice[v]->getMidiNote() == midiNote)) {
            voice[v]->stop();
        }
    }
}

// **************************************************************************
// allocateVoice
// **************************************************************************
int VoiceManager::allocateVoice() {

int avail = -1;

    for (int v = 0; v < NUM_VOICES; v++) {
        if (voice[v]->getState() == VOICE_STATE_READY) {
            return v;
        }
    }
    return avail;
}

// **************************************************************************
// getFrames
// **************************************************************************
void VoiceManager::getFrames(AudioBuffer<float> * mixBuff, uint16_t reqFrames) {

int n = 0;

    for (int v = 0; v < NUM_VOICES; v++) {
        if (voice[v]->getState() == VOICE_STATE_PLAYING) {
            if (voice[v]->getFrames(mixBuff, reqFrames) < reqFrames) {
                voice[v]->setState(VOICE_STATE_READY);
            }
            else
                n++;
        }
    }
    activeVoices = n;
}
