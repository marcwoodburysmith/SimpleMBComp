/*
  ==============================================================================

    GlobalControls.cpp
    Created: 13 May 2024 5:05:41pm
    Author:  Marc Woodbury-Smith

  ==============================================================================
*/

#include "GlobalControls.h"
#include "Params.h"
#include "Utilities.h"


GlobalControls::GlobalControls(juce::AudioProcessorValueTreeState& apvts)
{
    using namespace Params;
    const auto& params = GetParams();
    
    auto getParamHelper = [&apvts, &params](const auto& pos) -> auto&
    {
        return getParam(pos, apvts, params);
    };
    
    auto& gainInParam = getParamHelper(Names::Gain_In);
    auto& lowMidParam = getParamHelper(Names::Low_Mid_Crossover_Freq);
    auto& midHighParam = getParamHelper(Names::Mid_High_Crossover_Freq);
    auto& gainOutParam = getParamHelper(Names::Gain_Out);


    
    using RSWL = RotarySliderWithLabels;

    inGainSlider = std::make_unique<RSWL>(&gainInParam,
                                          "dB",
                                          "INPUT TRIM");
    
    lowMidXoverSlider = std::make_unique<RSWL>(&lowMidParam,
                                               "Hz",
                                               "LOW-MID X-OVER");
    
    midHighXoverSlider = std::make_unique<RSWL>(&midHighParam,
                                                "Hz",
                                                "MID-HIGH X-OVER");
    
    outGainSlider = std::make_unique<RSWL>(&gainOutParam,
                                           "dB",
                                           "OUTPUT TRIM");
    
    auto makeAttachmentHelper = [&params, &apvts](auto& attachment, const auto& name, auto& slider)
    {
        makeAttachment(attachment, name, slider, params, apvts);
    };
    
    makeAttachmentHelper(inGainSliderAttachment,
                             Names::Gain_In,
                             *inGainSlider);
        
    makeAttachmentHelper(lowMidXoverSliderAttachment,
                         Names::Low_Mid_Crossover_Freq,
                         *lowMidXoverSlider);
    
    makeAttachmentHelper(midHighXoverSliderAttachment,
                         Names::Mid_High_Crossover_Freq,
                         *midHighXoverSlider);
    
    makeAttachmentHelper(outGainSliderAttachment,
                         Names::Gain_Out,
                         *outGainSlider);
    
    addLabelPairs(lowMidXoverSlider->labels,
                      lowMidParam,
                      "Hz");
    addLabelPairs(midHighXoverSlider->labels,
                  midHighParam,
                  "Hz");
    addLabelPairs(inGainSlider->labels,
                  gainInParam,
                  "dB");
    addLabelPairs(outGainSlider->labels,
                  gainOutParam,
                  "dB");
    
    addAndMakeVisible(*inGainSlider);
    addAndMakeVisible(*lowMidXoverSlider);
    addAndMakeVisible(*midHighXoverSlider);
    addAndMakeVisible(*outGainSlider);
}






void GlobalControls::paint(juce::Graphics &g)
{
    using namespace juce;
    auto bounds = getLocalBounds();
    
//    g.setColour(Colours::blueviolet);
//    g.fillAll();
//
//    auto localBounds = bounds;
//
//    bounds.reduce(3, 3);
//    g.setColour(juce::Colours::black);
//    g.fillRoundedRectangle(bounds.toFloat(), 3);
//
//    g.drawRect(localBounds);
    
    
    drawModuleBackground(g, bounds);
}

void GlobalControls::resized()
{
    auto bounds = getLocalBounds().reduced(5);
    
    using namespace juce;
    FlexBox flexBox;
    flexBox.flexDirection = FlexBox::Direction::row;
    flexBox.flexWrap = FlexBox::Wrap::noWrap;
    
    auto spacer = FlexItem().withWidth(4);
    auto endCap = FlexItem().withWidth(6);
    
    flexBox.items.add(endCap);
    flexBox.items.add(FlexItem(*inGainSlider).withFlex(1.f));
    flexBox.items.add(spacer);
    flexBox.items.add(FlexItem(*lowMidXoverSlider).withFlex(1.f));
    flexBox.items.add(spacer);
    flexBox.items.add(FlexItem(*midHighXoverSlider).withFlex(1.f));
    flexBox.items.add(spacer);
    flexBox.items.add(FlexItem(*outGainSlider).withFlex(1.f));
    flexBox.items.add(endCap);
    
    
    
    flexBox.performLayout(bounds);
} //end GlobalControls::resized()

