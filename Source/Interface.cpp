
#include "MainComponent.h"
#include "Interface.h"

//==============================================================================
Interface::Interface (MainComponent * mc, Rmixer * rm, VoiceManager * vm, SoundManager *sm)
{

int row1 = 336;
int row2 = 374;

    mainComponent = mc;
    rmixer = rm;
    soundManager = sm;
    voiceManager = vm;

    for (int m = 0; m < 8; m++) {
        addAndMakeVisible(verticalMeter[m]);
        meterLabel[m].reset (new juce::Label ("meter label", TRANS("Out 1")));
        addAndMakeVisible (meterLabel[m].get());
        meterLabel[m]->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    }

    juce__groupComponent.reset (new juce::GroupComponent ("new group",
                                                          TRANS("Diagnostics")));
    addAndMakeVisible (juce__groupComponent.get());
    juce__groupComponent->setColour (juce::GroupComponent::outlineColourId, juce::Colours::skyblue);
    juce__groupComponent->setBounds (37, 310, 728, 109);

    lblAudioFrameAve.reset (new juce::Label ("audio frame ave",
                                             juce::String()));
    addAndMakeVisible (lblAudioFrameAve.get());
    lblAudioFrameAve->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    lblAudioFrameAve->setJustificationType (juce::Justification::centredLeft);
    lblAudioFrameAve->setEditable (false, false, false);
    lblAudioFrameAve->setColour (juce::Label::outlineColourId, juce::Colours::black);
    lblAudioFrameAve->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    lblAudioFrameAve->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));
    lblAudioFrameAve->setBounds (665, row1, 62, 24);

    juce__label.reset (new juce::Label ("new label",
                                        TRANS("Audio Frame Ave:")));
    addAndMakeVisible (juce__label.get());
    juce__label->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label->setJustificationType (juce::Justification::centredLeft);
    juce__label->setEditable (false, false, false);
    juce__label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));
    juce__label->setBounds (545, row1, 117, 24);

    lblAudioFrameMax.reset (new juce::Label ("audio frame max",
                                             juce::String()));
    addAndMakeVisible (lblAudioFrameMax.get());
    lblAudioFrameMax->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    lblAudioFrameMax->setJustificationType (juce::Justification::centredLeft);
    lblAudioFrameMax->setEditable (false, false, false);
    lblAudioFrameMax->setColour (juce::Label::outlineColourId, juce::Colours::black);
    lblAudioFrameMax->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    lblAudioFrameMax->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));
    lblAudioFrameMax->setBounds (665, row2, 62, 24);

    juce__label2.reset (new juce::Label ("new label",
                                         TRANS("Audio Frame Max:")));
    addAndMakeVisible (juce__label2.get());
    juce__label2->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label2->setJustificationType (juce::Justification::centredLeft);
    juce__label2->setEditable (false, false, false);
    juce__label2->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label2->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));
    juce__label2->setBounds (542, row2, 120, 24);

    lblActiveVoices.reset (new juce::Label ("active voices",
                                            juce::String()));
    addAndMakeVisible (lblActiveVoices.get());
    lblActiveVoices->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    lblActiveVoices->setJustificationType (juce::Justification::centredLeft);
    lblActiveVoices->setEditable (false, false, false);
    lblActiveVoices->setColour (juce::Label::outlineColourId, juce::Colours::black);
    lblActiveVoices->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    lblActiveVoices->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));
    lblActiveVoices->setBounds (259, row1, 40, 24);

    juce__label1.reset (new juce::Label ("new label",
                                         TRANS("Active Voices:")));
    addAndMakeVisible (juce__label1.get());
    juce__label1->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label1->setJustificationType (juce::Justification::centredLeft);
    juce__label1->setEditable (false, false, false);
    juce__label1->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label1->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));
    juce__label1->setBounds (161, row1, 98, 24);

    lblAudioUnderruns.reset (new juce::Label ("audio frame ave",
                                              juce::String()));
    addAndMakeVisible (lblAudioUnderruns.get());
    lblAudioUnderruns->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    lblAudioUnderruns->setJustificationType (juce::Justification::centredLeft);
    lblAudioUnderruns->setEditable (false, false, false);
    lblAudioUnderruns->setColour (juce::Label::outlineColourId, juce::Colours::black);
    lblAudioUnderruns->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    lblAudioUnderruns->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));
    lblAudioUnderruns->setBounds (259, row2, 62, 24);

    juce__label5.reset (new juce::Label ("new label",
                                         TRANS("Underruns:")));
    addAndMakeVisible (juce__label5.get());
    juce__label5->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label5->setJustificationType (juce::Justification::centredLeft);
    juce__label5->setEditable (false, false, false);
    juce__label5->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label5->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));
    juce__label5->setBounds (178, row2, 84, 24);

    lblAudioIntAve.reset (new juce::Label ("audio interval ave",
                                           juce::String()));
    addAndMakeVisible (lblAudioIntAve.get());
    lblAudioIntAve->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    lblAudioIntAve->setJustificationType (juce::Justification::centredLeft);
    lblAudioIntAve->setEditable (false, false, false);
    lblAudioIntAve->setColour (juce::Label::outlineColourId, juce::Colours::black);
    lblAudioIntAve->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    lblAudioIntAve->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));
    lblAudioIntAve->setBounds (467, row1, 62, 24);

    juce__label3.reset (new juce::Label ("new label",
                                         TRANS("Audio Interval Ave:")));
    addAndMakeVisible (juce__label3.get());
    juce__label3->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label3->setJustificationType (juce::Justification::centredLeft);
    juce__label3->setEditable (false, false, false);
    juce__label3->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label3->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));
    juce__label3->setBounds (341, row1, 128, 24);

    lblAudioIntMax.reset (new juce::Label ("audio interval max",
                                           juce::String()));
    addAndMakeVisible (lblAudioIntMax.get());
    lblAudioIntMax->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    lblAudioIntMax->setJustificationType (juce::Justification::centredLeft);
    lblAudioIntMax->setEditable (false, false, false);
    lblAudioIntMax->setColour (juce::Label::outlineColourId, juce::Colours::black);
    lblAudioIntMax->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    lblAudioIntMax->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));
    lblAudioIntMax->setBounds (467, row2, 62, 24);

    juce__label4.reset (new juce::Label ("new label",
                                         TRANS("Audio Interval Max:")));
    addAndMakeVisible (juce__label4.get());
    juce__label4->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    juce__label4->setJustificationType (juce::Justification::centredLeft);
    juce__label4->setEditable (false, false, false);
    juce__label4->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label4->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));
    juce__label4->setBounds (338, row2, 128, 24);

    btnReset.reset (new juce::TextButton ("reset button"));
    addAndMakeVisible (btnReset.get());
    btnReset->setButtonText (TRANS("Reset"));
    btnReset->addListener (this);
    btnReset->setBounds (72, row2, 63, 24);

    setSize (600, 400);

    mainComponent->addChangeListener(this);
    rmixer->clearChangePending();
    rmixer->addChangeListener(this);
    rmixer->setStatsEnabled(true);
    startTimerHz(24);
}

