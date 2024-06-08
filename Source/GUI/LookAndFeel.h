/*
  ==============================================================================

    LookAndFeel.h
    Created: 13 May 2024 3:08:57pm
    Author:  Marc Woodbury-Smith

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#define USE_LIVE_CONSTANT false

#if USE_LIVE_CONSTANT
#define colorHelper(c) JUCE_LIVE_CONSTANT(c);
#else
#define colorHelper(c) c;
#endif

namespace ColorScheme
{
inline juce::Colour getSliderBorderColor()
{
    return colorHelper( juce::Colour(0xff00c8ff) );
}

inline juce::Colour getModuleBorderColor()
{
    return colorHelper( juce::Colours::blueviolet );
}
}



struct LookAndFeel : juce::LookAndFeel_V4
{
    void drawRotarySlider (juce::Graphics&,
                           int x, int y, int width, int height,
                           float sliderPosProportional,
                           float rotaryStartAngle,
                           float rotaryEndAngle,
                           juce::Slider&) override;
    
    void drawToggleButton (juce::Graphics &g,
                           juce::ToggleButton & toggleButton,
                           bool shouldDrawButtonAsHighlighted,
                           bool shouldDrawButtonAsDown) override;
};
