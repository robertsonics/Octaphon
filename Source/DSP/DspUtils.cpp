// **************************************************************************
//     Filename: DspUtils.cpp
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

#include "DspUtils.h"

// **************************************************************************
// DspUtils
// **************************************************************************
DspUtils::DspUtils() {

    // Capture the size of our ADSR gain lookup table
    adsrTableSize = ADSR_TABLE_SIZE;

    // Generate the table of corresponding linear gain values. The last entry
    //  should be 1.0 for 0 dB
    float g = ADSR_LIMIT_LO;
    for (int i = 0; i < adsrTableSize; i++) {
        ADSR_table[i] = Decibels::decibelsToGain( g + 0.5f );
        g += ADSR_STEP_SIZE;
    }
}

// **************************************************************************
// ~DspUtils
// **************************************************************************
DspUtils::~DspUtils() {

}

// **************************************************************************
// dBToLinear
// **************************************************************************
float DspUtils::dBToLinear(float g) {

    if (g < (ADSR_LIMIT_LO + 0.5f))
        return 0.0f;
    if (g > ADSR_LIMIT_HI)
        return ADSR_table[adsrTableSize - 1];

    int i = (adsrTableSize - 1) + (int)(g + 0.5f);
    if ((i < 0) || (i > (adsrTableSize - 1)))
            DBG("bad table index");
    return ADSR_table[(i)];
}

// **************************************************************************
// iirCoefficients
// **************************************************************************
void DspUtils::iirCoefficients(IIR_COEFF_STRUCTURE * pFc, int type, double samplesPerSec, double freq, double q, double gain ) {

	if( freq > samplesPerSec/(double)2.0 ) {
		// For center frequencies above Nyquist we simply create the identity transform
		pFc->c[0]= pFc->c[3]= (double)1.0;
		pFc->c[1]= pFc->c[2]= pFc->c[4]= pFc->c[5]= (double)0.0;

	} else {
		// We use RBJ's Cookbook filter
		double fA= pow( (double)10.0, (double)gain/40.0 );
		double fOmega= MathConstants<double>::twoPi * freq / samplesPerSec;
		double fSin= sin( fOmega );
		double fCos= cos( fOmega );
		double fAlpha= fSin / (2.0*q);

		switch (type)
			{

			case LOW_PASS:
				pFc->c[0]= ((double)1.0 - fCos) / (double)2.0;
				pFc->c[1]= (double)1.0 - fCos;
				pFc->c[2]= ((double)1.0 - fCos) / (double)2.0;
				pFc->c[3]= (double)1.0 + fAlpha;
				pFc->c[4]= (double)-2.0 * fCos;
				pFc->c[5]= (double)1.0 - fAlpha;
			break;

			case HIGH_PASS:
				pFc->c[0]= ((double)1.0 + fCos) / (double)2.0;
				pFc->c[1]= -((double)1.0 + fCos);
				pFc->c[2]= ((double)1.0 + fCos) / (double)2.0;
				pFc->c[3]= (double)1.0 + fAlpha;
				pFc->c[4]= (double)-2.0 * fCos;
				pFc->c[5]= (double)1.0 - fAlpha;
			break;

			case PEAKING:
				pFc->c[0]= (double)1.0 + fAlpha*fA;
				pFc->c[1]= (double)-2.0 * fCos;
				pFc->c[2]= (double)1.0 - fAlpha*fA;
				pFc->c[3]= (double)1.0 + fAlpha/fA;
				pFc->c[4]= (double)-2.0 * fCos;
				pFc->c[5]= (double)1.0 - fAlpha/fA;
			break;

			}

		// Normalize the coefficients by the 4th one
		for( int iCoeff=0; iCoeff<3; iCoeff++ )
			pFc->c[iCoeff] /= pFc->c[3];

		for( int iCoeff2=4; iCoeff2<6; iCoeff2++ )
			pFc->c[iCoeff2] /= pFc->c[3];

		// Now that we've normalized by this coefficient, we must set it to 1.0
		pFc->c[3]= 1.0;

		// We should have at least one non-zero b[] coefficient
		//assert( fCoeffs[0] != 0.0 || fCoeffs[1] != 0.0 || fCoeffs[2] != 0.0 );

	} // end else calculating filter coefficients

}