Interface::~Interface()
{
    mainComponent->removeChangeListener(this);
    rmixer->removeChangeListener(this);

    juce__groupComponent = nullptr;
    lblAudioFrameAve = nullptr;
    juce__label = nullptr;
    lblAudioFrameMax = nullptr;
    juce__label2 = nullptr;
    lblActiveVoices = nullptr;
    juce__label1 = nullptr;
    lblAudioUnderruns = nullptr;
    juce__label5 = nullptr;
    lblAudioIntAve = nullptr;
    juce__label3 = nullptr;
    lblAudioIntMax = nullptr;
    juce__label4 = nullptr;
    btnReset = nullptr;

    for (int m = 0; m < 8; m++)
        meterLabel[m] = nullptr;
}

//==============================================================================
void Interface::paint (juce::Graphics& g)
{

float v, vs;

    String c("Chan ");

    g.fillAll (Colours::black);

    g.setColour(Colour(0xffa2a2a2));
    vs = (meter_height / meter_ticks);
    float f = meter_left - 10.0f;

    for (int m = 0; m < num_meters; m++) {
        v = meter_top;
        for (int t = 0; t < meter_ticks; t++) {
            g.drawHorizontalLine(v, f, f + 10.0f);
            g.drawHorizontalLine(v + (vs / 2.0f), f + 5.0f, f + 10.0f);
            v += vs;
        }
        v -= 1.0f;
        g.drawHorizontalLine(v, f, f + 10.0f);
        g.setFont(11.0f);
        v = meter_top + 3.0f;
        g.drawSingleLineText("0", f - 4.0f, v, Justification::right);
        v += vs;
        g.drawSingleLineText("-10", f - 4.0f, v, Justification::right);
        v += vs;
        g.drawSingleLineText("-20", f - 4.0f, v, Justification::right);
        v += vs;
        g.drawSingleLineText("-30", f - 4.0f, v, Justification::right);
        v += vs;
        g.drawSingleLineText("-40", f - 4.0f, v, Justification::right);
        v += vs;
        g.drawSingleLineText("-50", f - 4.0f, v, Justification::right);
        v += vs;
        g.drawSingleLineText("-60", f - 4.0f, v, Justification::right);

        g.drawSingleLineText(c + String(m + 1), f - 2.0f, v + 20.0f, Justification::left);
        f += meter_spacing;
    }
}

void Interface::resized()
{
    for (int m = 0; m < 8; m++) {
        verticalMeter[m].setBounds(meter_left + (m *meter_spacing), meter_top, meter_width, meter_height);
    }
}

void Interface::buttonClicked (juce::Button* buttonThatWasClicked)
{

    if (buttonThatWasClicked == btnReset.get())
    {
        rmixer->resetStats();
    }
}

// ***************************************************************************
void Interface::changeListenerCallback(ChangeBroadcaster *)
{

MIXER_STATS_STRUCTURE mStats;

	if (rmixer->getChangePending()) {
        rmixer->getStats(&mStats);
        lblAudioIntAve->setText(String(mStats.intervalMsAve, 3), dontSendNotification);
        lblAudioIntMax->setText(String(mStats.intervalMsMax, 3), dontSendNotification);
        lblAudioFrameAve->setText(String(mStats.frameMsAve, 3), dontSendNotification);
        lblAudioFrameMax->setText(String(mStats.frameMsMax, 3), dontSendNotification);
        lblAudioUnderruns->setText(String(mStats.underruns), dontSendNotification);
		for (int n = 0; n < 8; n++) {
            verticalMeter[n].setLevel(mStats.rmsLevel[n]);
        }
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

