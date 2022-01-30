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

//[Headers] You can add your own extra header files here...

#include "MainComponent.h"

//[/Headers]

#include "Interface.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...

//[/MiscUserDefs]

//==============================================================================
Interface::Interface (MainComponent * mc, Rmixer * rm, VoiceManager * vm, SoundManager *sm)
{
    //[Constructor_pre] You can add your own custom stuff here..

    mainComponent = mc;
    rmixer = rm;
    soundManager = sm;
    voiceManager = vm;

    //[/Constructor_pre]

    juce__groupComponent.reset (new juce::GroupComponent ("new group",
                                                          TRANS("Diagnostics")));
    addAndMakeVisible (juce__groupComponent.get());
    juce__groupComponent->setColour (juce::GroupComponent::outlineColourId, juce::Colour (0xff666666));

    juce__groupComponent->setBounds (37, 244, 728, 109);

    lblAudioFrameAve.reset (new juce::Label ("audio frame ave",
                                             juce::String()));
    addAndMakeVisible (lblAudioFrameAve.get());
    lblAudioFrameAve->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    lblAudioFrameAve->setJustificationType (juce::Justification::centredLeft);
    lblAudioFrameAve->setEditable (false, false, false);
    lblAudioFrameAve->setColour (juce::Label::outlineColourId, juce::Colour (0xff666666));
    lblAudioFrameAve->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    lblAudioFrameAve->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    lblAudioFrameAve->setBounds (665, 272, 62, 24);

    juce__label.reset (new juce::Label ("new label",
                                        TRANS("Audio Frame Ave:")));
    addAndMakeVisible (juce__label.get());
    juce__label->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label->setJustificationType (juce::Justification::centredLeft);
    juce__label->setEditable (false, false, false);
    juce__label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label->setBounds (545, 271, 117, 24);

    lblAudioFrameMax.reset (new juce::Label ("audio frame max",
                                             juce::String()));
    addAndMakeVisible (lblAudioFrameMax.get());
    lblAudioFrameMax->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    lblAudioFrameMax->setJustificationType (juce::Justification::centredLeft);
    lblAudioFrameMax->setEditable (false, false, false);
    lblAudioFrameMax->setColour (juce::Label::outlineColourId, juce::Colour (0xff666666));
    lblAudioFrameMax->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    lblAudioFrameMax->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    lblAudioFrameMax->setBounds (665, 309, 62, 24);

    juce__label2.reset (new juce::Label ("new label",
                                         TRANS("Audio Frame Max:")));
    addAndMakeVisible (juce__label2.get());
    juce__label2->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label2->setJustificationType (juce::Justification::centredLeft);
    juce__label2->setEditable (false, false, false);
    juce__label2->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label2->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label2->setBounds (542, 307, 120, 24);

    lblActiveVoices.reset (new juce::Label ("active voices",
                                            juce::String()));
    addAndMakeVisible (lblActiveVoices.get());
    lblActiveVoices->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    lblActiveVoices->setJustificationType (juce::Justification::centredLeft);
    lblActiveVoices->setEditable (false, false, false);
    lblActiveVoices->setColour (juce::Label::outlineColourId, juce::Colour (0xff666666));
    lblActiveVoices->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    lblActiveVoices->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    lblActiveVoices->setBounds (454, 272, 40, 24);

    juce__label5.reset (new juce::Label ("new label",
                                         TRANS("Active Voices:")));
    addAndMakeVisible (juce__label5.get());
    juce__label5->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label5->setJustificationType (juce::Justification::centredLeft);
    juce__label5->setEditable (false, false, false);
    juce__label5->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label5->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label5->setBounds (356, 271, 98, 24);

    lblAudioUnderruns.reset (new juce::Label ("audio frame ave",
                                              juce::String()));
    addAndMakeVisible (lblAudioUnderruns.get());
    lblAudioUnderruns->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    lblAudioUnderruns->setJustificationType (juce::Justification::centredLeft);
    lblAudioUnderruns->setEditable (false, false, false);
    lblAudioUnderruns->setColour (juce::Label::outlineColourId, juce::Colour (0xff666666));
    lblAudioUnderruns->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    lblAudioUnderruns->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    lblAudioUnderruns->setBounds (454, 308, 62, 24);

    juce__label7.reset (new juce::Label ("new label",
                                         TRANS("Underruns:")));
    addAndMakeVisible (juce__label7.get());
    juce__label7->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label7->setJustificationType (juce::Justification::centredLeft);
    juce__label7->setEditable (false, false, false);
    juce__label7->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label7->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label7->setBounds (373, 307, 84, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    mainComponent->addChangeListener(this);
    rmixer->clearChangePending();
    rmixer->addChangeListener(this);
    rmixer->setStatsEnabled(true);
    startTimer(100);
    //[/Constructor]
}

Interface::~Interface()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    mainComponent->removeChangeListener(this);
    rmixer->removeChangeListener(this);
    //[/Destructor_pre]

    juce__groupComponent = nullptr;
    lblAudioFrameAve = nullptr;
    juce__label = nullptr;
    lblAudioFrameMax = nullptr;
    juce__label2 = nullptr;
    lblActiveVoices = nullptr;
    juce__label5 = nullptr;
    lblAudioUnderruns = nullptr;
    juce__label7 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Interface::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colours::black);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Interface::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...


