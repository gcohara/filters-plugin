/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class FiltersAudioProcessorEditor  : public juce::AudioProcessorEditor,
private juce::Slider::Listener
{
public:
    FiltersAudioProcessorEditor (FiltersAudioProcessor&);
    ~FiltersAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void sliderValueChanged(juce::Slider* slider) override;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FiltersAudioProcessor& audioProcessor;
    
    juce::Label cutoffLabel;
    juce::Slider cutoffFreqKnob;
    
    juce::Label resonanceLabel;
    juce::Slider resonanceKnob;
    
    juce::Label blendLabel;
    juce::Slider blendKnob;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FiltersAudioProcessorEditor)
};
