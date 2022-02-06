
#pragma once

#include <JuceHeader.h>
#include "Rmixer.h"
#include "VoiceManager.h"
#include "SoundManager.h"
#include "LevelMeter.h"

class MainComponent;

class Interface  : public juce::Component,
                   public juce::Timer,
                   public juce::ChangeListener,
                   public juce::Button::Listener
{
public:

    Interface (MainComponent * mc, Rmixer * rm, VoiceManager * vm, SoundManager *sm);
    ~Interface() override;

	void changeListenerCallback(ChangeBroadcaster *) override;
    void timerCallback() override;

    void paint (juce::Graphics& g) override;
    void resized() override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;

private:

    const float meter_left{ 100.0f };
    const float meter_top{ 50.0f };
    const float meter_width{ 20.0f };
    const float meter_height{ 222.0f };
    const float meter_spacing{ 86.0f };
    const float meter_ticks{ 6.0f };
    const int num_meters{ 8 };

    Rmixer * rmixer;
    MainComponent * mainComponent;
    VoiceManager * voiceManager;
    SoundManager * soundManager;

    VerticalMeter verticalMeter[8];
    std::unique_ptr<juce::Label> meterLabel[8];

    std::unique_ptr<juce::GroupComponent> juce__groupComponent;
    std::unique_ptr<juce::Label> lblAudioFrameAve;
    std::unique_ptr<juce::Label> juce__label;
    std::unique_ptr<juce::Label> lblAudioFrameMax;
    std::unique_ptr<juce::Label> juce__label2;
    std::unique_ptr<juce::Label> lblActiveVoices;
    std::unique_ptr<juce::Label> juce__label1;
    std::unique_ptr<juce::Label> lblAudioUnderruns;
    std::unique_ptr<juce::Label> juce__label5;
    std::unique_ptr<juce::Label> lblAudioIntAve;
    std::unique_ptr<juce::Label> juce__label3;
    std::unique_ptr<juce::Label> lblAudioIntMax;
    std::unique_ptr<juce::Label> juce__label4;
    std::unique_ptr<juce::TextButton> btnReset;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Interface)
};