// ***************************************************************************
void Interface::changeListenerCallback(ChangeBroadcaster *)
{

MIXER_STATS_STRUCTURE mStats;

	if (rmixer->getChangePending()) {
        rmixer->getStats(&mStats);
        lblAudioFrameAve->setText(String(mStats.frameMsAve, 3), dontSendNotification);
        lblAudioFrameMax->setText(String(mStats.frameMsMax, 3), dontSendNotification);
        lblAudioUnderruns->setText(String(mStats.underruns), dontSendNotification);
		rmixer->clearChangePending();
		lblActiveVoices->setText(String(voiceManager->getActiveVoices()), dontSendNotification);
	}
    if (mainComponent->getChangePending()) {
        mainComponent->clearChangePending();
    }
}

// ******************************************************************
//  timerCallback
// ******************************************************************
void Interface::timerCallback()
{
    rmixer->requestStats();
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Interface" componentName=""
                 parentClasses="public juce::Component, public juce::Timer, public juce::ChangeListener"
                 constructorParams="MainComponent * mc, Rmixer * rm, VoiceManager * vm, SoundManager *sm"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff000000"/>
  <GROUPCOMPONENT name="new group" id="341acc9ffaa48110" memberName="juce__groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="37 244 728 109" outlinecol="ff666666"
                  title="Diagnostics"/>
  <LABEL name="audio frame ave" id="fd0c6141b7b821bf" memberName="lblAudioFrameAve"
         virtualName="" explicitFocusOrder="0" pos="665 272 62 24" outlineCol="ff666666"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="adc90cf19a11cc49" memberName="juce__label"
         virtualName="" explicitFocusOrder="0" pos="545 271 117 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Audio Frame Ave:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="audio frame max" id="affb2329a271f731" memberName="lblAudioFrameMax"
         virtualName="" explicitFocusOrder="0" pos="665 309 62 24" outlineCol="ff666666"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="bd2321cfd08f290e" memberName="juce__label2"
         virtualName="" explicitFocusOrder="0" pos="542 307 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Audio Frame Max:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="active voices" id="35dd4980b917c363" memberName="lblActiveVoices"
         virtualName="" explicitFocusOrder="0" pos="454 272 40 24" outlineCol="ff666666"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="615bc6c8951e7b79" memberName="juce__label5"
         virtualName="" explicitFocusOrder="0" pos="356 271 98 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Active Voices:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="audio frame ave" id="e8f8b1e65398c568" memberName="lblAudioUnderruns"
         virtualName="" explicitFocusOrder="0" pos="454 308 62 24" outlineCol="ff666666"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="167f86cf89f6212c" memberName="juce__label7"
         virtualName="" explicitFocusOrder="0" pos="373 307 84 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Underruns:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

