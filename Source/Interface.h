/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.1.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
#include "Rmixer.h"
#include "VoiceManager.h"
#include "SoundManager.h"

class MainComponent;

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class Interface  : public juce::Component,
                   public juce::Timer,
                   public juce::ChangeListener
{
public:
    //==============================================================================
    Interface (MainComponent * mc, Rmixer * rm, VoiceManager * vm, SoundManager *sm);
    ~Interface() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

	void changeListenerCallback(ChangeBroadcaster *) override;
    void timerCallback() override;

    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

    Rmixer * rmixer;
    MainComponent * mainComponent;
    VoiceManager * voiceManager;
    SoundManager * soundManager;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::GroupComponent> juce__groupComponent;
    std::unique_ptr<juce::Label> lblAudioFrameAve;
    std::unique_ptr<juce::Label> juce__label;
    std::unique_ptr<juce::Label> lblAudioFrameMax;
    std::unique_ptr<juce::Label> juce__label2;
    std::unique_ptr<juce::Label> lblActiveVoices;
    std::unique_ptr<juce::Label> juce__label5;
    std::unique_ptr<juce::Label> lblAudioUnderruns;
    std::unique_ptr<juce::Label> juce__label7;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Interface)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

