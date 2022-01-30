// **************************************************************************
//     Filename: PitchBend.h
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


// **************************************************************************
class PitchBend  {

public:
	PitchBend(int frames);
	~PitchBend();

	void setSampleIncrement(uint32_t inc)    { sampleFractInc = inc; }
	void reset(void);
    uint16_t getNumFrames(void);
    void process(AudioBuffer<float> & srcBuff, AudioBuffer<float> & dstBuff);


private:

	// Variables for samplerate conversion algorithm
	uint32_t sampleFractInc;
	U32_UNION sampleFractAcc;
	double curSampleLeft;
	double curSampleRight;
	double nxtSampleLeft;
	double nxtSampleRight;

	int m_numframes;

}; // end class PitchBend

