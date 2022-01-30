// **************************************************************************
//     Filename: Sound.cpp
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
#include "Sound.h"


// **************************************************************************
// Sound
// **************************************************************************
Sound::Sound() {

    formatManager.registerBasicFormats();
    fLoaded = false;
}

// **************************************************************************
// ~Sound
// **************************************************************************
Sound::~Sound() {

}


// **************************************************************************
// unload
// **************************************************************************
void Sound::unload(void) {

    soundBuffer.clear();
    fLoaded = false;
}

// **************************************************************************
// load
// **************************************************************************
bool Sound::load(String sndFileName) {

File sndFile(sndFileName);
bool fResult = false;

    if (sndFile.existsAsFile()) {
        formatReader = formatManager.createReaderFor(sndFileName);
        soundBuffer.clear();
        fLoaded = false;
        numChannels = formatReader->numChannels;
        if (numChannels == 1) {
            numSamples = formatReader->lengthInSamples;
            soundBuffer.setSize(numChannels, numSamples);
            formatReader->read(&soundBuffer, 0, numSamples, 0, true, true);
            fResult = true;
            fLoaded = true;
        }
        delete formatReader;
    }
    return fResult;
}
