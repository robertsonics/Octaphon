// **************************************************************************
//     Filename: MainComponent.h
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

#include "DspUtils.h"
#include "Rmixer.h"
#include "SoundManager.h"
#include "VoiceManager.h"
#include "MidiManager.h"
#include "Interface.h"
#include "MyLookAndFeel.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component,
                        public juce::ComboBox::Listener,
                        public ChangeBroadcaster,
                        private MidiInputCallback
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    bool getChangePending()						    { return m_changePendingFlag; }
	void clearChangePending()					    { m_changePendingFlag = false; }

	void setMidiInput(int index);
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;
	void handleIncomingMidiMessage(MidiInput *source, const MidiMessage &message);

	bool loadPreset(String presetFilePath);

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...

    uint8_t m_abMix;
    uint8_t m_abSpread;

	bool m_changePendingFlag;

 	AudioDeviceManager deviceManager;
	int lastInputIndex;

	MyLookAndFeel myLookAndFeel;

	DspUtils dspUtils;
    SoundManager soundManager;
    VoiceManager voiceManager;
    MidiManager midiManager;
    Rmixer rmixer;

    std::unique_ptr<juce::ComboBox> midiBox;
    std::unique_ptr<juce::Label> lblVersion;
    std::unique_ptr<Interface> interface;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
