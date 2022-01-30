// **************************************************************************
//     Filename: Mixer.cpp
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

#include "Rmixer.h"
#include <unistd.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <iostream>
using namespace std;


// **************************************************************************
// ~Rmixer
// **************************************************************************
Rmixer::~Rmixer() {

}


// **************************************************************************
// startAudio
// **************************************************************************
bool Rmixer::startAudio(String sndDevName) {

int alsa_err;
unsigned int alsa_val;
snd_pcm_hw_params_t * hw_params;
snd_pcm_uframes_t uframes;
String msg;
float * fPtr;
int i;

char** hints = nullptr;
String name;
String ioid;

uint8_t qBuf[8];

    syncModeEnabled = true;

    // Zero out our hardware buffer
    for (i = 0; i < (HW_BUFFER_SAMPLES); i++) {
        hwBuff[i] = 0;
    }

    // Prefill our sync ID buffer with special values
    fPtr = syncBuffer.getWritePointer(0);
    for (i = 0; i < MIX_BUFFER_SAMPLES; i++) {
        *fPtr++ = 0.5f;
    }

    // Open our I2C interface, set the slave address and send a reset to our audio
    //  hardware.
    m_qId = open("/dev/i2c-1", O_RDWR);
    if (m_qId < 0) {
        cout << "Can't open I2C-1 device" << endl;
        return false;
    }
    if (ioctl(m_qId, I2C_SLAVE, QWIIC_ADDRESS) < 0) {
        cout << "Can't find audio hardware at I2C address" << endl;
        return false;
    }
    qBuf[0] = 0x01;
    qBuf[1] = 0x55;
    if (write(m_qId, qBuf, 2) != 2) {
        cout << "Can't send reset command to audio hardware" << endl;
        return false;
    }
    cout << "Audio hardware reset at I2C address" << endl;

    // ======================= Enumerate alsa devices ===================
    DBG("===============================");
    DBG("Enumerating alsa output devices");
    alsa_err = snd_device_name_hint(-1, "pcm", (void***)&hints);
    if (alsa_err != 0) {
        DBG("Can't get output device names");
        return false;
    }
    char** n = hints;
    while (*n != nullptr) {
        name = snd_device_name_get_hint(*n, "NAME");
        ioid = snd_device_name_get_hint(*n, "IOID");
        DBG(name);
        n++;
    }
    snd_device_name_free_hint((void**)hints);
    DBG("===============================");

    // ======================= Open and initialize the output device ===================
    cout << "Initializing Playback Device..." << endl;
    m_sndDeviceOut = nullptr;

    // Open the sound device by name
    //alsa_err = snd_pcm_open( &m_sndDeviceOut, "plughw:0,0", SND_PCM_STREAM_PLAYBACK, SND_PCM_NONBLOCK);
    alsa_err = snd_pcm_open( &m_sndDeviceOut, "plughw:0,0", SND_PCM_STREAM_PLAYBACK, 0);
    if (alsa_err < 0) {
        m_sndDeviceOut = nullptr;
        cout << "can't open sound output device" << endl;
        return false;
    }

    // Allocate a hardware parameter block
    alsa_err = snd_pcm_hw_params_malloc(&hw_params);
    if (alsa_err < 0) {
        cout << "can't allocate output hw params" << endl;
        return false;
    }

    // Set hardware parameters to default
    alsa_err = snd_pcm_hw_params_any(m_sndDeviceOut, hw_params);
    if (alsa_err < 0) {
        cout << "can't initialize output hw params" << endl;
        return false;
    }

    // Set for interleaved
    alsa_err = snd_pcm_hw_params_set_access(m_sndDeviceOut, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED);
    if (alsa_err < 0) {
        cout << "can't set output access type" << endl;
        return false;
    }

    // Set for 16-bit Little Endian
    alsa_err = snd_pcm_hw_params_set_format(m_sndDeviceOut, hw_params, SND_PCM_FORMAT_S16_LE);
    if (alsa_err < 0) {
        cout << "can't set output format" << endl;
        return false;
    }

    // Set for 2 channels = stereo
    alsa_err = snd_pcm_hw_params_set_channels(m_sndDeviceOut, hw_params, 2);
    if (alsa_err < 0) {
        cout << "can't set output channels" << endl;
        return false;
    }

    // Set sample rate to 44100
    msg.clear();
    msg = "Sample rate: ";
    alsa_val = 44100;
    alsa_err = snd_pcm_hw_params_set_rate_near(m_sndDeviceOut, hw_params, &alsa_val, 0);
    if (alsa_err < 0) {
        cout << "can't set output samplerate" << endl;
        return false;
    }
    else {
        msg += (int)alsa_val;
        cout << msg << endl;
    }

    // Set the period size
    uframes = ALSA_PERIOD_FRAMES;
    alsa_err = snd_pcm_hw_params_set_period_size_near(m_sndDeviceOut, hw_params, &uframes, 0);
    if (alsa_err < 0) {
        cout << "can't set output period size" << endl;
        return false;
    }

    // Set the number of periods
    alsa_val = ALSA_PERIODS;
    alsa_err = snd_pcm_hw_params_set_periods_near(m_sndDeviceOut, hw_params, &alsa_val, 0);
    if (alsa_err < 0) {
        cout << "can't set output periods" << endl;
        return false;
    }

    // Write the hardware parameters
    alsa_err = snd_pcm_hw_params(m_sndDeviceOut, hw_params);
    if (alsa_err < 0) {
        cout << "can't set output hw params" << endl;
        return false;
    }

    // Get the actual period size
    msg.clear();
    m_numframes = 0;
    msg = "Period size: ";
    alsa_err = snd_pcm_hw_params_get_period_size(hw_params, &m_numframes, 0);
    if (alsa_err < 0) {
        cout << "can't get output period size" << endl;
        return false;
    }
    else {
        m_numsamples = m_numframes * 2;
        msg += (int)m_numframes;
        cout << msg << endl;
    }

    // Get the actual periods
    msg.clear();
    alsa_val = 0;
    msg = "Periods: ";
    alsa_err = snd_pcm_hw_params_get_periods(hw_params, &alsa_val, 0);
    if (alsa_err < 0) {
        cout << "can't get output periods" << endl;
        return false;
    }
    else {
        msg += (int)alsa_val;
        cout << msg << endl;
    }

    // Free the hardware parameter block memory
    snd_pcm_hw_params_free(hw_params);
    hw_params = nullptr;

    // ======================= Start the audio engine ===================
    // Write enough audio to fill the buffer
    uframes = snd_pcm_avail_update(m_sndDeviceOut);
    while (uframes >= ALSA_PERIOD_FRAMES) {
        snd_pcm_writei(m_sndDeviceOut, hwBuff, m_numframes);
        if (alsa_err < 0) {
            cout << "can't write data" << endl;
            return false;
        }
        uframes = snd_pcm_avail_update(m_sndDeviceOut);
    }

    //pitchBend.reset(new PitchBend(m_numframes));
    // We're running at 4X the sample rate with 8 outputs
    pitchBend.reset(new PitchBend(m_numframes / 4));
    m_sampleIncrement = UNITY_PITCH_INC;
    FloatVectorOperations::enableFlushToZeroMode(true);
    startThread();

    // Wait a bit until we know we're sending the sync data, then send the sync
    //  command to the audio hardware.
    Thread::sleep(100);
    qBuf[0] = 0x01;
    qBuf[1] = 0x01;
    if (write(m_qId, qBuf, 2) != 2) {
        cout << "Can't send sync command to audio hardware" << endl;
        return false;
    }

    // Finally, start normal audio output and send the run command to the audio
    //  hardware
    Thread::sleep(100);
    syncModeEnabled = false;
    qBuf[0] = 0x01;
    qBuf[1] = 0x02;
    if (write(m_qId, qBuf, 2) != 2) {
        cout << "Can't send run command to audio hardware" << endl;
        return false;
    }

    // Wait another bit then read the channel 1 offset register
    Thread::sleep(100);
    qBuf[0] = 0x02;
    if (write(m_qId, qBuf, 1) != 1) {
        cout << "Can't send read offset command to audio hardware" << endl;
        return false;
    }
    if (read(m_qId, qBuf, 1) != 1) {
        cout << "Can't read offset channel from audio hardware" << endl;
        return false;
    }
    //DBG((int)qBuf[0]);

    return true;
}

