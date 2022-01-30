// **************************************************************************
//     Filename: Sound.h
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


// *************************************************************************
class Sound : public ChangeBroadcaster
{

public:
	Sound();
	~Sound();

	void unload();
	bool exists()                       { return fLoaded; }
	bool load(String sndFileName);
	int getNumChannels()                { return numChannels; }
	int getNumSamples()                 { return numSamples; }
	const float * getSoundBase()        { return soundBuffer.getReadPointer(0); }

private:

    bool fLoaded;
    int numChannels;
    int64 numSamples;

    AudioFormatManager formatManager;
    AudioFormatReader * formatReader;
    AudioBuffer<float> soundBuffer;

}; // end class Sound

