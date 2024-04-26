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
 
 struct Placeholder : juce::Component
 {
     Placeholder();
     
     void paint(juce::Graphics& g) override
         {
             g.fillAll(customColor);
         }
     juce::Colour customColor;
     

 };
 
struct GlobalControls : juce::Component
{
    void paint(juce::Graphics& g) override;

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
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleMBCompAudioProcessor& audioProcessor;
    
    Placeholder controlBar, analyzer, /*globalControls,*/ bandControls;
    GlobalControls globalControls;
    
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleMBCompAudioProcessorEditor)
};
