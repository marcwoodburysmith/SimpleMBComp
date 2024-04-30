/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

/*
 ROADMAP:

 1. Global Controls (xover sliders, gain sliders).
 These are going to go in the middle of the display.
 Input gain on the left, output gain on the right.

 2. Main Band control (attack, release, threshold, ratio).
 These will go below the global controls.
 The controls will be assigned to the Mid band at first.

 3. Add Solo/Mute/Bypass buttons.
 Again, assigned to the mid-band first.

 4. Band Select functionality (resettable parameter attachments).
 This will allow us to have one set of controls for all bands, and some buttons to switch which band the controls are targetting.
 We'll be reusing the band controls, so we'll need to have a mechanism to change which parameter a control is assigned to.
 It'll be fun to implement.

 5. Band Select Buttons reflect Solo/Mute/Bypass State when switching bands.
 This is to give some visual feedback when we click any of these buttons.
 We also need to implement logic so that you can't have both the mute and solo button toggled on at the same time, for example.

 6. Custom Look And Feel for rotary sliders and toggle buttons.
 We will be modifying the look and feel that we developed from the SimpleEQ tutorial.
 If you haven't completed that tutorial, I will include links where you can download the source code, which we will be modifying.

 7. Spectrum Analyzer overview.
 The spectrum analyzer in this project is slightly different than the one in the SimpleEQ.
 I'll go into detail about what is different.

 8. Data structures for Spectrum Analyzer (copied).
 We'll grab these from the SimpleEQ tutorial.

 9. Fifo usage in pluginProcessor::processBlock().
 A little bit of DSP modification is needed here.

 10. Implementation of analyzer rendering pre-computed paths.
 Again, taken from SimpleEQ.
 The SimpleEQ analyzer took a decent chunk of time to develop in the video.
 There is nothing gained if I duplicate that same chunk in this video.
 I will include links to the relevant code that we will be copying and reusing.

 11. Drawing Crossovers on top of analyzer plot.
 This is where we will customize the Spectrum Analyzer.

 12. Drawing thresholds on top of analyzer plot.
 Another customization of the Spectrum Analyzer.

 13. Drawing gain reduction on top of analyzer plot.
 And the final customization.
 We'll need to write a little bit of DSP code to make this happen.

 14. Analyzer bypass.
 We'll use the same button code from the SimpleEQ tutorial.

 15. Global bypass button.
 Finally, a global bypass button is something that every plugin should have.

  That'll wrap up the GUI! */

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

struct RotarySliderWithLabels : juce::Slider
{
    RotarySliderWithLabels(juce::RangedAudioParameter* rap, const juce::String& unitSuffix,
                           const juce::String& title /*= "NO TITLE" */) :
    juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
                 juce::Slider::TextEntryBoxPosition::NoTextBox),
    param(rap),
    suffix(unitSuffix)
    {
        setName(title);
        //setLookAndFeel(&lnf);
    }
    
//    ~RotarySliderWithLabels()
//    {
//        setLookAndFeel(nullptr);
//    }
    
    struct LabelPos
    {
        float pos;
        juce::String label;
    };
    
    juce::Array<LabelPos> labels;
    
    void paint(juce::Graphics& g) override;
    juce::Rectangle<int> getSliderBounds() const;
    int getTextHeight() const { return 14; }
    virtual juce::String getDisplayString() const;
    
    void changeParam(juce::RangedAudioParameter* p);

    //LookAndFeel lnf;
protected:
    
    juce::RangedAudioParameter* param;
    juce::String suffix;
    
private:
    
};

struct RatioSlider : RotarySliderWithLabels
{
    RatioSlider(juce::RangedAudioParameter* rap, const juce::String& unitSuffix) : RotarySliderWithLabels(rap, unitSuffix, "RATIO") {}
    
    juce::String getDisplayString() const override;
};
    

struct PowerButton : juce::ToggleButton { };

struct AnalyzerButton : juce::ToggleButton
{
    void resized() override
    {
        auto bounds = getLocalBounds();
        auto insetRect = bounds.reduced(4);
        
        randomPath.clear();
        
        juce::Random r;
        
        randomPath.startNewSubPath(insetRect.getX(),
                                   insetRect.getY() + insetRect.getHeight() * r.nextFloat());
        
        for( auto x = insetRect.getX() + 1; x < insetRect.getRight(); x += 2 )
        {
            randomPath.lineTo(x,
                              insetRect.getY() + insetRect.getHeight() * r.nextFloat());
        }
    }
    
    juce::Path randomPath;
};

//==============================================================================

struct RotarySlider : juce::Slider
{
    RotarySlider() :
    juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
                 juce::Slider::TextEntryBoxPosition::NoTextBox)
    { }
};
 

//==============================================================================

template<
    typename Attachment,
    typename ParamName,
    typename SliderType,
    typename Params,
    typename APVTS
        >
void makeAttachment(std::unique_ptr<Attachment>& attachment,
                    ParamName name,
                    SliderType& slider,
                    Params& params,
                    APVTS& apvts)
{
    attachment = std::make_unique<Attachment>(apvts,
                                              params.at(name),
                                              slider);
}


template<
    typename Name,
    typename APVTS,
    typename Params
        >
juce::RangedAudioParameter& getParam(const Name& pos, APVTS& apvts, const Params& params)
{
    auto param = apvts.getParameter(params.at(pos));
    
    jassert(param != nullptr);
    
    return *param;
}

juce::String getValString(const juce::RangedAudioParameter& param, bool getLow, juce::String suffix);

template<
    typename Labels,
    typename ParamType,
    typename SuffixType
        >
void addLabelPairs(Labels& labels, const ParamType& param, const SuffixType& suffix)
{
    labels.clear();
    labels.add({0.f,
        getValString(param, true, suffix)});
    labels.add({1.f, getValString(param, false, suffix)});
}
    
    

//==============================================================================



 struct Placeholder : juce::Component
 {
     Placeholder();
     
     void paint(juce::Graphics& g) override
         {
             g.fillAll(customColor);
         }
     juce::Colour customColor;
     

 };


struct CompressorBandControls : juce::Component
{
    CompressorBandControls(juce::AudioProcessorValueTreeState& apvts);
    void resized() override;
    
    void paint(juce::Graphics& g) override;
    
    juce::AudioProcessorValueTreeState& apvts;
private:
    RotarySliderWithLabels attackSlider, releaseSlider, thresholdSlider /*ratioSlider*/;
    RatioSlider ratioSlider;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attackSliderAttachment, releaseSliderAttachment, thresholdSliderAttachment, ratioSliderAttachment;
    

};


 
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

 
//==============================================================================
/**
*/
class SimpleMBCompAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SimpleMBCompAudioProcessorEditor (SimpleMBCompAudioProcessor&);
    ~SimpleMBCompAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    LookAndFeel lnf; 
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleMBCompAudioProcessor& audioProcessor;
    
    Placeholder controlBar, analyzer /*globalControls,*/ /*bandControls*/;
    GlobalControls globalControls {audioProcessor.apvts};
    CompressorBandControls bandControls {audioProcessor.apvts};
    
    
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleMBCompAudioProcessorEditor)
};
