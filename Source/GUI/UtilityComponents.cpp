/*
  ==============================================================================

    UtilityComponents.cpp
    Created: 13 May 2024 3:33:36pm
    Author:  Marc Woodbury-Smith

  ==============================================================================
*/

#include "UtilityComponents.h"


Placeholder::Placeholder()
{
    juce::Random r;
    customColor = juce::Colour(r.nextInt(255), r.nextInt(255), r.nextInt(255));
}


RotarySlider :: RotarySlider() : juce::Slider
(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
                 juce::Slider::TextEntryBoxPosition::NoTextBox)
{ }