// **************************************************************************
// stopAudio
// **************************************************************************
void Rmixer::stopAudio() {

    if (m_sndDeviceOut != nullptr) {
        cout << "Stop audio" << endl;
        snd_pcm_drain(m_sndDeviceOut);
        snd_pcm_close(m_sndDeviceOut);
        m_sndDeviceOut = nullptr;
    }
}

// **************************************************************************
// setPitchBend
// **************************************************************************
void Rmixer::setPitchBend(int pb) {

    if (pb > 16384)
        return;
    if (pb > 8192)
        m_sampleIncrement = UNITY_PITCH_INC + (((pb - 8192) * PITCH_UP_MAX) / 8192);
    else if (pb < 8192)
        m_sampleIncrement = UNITY_PITCH_INC - (((8192 - pb) * PITCH_DN_MAX) / 8192);
    else
        m_sampleIncrement = UNITY_PITCH_INC;


}

// **************************************************************************
// getStats
// **************************************************************************
void Rmixer::getStats(MIXER_STATS_STRUCTURE * stats) {

    stats->frameMsAve = dspFrameMsAve;
    stats->frameMsMax = dspFrameMsMax;
    stats->underruns = dspUnderruns;
}

// **************************************************************************
// run
// **************************************************************************
void Rmixer::run() {

snd_pcm_uframes_t uframes;
snd_pcm_uframes_t pframes;
int alsa_err;

juce::int64 startTick = 0;
juce::int64 endTick;
double thisDeltaTimeMs;
float localFrameMsMax = 0.0f;
float localFrameMsAve = 0.0f;
float localFrameMsAcc = 0.0f;
int localUnderruns = 0;

bool dbgExit = false;

    cout << "Mixer thread running" << endl;

    setPriority(10);

    dspFrameMsMax = 0.0f;
    dspFrameMsAve = 0.0f;
	time = new Time();

	while (!threadShouldExit() && !dbgExit) {

	    uframes = snd_pcm_avail_update(m_sndDeviceOut);
	    if (uframes < 0) {
            DBG("Alsa update avail recovery");
            snd_pcm_recover(m_sndDeviceOut, uframes, 0);
            dbgExit = true;
	    }
	    //else if ((uframes >= m_numframes) && (iframes >= m_numframes)) {
	    else if (uframes >= m_numframes) {

            //std::cout << static_cast<void*>(dstBuff) << std::endl;

            // Grab the current hig res tick
            startTick = time->getHighResolutionTicks();

            // Figure out how many frames we need based on the current
            //  pitch factor
            pitchBend->setSampleIncrement(m_sampleIncrement);
            pframes = pitchBend->getNumFrames();

            // Silence our mix buffer
            mixBuffer.clear(0, pframes);

            typedef AudioData::Pointer<AudioData::Int16, AudioData::LittleEndian, AudioData::Interleaved,    AudioData::NonConst> DstSampleType;
            typedef AudioData::Pointer<AudioData::Float32, AudioData::NativeEndian, AudioData::NonInterleaved, AudioData::NonConst> SrcSampleType;

            // If we're in sync ID mode, then send the special data on just the first and second channels
            if (syncModeEnabled) {
                DstSampleType dst0LData(&hwBuff[0], 8);
                SrcSampleType src0LData((AudioData::NonConst::VoidType *)syncBuffer.getReadPointer(0));
                dst0LData.convertSamples(src0LData, (m_numframes / 4));
             }

            // Otherwise, we need to mix all of our voices and then do dsp.
            else {

                // Add voice data to mix buffer here
                voiceManager->getFrames(&mixBuffer, pframes);

                // Do pitch bending here
                pitchBend->process(mixBuffer, mainsBuffer);

                // Convert to fixed and send to the PCM devices
                DstSampleType dst1LData(&hwBuff[0], 8);
                SrcSampleType src1LData((AudioData::NonConst::VoidType *)mainsBuffer.getReadPointer(0));
                dst1LData.convertSamples(src1LData, (m_numframes / 4));
                DstSampleType dst1RData(&hwBuff[1], 8);
                SrcSampleType src1RData((AudioData::NonConst::VoidType *)mainsBuffer.getReadPointer(1));
                dst1RData.convertSamples(src1RData, (m_numframes / 4));

                DstSampleType dst2LData(&hwBuff[2], 8);
                SrcSampleType src2LData((AudioData::NonConst::VoidType *)mainsBuffer.getReadPointer(2));
                dst2LData.convertSamples(src2LData, (m_numframes / 4));
                DstSampleType dst2RData(&hwBuff[3], 8);
                SrcSampleType src2RData((AudioData::NonConst::VoidType *)mainsBuffer.getReadPointer(3));
                dst2RData.convertSamples(src2RData, (m_numframes / 4));

                DstSampleType dst3LData(&hwBuff[4], 8);
                SrcSampleType src3LData((AudioData::NonConst::VoidType *)mainsBuffer.getReadPointer(4));
                dst3LData.convertSamples(src3LData, (m_numframes / 4));
                DstSampleType dst3RData(&hwBuff[5], 8);
                SrcSampleType src3RData((AudioData::NonConst::VoidType *)mainsBuffer.getReadPointer(5));
                dst3RData.convertSamples(src3RData, (m_numframes / 4));

                DstSampleType dst4LData(&hwBuff[6], 8);
                SrcSampleType src4LData((AudioData::NonConst::VoidType *)mainsBuffer.getReadPointer(6));
                dst4LData.convertSamples(src4LData, (m_numframes / 4));
                DstSampleType dst4RData(&hwBuff[7], 8);
                SrcSampleType src4RData((AudioData::NonConst::VoidType *)mainsBuffer.getReadPointer(7));
                dst4RData.convertSamples(src4RData, (m_numframes / 4));
            }

            // Grab the current high res tick and calculate how long our frame processing
            //  took. If we exceed the previous maximum, update the max and signal that
            //  there's been a change.
            if (statsEnabledFlag) {
                endTick = time->getHighResolutionTicks();
                if (resetStatsFlag) {
                    resetStatsFlag = false;
                    localFrameMsMax = 0.0f;
                    localFrameMsAve = 0.0f;
                    localFrameMsAcc = 0.0f;
                    localUnderruns = 0;
                }
                thisDeltaTimeMs = time->highResolutionTicksToSeconds(endTick - startTick) * 1000.0;
                if (thisDeltaTimeMs > localFrameMsMax)
                    localFrameMsMax = thisDeltaTimeMs;
                localFrameMsAcc = (localFrameMsAcc * 63.0f / 64.0f) + thisDeltaTimeMs;
                localFrameMsAve = localFrameMsAcc / 64.0f;

                if (statsRequestFlag) {
                    statsRequestFlag = false;
                    if (!m_changePendingFlag) {
                        dspFrameMsMax = localFrameMsMax;
                        dspFrameMsAve = localFrameMsAve;
                        dspUnderruns = localUnderruns;
                        m_changePendingFlag = true;
                        sendChangeMessage();
                    }
                }
            }

            // Now Send the PCM data to the audio device
            alsa_err=snd_pcm_writei(m_sndDeviceOut, hwBuff, m_numframes);
            if (alsa_err < 0) {
                DBG("Alsa writei recovery");
                snd_pcm_recover(m_sndDeviceOut, (int)alsa_err, 1);
            }
            else if (uframes > (m_numframes * 3))
                DBG("Getting behind");
            else if (uframes > (m_numframes * 4))
                DBG("Underrun");
            //uframes = snd_pcm_avail_update(m_sndDeviceOut);
	    }

	    // Sleep for the specified interval
	    usleep(ALSA_UPDATE_INTERVAL);
	}
	cout << "Mixer thread stopped" << endl;
	return;
}




