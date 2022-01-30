// **************************************************************************
//     Filename: DspUtils.h
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

#define ADSR_LIMIT_HI       0.0f
#define ADSR_LIMIT_LO      -80.0f
#define ADSR_STEP_SIZE      0.5f

#define ADSR_TABLE_SIZE     (int)((ADSR_LIMIT_HI - ADSR_LIMIT_LO) / ADSR_STEP_SIZE)

#define IIR_FILTER_ORDER        2
#define IIR_NUM_COEFFS          (2 * (IIR_FILTER_ORDER + 1))

enum {
    LOW_PASS = 0,
    HIGH_PASS,
    PEAKING
};

typedef struct {

    double c[IIR_NUM_COEFFS];

} IIR_COEFF_STRUCTURE;


// **************************************************************************
class DspUtils  {

public:
	DspUtils();
	~DspUtils();
	float dBToLinear(float g);
	static void iirCoefficients(IIR_COEFF_STRUCTURE * pFc, int type, double fsamplesPerSec, double freq, double q, double gain );

private:

int adsrTableSize;

// Allocate our ADSR gain lookup table
float ADSR_table[ADSR_TABLE_SIZE];

}; // end class DspUtils

