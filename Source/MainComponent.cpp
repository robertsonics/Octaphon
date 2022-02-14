// **************************************************************************
//     Filename: MainComponent.cpp
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

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{

String dmsg;

    m_changePendingFlag = false;
    Process::setPriority(Process::RealtimePriority);

    setSize (800, 480);

    LookAndFeel::setDefaultLookAndFeel(&myLookAndFeel);

    midiBox.reset (new juce::ComboBox ("port combo box"));
    addAndMakeVisible (midiBox.get());
    midiBox->setEditableText (false);
    midiBox->setJustificationType (juce::Justification::centredLeft);
    midiBox->setTextWhenNothingSelected (juce::String());
    midiBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    midiBox->addListener (this);
    midiBox->setBounds(getWidth() - 280, 10, 260, 24);

    lblVersion.reset (new juce::Label ("new label", TRANS("Octaphon Beta v0.10")));
    addAndMakeVisible (lblVersion.get());
    lblVersion->setFont (juce::Font (16.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    lblVersion->setJustificationType (juce::Justification::centredLeft);
    lblVersion->setEditable (false, false, false);
    lblVersion->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    lblVersion->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));
    lblVersion->setBounds (20, 10, 200, 24);

    lblMidiDev.reset (new juce::Label ("new label", TRANS("MIDI Input: ")));
    addAndMakeVisible (lblMidiDev.get());
    lblMidiDev->setFont (juce::Font (16.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    lblMidiDev->setJustificationType (juce::Justification::centredLeft);
    lblMidiDev->setEditable (false, false, false);
    lblMidiDev->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    lblMidiDev->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));
    lblMidiDev->setBounds (getWidth() - 360, 10, 200, 24);

    interface.reset(new Interface(this, &rmixer, &voiceManager, &soundManager));
    addAndMakeVisible(interface.get());
    interface->setBounds(0, 42, getWidth(), getHeight() - 42);

	// Populate the MIDI In combo box with available devices and open the first
	//  one in the list if there are any. Otherwise create a single notification
	//  entry in the list.
	lastInputIndex = 0;
	midiBox->setTextWhenNoChoicesAvailable("No MIDI IN Devices!");
	auto midiInputs(MidiInput::getAvailableDevices());

	StringArray midiInputNames;
	for (auto input : midiInputs)
	    midiInputNames.add(input.name);

	midiBox->addItemList(midiInputNames, 1);

	// On the Pi, let's use the second input device
	if (midiBox->getNumItems() > 0) {
	    if (midiBox->getNumItems() > 2)
	        setMidiInput(2);
	    else
	        setMidiInput(1);
	}

    // Initialize our sound manager, gain utils, voice manager and mixer
    soundManager.setVoiceManager(&voiceManager);
    voiceManager.setDspUtils(&dspUtils);
    midiManager.setSoundManager(&soundManager);
    midiManager.setVoiceManager(&voiceManager);
    rmixer.setVoiceManager(&voiceManager);
    //rmixer.setPitchBend(8192);
    //rmixer.clearChangePending();
    //rmixer.addChangeListener(this);
    //rmixer.setStatsEnabled(true);

    loadPreset("~/Projects/octaphon.csv");

    // Start the audio device and if successful, start our voice manager
    //  and mixer threads. Load the default sounds
    if (rmixer.startAudio("plughw:0,0")) {
        //voiceManager.startThread();
        rmixer.startThread();
        m_changePendingFlag = true;
        sendChangeMessage();
    }
    else
        DBG("Couldn't start audio");
}

MainComponent::~MainComponent()
{

    DBG("Main component shutdown");
    //stopTimer();
    rmixer.stopThread(2000);
    //rmixer.removeChangeListener(this);
	//voiceManager.stopThread(2000);
	//voiceManager.removeChangeListener(this);
	rmixer.stopAudio();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    //g.fillAll(Colours::black);

}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

    //lblVersion->setBounds (20, 20, 200, 24);
    //midiBox->setBounds(getWidth() - 280, 20, 260, 24);

}

// ******************************************************************
//  comboBoxChanged
// ******************************************************************
void MainComponent::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == midiBox.get())
    {
		setMidiInput(midiBox->getSelectedItemIndex());
    }
}

// ******************************************************************
//  setMidiInput
// ******************************************************************
void MainComponent::setMidiInput(int index)
{
	auto list = MidiInput::getAvailableDevices();
	deviceManager.removeMidiInputDeviceCallback(list[lastInputIndex].identifier, this);
	auto newInput = list[index];
	if (!deviceManager.isMidiInputDeviceEnabled(newInput.identifier))
		deviceManager.setMidiInputDeviceEnabled(newInput.identifier, true);
	deviceManager.addMidiInputDeviceCallback(newInput.identifier, this);
	midiBox->setSelectedId(index + 1, dontSendNotification);
	lastInputIndex = index;
}

// ******************************************************************
//  handleIncomingMidiMessage
// ******************************************************************
void MainComponent::handleIncomingMidiMessage(MidiInput *source, const MidiMessage &message)
{

int n, v;

	if (message.isNoteOn()) {
		n = message.getNoteNumber();
		v = message.getVelocity();
        midiManager.noteOn(n, v);
	}

	else if (message.isNoteOff()) {
		n = message.getNoteNumber();
		midiManager.noteOff(n);
	}
/*
	else if (message.isControllerOfType(0x14)) {
        soundManager.load(0, message.getControllerValue(), 0, 36);
        m_changePendingFlag = true;
        sendChangeMessage();
	}
	else if (message.isControllerOfType(0x34)) {
        soundManager.load(1, message.getControllerValue(), 0, 36);
        m_changePendingFlag = true;
        sendChangeMessage();
	}
	else if (message.isControllerOfType(0x03)) {
        m_abMix = message.getControllerValue();
        voiceManager.setAbMix(m_abMix, m_abSpread);
        m_changePendingFlag = true;
        sendChangeMessage();
	}
	else if (message.isControllerOfType(0x40)) {
        if (message.getControllerValue() >= 64)
            soundManager.sustain(true);
        else
            soundManager.sustain(false);
	}

	else if (message.isPitchWheel()) {
		n = message.getPitchWheelValue();
		rmixer.setPitchBend(n);
        m_changePendingFlag = true;
        sendChangeMessage();
	}
*/
}

// ******************************************************************
//  loadPreset
// ******************************************************************
bool MainComponent::loadPreset(String presetFilePath) {

File initFile(presetFilePath);
StringArray initLines;
StringArray fields;
int numLines;

    if (!initFile.exists()) {
        DBG("Can't open init file");
        return false;
    }
    initFile.readLines(initLines);
    numLines = initLines.size();
    for (int l = 0; l < numLines; l++) {
        if (initLines[l].startsWith("#PATH")) {
            fields.addTokens(initLines[l], ",", "");
            soundManager.setSoundPath(fields[1]);
            fields.clear();
        }
        else if (initLines[l].startsWith("#FILE")) {
            soundManager.loadSound(initLines[l]);
        }
        else if (initLines[l].startsWith("#NOTE")) {
            midiManager.initNote(initLines[l]);
        }
    }
    return true;
}



