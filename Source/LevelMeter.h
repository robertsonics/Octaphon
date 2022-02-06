// **************************************************************************
//     Filename: LevelMeter.h
// Date Created: 1/30/2022
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

//==============================================================================
class VerticalMeter  : public juce::Component {
public:
    VerticalMeter() {

        currentLevel = -60.0f;
    }

    ~VerticalMeter() override {
    }

    void setLevel(float newLevel) {
        targetLevel = newLevel;
        if (targetLevel > currentLevel)
            currentLevel = targetLevel;
        else if ((currentLevel - targetLevel) > 1.5f)
            currentLevel -= 1.5f;
        else
            currentLevel = targetLevel;
        repaint();
    }

    void paint (juce::Graphics& g) override {

        auto bounds = getLocalBounds().toFloat();
        g.setColour(Colour(0xff323232));
        g.fillRect(bounds);
        g.setGradientFill(gradient);
        const auto scaledY = jmap(currentLevel, -60.0f, 6.0f, 0.0f, static_cast<float>(getHeight()));
        g.fillRect(bounds.removeFromBottom(scaledY));
    }

    void resized() override {

        auto bounds = getLocalBounds().toFloat();
        gradient = ColourGradient {
            Colours::deepskyblue,
            bounds.getBottomLeft(),
            Colours::red,
            bounds.getTopLeft(),
            false
        };
        gradient.addColour(0.75, Colours::skyblue);
    }

private:

    ColourGradient gradient;
    float currentLevel;
    float targetLevel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VerticalMeter)
};
