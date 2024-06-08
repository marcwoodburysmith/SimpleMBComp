/*
  ==============================================================================

    CompressorBandControls.h
    Created: 13 May 2024 5:00:44pm
    Author:  Marc Woodbury-Smith

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "RotarySliderWithLabels.h"



struct CompressorBandControls : juce::Component, juce::Button::Listener
{
    CompressorBandControls(juce::AudioProcessorValueTreeState& apvts);
    ~CompressorBandControls() override;
    void resized() override;
    
    void paint(juce::Graphics& g) override;
    
    void buttonClicked(juce::Button* button) override;
    
    void toggleAllBands(bool shouldBeBypassed);
    
    juce::AudioProcessorValueTreeState& apvts;
private:
    RotarySliderWithLabels attackSlider, releaseSlider, thresholdSlider /*ratioSlider*/;
    RatioSlider ratioSlider;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attackSliderAttachment, releaseSliderAttachment, thresholdSliderAttachment, ratioSliderAttachment;
    
    juce::ToggleButton bypassButton, soloButton, muteButton, lowBand, midBand, highBand;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bypassButtonAttachment, soloButtonAttachment, muteButtonAttachment;
    
    juce::Component::SafePointer<CompressorBandControls> safePtr { this };
    
    juce::ToggleButton* activeBand = &lowBand;
    
    
    void updateAttachments();
    
    void updateSliderEnablements();
    
    void updateSoloMuteBypassToggleStates(juce::Button& clickedButton);
    
    void updateActiveBandFillColors(juce::Button &clickedButton);
    
    void resetActiveBandColors();
    
    
    static void refreshBandButtonColors(juce::Button& band, juce::Button& colorSource);
    
    void updateBandSelectButtonStates();
    

};
