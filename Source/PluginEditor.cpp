/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FiltersAudioProcessorEditor::FiltersAudioProcessorEditor (FiltersAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 200);
    
    // Set the look of the sliders (i.e as knobs).
    // We can set by moving mouse left to right or up and down
    cutoffFreq.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    resonance.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    // Put the values underneath the knobs
    cutoffFreq.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 20);
    resonance.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 20);
    // Make sliders/knobs visible
    addAndMakeVisible(&cutoffFreq);
    addAndMakeVisible(&resonance);
}

FiltersAudioProcessorEditor::~FiltersAudioProcessorEditor()
{
}

//==============================================================================
void FiltersAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("George's Lovely Filter", getLocalBounds(), juce::Justification::centredTop, 1);
}

void FiltersAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    cutoffFreq.setBounds(220, 20, 180, 180);
    resonance.setBounds(0, 20, 180, 180);
}
