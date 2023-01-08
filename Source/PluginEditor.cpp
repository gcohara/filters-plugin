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
    setSize (600, 200);
    
    // Set the look of the sliders (i.e as knobs).
    // We can set by moving mouse left to right or up and down
    cutoffFreqKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    resonanceKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    blendKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    // Put the values underneath the knobs
    cutoffFreqKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 20);
    resonanceKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 20);
    blendKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 20);
    // Set range
    cutoffFreqKnob.setRange(20.0, 20000.0);
    blendKnob.setRange(0.0, 1.0);
    resonanceKnob.setRange(0.5, 20.0);
    // Add the listeners to the sliders
    cutoffFreqKnob.addListener(this);
    resonanceKnob.addListener(this);
    blendKnob.addListener(this);
    // Set up labels
    cutoffLabel.setText("Cutoff Freq", juce::dontSendNotification);
    cutoffLabel.attachToComponent(&cutoffFreqKnob, false);
    
    resonanceLabel.setText("Resonance", juce::dontSendNotification);
    resonanceLabel.attachToComponent(&resonanceKnob, false);
    
    blendLabel.setText("Blend", juce::dontSendNotification);
    blendLabel.attachToComponent(&blendKnob, false);
    
    // Make sliders/knobs visible
    addAndMakeVisible(&cutoffFreqKnob);
    addAndMakeVisible(&cutoffLabel);
    addAndMakeVisible(&resonanceKnob);
    addAndMakeVisible(&resonanceLabel);
    addAndMakeVisible(&blendKnob);
    addAndMakeVisible(&blendLabel);
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
    blendKnob.setBounds(440, 20, 180, 180);
    cutoffFreqKnob.setBounds(220, 20, 180, 180);
    resonanceKnob.setBounds(0, 20, 180, 180);
}

void FiltersAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    if (slider == &cutoffFreqKnob) {
        audioProcessor.cutoffFrequency = cutoffFreqKnob.getValue();
    } else if (slider == &resonanceKnob) {
        audioProcessor.resonance = resonanceKnob.getValue();
    } else if (slider == &blendKnob) {
        audioProcessor.blend = blendKnob.getValue();
    }
}

