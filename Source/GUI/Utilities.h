/*
  ==============================================================================

    Utilities.h
    Created: 13 May 2024 4:52:38pm
    Author:  Marc Woodbury-Smith

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#define MIN_FREQUENCY 20.f
#define MAX_FREQUENCY 20000.f

#define NEGATIVE_INFINITY -72.f

#define MAX_DECIBELS 12.f

#define MIN_THRESHOLD -60.f


enum FFTOrder
{
    order2048 = 11,
    order4096 = 12,
    order8192 = 13
};



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


template<typename T>
bool truncateKiloValue(T& value)
{
    if( value > static_cast<T>(999) )
    {
        value /= static_cast<T>(1000);
        return true;
    }
    
    return false;
}






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


//void drawModuleBackground(juce::Graphics& g,
//                          juce::Rectangle<int> bounds);;

juce::Rectangle<int> drawModuleBackground(juce::Graphics& g,
                                          juce::Rectangle<int> bounds);
