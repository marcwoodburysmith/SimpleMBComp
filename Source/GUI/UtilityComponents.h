/*
  ==============================================================================

    UtilityComponents.h
    Created: 13 May 2024 3:33:36pm
    Author:  Marc Woodbury-Smith

  ==============================================================================
*/

#pragma once
#include<JuceHeader.h>


struct RotarySlider : juce::Slider
{
    RotarySlider();
};


struct Placeholder : juce::Component
{
    Placeholder();
    
    void paint(juce::Graphics& g) override
        {
            g.fillAll(customColor);
        }
    juce::Colour customColor;
    

};
