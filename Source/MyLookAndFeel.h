/*
  ==============================================================================

    MyLookAndFeel.h
    Created: 5 Jun 2018 9:13:23am
    Author:  Jamie Desktop Dev

  ==============================================================================
*/

#pragma once
//#pragma warning (disable : 4100)

#include "../JuceLibraryCode/JuceHeader.h"
#include "Config.h"

class MyLookAndFeel : public LookAndFeel_V4
{
public:
	MyLookAndFeel()
	{
        setColour(ComboBox::backgroundColourId, MY_TAB_COLOUR);
        setColour(ComboBox::textColourId, MY_TEXT_COLOUR);
        setColour(ComboBox::outlineColourId, MY_BG_COLOUR);
        setColour(ComboBox::focusedOutlineColourId, MY_BG_COLOUR);
        setColour(TextButton::buttonColourId, MY_BUTTON_COLOUR);
        setColour(TextButton::buttonOnColourId, MY_KNOB_COLOUR);
        setColour(TabbedButtonBar::tabOutlineColourId, MY_BG_COLOUR);
        setColour(TabbedButtonBar::frontOutlineColourId, MY_BG_COLOUR);
        setColour(TextEditor::textColourId, MY_TEXT_COLOUR);
        setColour(TextEditor::backgroundColourId, MY_TAB_COLOUR);
        setColour(TextEditor::outlineColourId, MY_TAB_COLOUR);
        setColour(Label::textColourId, MY_TEXT_COLOUR);
        setColour(GroupComponent::textColourId, MY_TEXT_COLOUR);
	}

	int getTabButtonBestWidth(TabBarButton& button, int tabDepth)
	{
		TabbedButtonBar* bar = button.findParentComponentOfClass<TabbedButtonBar>();
		if (bar && bar->getNumTabs() > 0)
			return bar->getWidth() / bar->getNumTabs() + 10;
		else
			return 50;
	}

	int getSliderThumbRadius(Slider& slider)
	{
		return jmin(20, slider.isHorizontal() ? static_cast<int> (slider.getHeight() * 0.5f)
			: static_cast<int> (slider.getWidth()  * 0.5f));
	}

	void drawLinearSlider(Graphics& g, int x, int y, int width, int height,
		float sliderPos,
		float minSliderPos,
		float maxSliderPos,
		const Slider::SliderStyle style, Slider& slider)
	{
		if (slider.isBar())
		{
			g.setColour(slider.findColour(Slider::trackColourId));
			g.fillRect(slider.isHorizontal() ? Rectangle<float>(static_cast<float> (x), y + 0.5f, sliderPos - x, height - 1.0f)
				: Rectangle<float>(x + 0.5f, sliderPos, width - 1.0f, y + (height - sliderPos)));
		}
		else
		{
			auto isTwoVal = (style == Slider::SliderStyle::TwoValueVertical || style == Slider::SliderStyle::TwoValueHorizontal);
			auto isThreeVal = (style == Slider::SliderStyle::ThreeValueVertical || style == Slider::SliderStyle::ThreeValueHorizontal);

			auto trackWidth = jmin(6.0f, slider.isHorizontal() ? height * 0.25f : width * 0.25f);

			Point<float> startPoint(slider.isHorizontal() ? x : x + width * 0.5f,
				slider.isHorizontal() ? y + height * 0.5f : height + y);

			Point<float> endPoint(slider.isHorizontal() ? width + x : startPoint.x,
				slider.isHorizontal() ? startPoint.y : y);

			Path backgroundTrack;
			backgroundTrack.startNewSubPath(startPoint);
			backgroundTrack.lineTo(endPoint);
			g.setColour(slider.findColour(Slider::backgroundColourId));
			g.strokePath(backgroundTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

			Path valueTrack;
			Point<float> minPoint, maxPoint, thumbPoint;

			if (isTwoVal || isThreeVal)
			{
				minPoint = { slider.isHorizontal() ? minSliderPos : width * 0.5f,
					slider.isHorizontal() ? height * 0.5f : minSliderPos };

				if (isThreeVal)
					thumbPoint = { slider.isHorizontal() ? sliderPos : width * 0.5f,
					slider.isHorizontal() ? height * 0.5f : sliderPos };

				maxPoint = { slider.isHorizontal() ? maxSliderPos : width * 0.5f,
					slider.isHorizontal() ? height * 0.5f : maxSliderPos };
			}
			else
			{
				auto kx = slider.isHorizontal() ? sliderPos : (x + width * 0.5f);
				auto ky = slider.isHorizontal() ? (y + height * 0.5f) : sliderPos;

				minPoint = startPoint;
				maxPoint = { kx, ky };
			}

			auto thumbWidth = getSliderThumbRadius(slider);

			valueTrack.startNewSubPath(minPoint);
			valueTrack.lineTo(isThreeVal ? thumbPoint : maxPoint);
			g.setColour(slider.findColour(Slider::trackColourId));
			g.strokePath(valueTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

			if (!isTwoVal)
			{
				g.setColour(MY_KNOB_COLOUR);
				g.fillEllipse(Rectangle<float>(static_cast<float> (thumbWidth), static_cast<float> (thumbWidth)).withCentre(isThreeVal ? thumbPoint : maxPoint));
			}

			if (isTwoVal || isThreeVal)
			{
				auto sr = jmin(trackWidth, (slider.isHorizontal() ? height : width) * 0.4f);
				auto pointerColour = slider.findColour(Slider::thumbColourId);

				if (slider.isHorizontal())
				{
					drawPointer(g, minSliderPos - sr,
						jmax(0.0f, y + height * 0.5f - trackWidth * 2.0f),
						trackWidth * 2.0f, pointerColour, 2);

					drawPointer(g, maxSliderPos - trackWidth,
						jmin(y + height - trackWidth * 2.0f, y + height * 0.5f),
						trackWidth * 2.0f, pointerColour, 4);
				}
				else
				{
					g.setColour(MY_KNOB_COLOUR);
					g.fillEllipse(((width * 0.5f) - (float)thumbWidth) - (trackWidth * 0.5f), minSliderPos - ((float)thumbWidth * 0.5f), (float)thumbWidth, (float)thumbWidth);

					g.fillEllipse((width * 0.5f) + (trackWidth * 0.52f), maxSliderPos - ((float)thumbWidth * 0.5f), (float)thumbWidth, (float)thumbWidth);

				}
			}
		}
	}

    void drawButtonBackground(Graphics& g, Button& button, const Colour& c, bool isMouseOverButton, bool isButtonDown) {

        g.setColour(c);
        const Rectangle<float> r (button.getLocalBounds().toFloat());
        g.fillRoundedRectangle(r, 10.0f);
    }

    Font getTextButtonFont(TextButton& b, int buttonHeight) {
        return { buttonHeight * 0.5f };
    }

    Font getTabButtonFont(TabBarButton& b, int buttonHeight) {
        return { buttonHeight * 0.34f };
    }

    int getTabButtonOverlap(int tabDepth) {
        return 0;
    }

	//int getSliderThumbRadius(Slider& slider)
	//{
	//	return 80;
	//}

};

