// **************************************************************************
//     Filename: PitchBend.cpp
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

#include "PitchBend.h"

// **************************************************************************
// PitchBend
// **************************************************************************
PitchBend::PitchBend(int frames) {

    m_numframes = frames;
    sampleFractInc = UNITY_PITCH_INC;
    sampleFractAcc.u32 = 0;
    for (int n = 0; n < NUM_OUTPUTS; n++) {
        curSample[n] = 0.0f;
        nxtSample[n] = 0.0f;
    }
}

// **************************************************************************
// ~PitchBend
// **************************************************************************
PitchBend::~PitchBend() {

}


// **************************************************************************
// Reset
// **************************************************************************
void PitchBend::reset() {

    sampleFractAcc.u32 = 0;
    for (int n = 0; n < NUM_OUTPUTS; n++) {
        curSample[n] = 0.0f;
        nxtSample[n] = 0.0f;
    }
}


// **************************************************************************
// getNumFrames
// **************************************************************************
uint16_t PitchBend::getNumFrames(void) {

U32_UNION tmpFrames;

    tmpFrames.u32 = m_numframes * sampleFractInc;
    tmpFrames.u32 += sampleFractAcc.u16[0];
    return tmpFrames.u16[1];

}

// **************************************************************************
// process
// **************************************************************************
void PitchBend::process(AudioBuffer<float> & srcBuff, AudioBuffer<float> & dstBuff) {

const float *srcPtr[NUM_OUTPUTS];
float *dstPtr[NUM_OUTPUTS];
uint16_t j = 0;
int s, n;
double slope;

    for (n = 0; n < NUM_OUTPUTS; n++) {
        srcPtr[n] = srcBuff.getReadPointer(n);
        dstPtr[n] = dstBuff.getWritePointer(n);
    }

    for (s = 0; s < m_numframes; s++) {

        sampleFractAcc.u32 += sampleFractInc;
        if (sampleFractAcc.u16[1] > 0) {
            j += sampleFractAcc.u16[1];

            if (j == 1) {
                for (n = 0; n < NUM_OUTPUTS; n++) {
                    curSample[n] = nxtSample[n];
                    nxtSample[n] = (double)srcPtr[n][j-1];
                }
            }
            else {
                for (n = 0; n < NUM_OUTPUTS; n++) {
                    curSample[n] = (double)srcPtr[n][j-2];
                    nxtSample[n] = (double)srcPtr[n][j-1];
                 }
            }
            sampleFractAcc.u16[1] = 0;
        }

        slope = (1.0 / (double)0xffff) * (double)sampleFractAcc.u16[0];
        for (n = 0; n < NUM_OUTPUTS; n++) {
            *dstPtr[n]++ = curSample[n] + ((nxtSample[n] - curSample[n]) * slope);
        }
    }
}
