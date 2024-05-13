/*
  ==============================================================================

    GlobalControls.h
    Created: 13 May 2024 5:05:41pm
    Author:  Marc Woodbury-Smith

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "RotarySliderWithLabels.h"



struct GlobalControls : juce::Component
{
    GlobalControls(juce::AudioProcessorValueTreeState& apvts);
    
    void paint(juce::Graphics& g) override;
    
    void resized() override;
    
private:
    //RotarySlider inGainSlider, lowMidXoverSlider, midHighXoverSlider, outGainSlider;
    std::unique_ptr<RotarySliderWithLabels> inGainSlider, lowMidXoverSlider, midHighXoverSlider, outGainSlider;
    
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<Attachment> lowMidXoverSliderAttachment, midHighXoverSliderAttachment, inGainSliderAttachment, outGainSliderAttachment;
    

};
