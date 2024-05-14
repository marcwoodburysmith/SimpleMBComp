/*
  ==============================================================================

    CustomButtons.h
    Created: 13 May 2024 3:27:14pm
    Author:  Marc Woodbury-Smith

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

struct PowerButton : juce::ToggleButton { };

struct AnalyzerButton : juce::ToggleButton
{
    
    void resized() override;
    
    juce::Path randomPath;
};

