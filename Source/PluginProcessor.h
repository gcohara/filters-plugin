/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
double constexpr pi = 3.1415926535;
double constexpr initialCutoff = 10000.0;
double constexpr initialResonance = 1.0;
double constexpr initialBlend = 1.0;
//==============================================================================
/**
*/
class BiQuadFilter {
protected:
    double previousSample, previousPreviousSample, previousOutput, previousPreviousOutput = 0.0;
    // coeffs
    double a_0, a_1, a_2, b_1, b_2;
public:
//    virtual void calculate_coeffs(double cutoff, double resonance, double sample_rate);
    double get_output_sample(double input_sample) {
        double outputSample = (a_0 * input_sample)
                            + (a_1 * previousSample)
                            + (a_2 * previousPreviousSample)
                            - (b_1 * previousOutput)
                            - (b_2 * previousPreviousOutput);
        previousPreviousSample = previousSample;
        previousSample = input_sample;
        previousPreviousOutput = previousOutput;
        previousOutput = outputSample;
        return outputSample;
    };
};

class LPFOrder1 : public BiQuadFilter {
public:
    void calculate_coeffs(double cutoff, double resonance, double sample_rate){
        double theta_c = 2.0 * pi * cutoff / sample_rate;
        double sin_theta_c = sin(theta_c);
        double cos_theta_c = cos(theta_c);
        double gamma = cos_theta_c / (1.0 + sin_theta_c);
        a_0 = (1.0 - gamma) / 2.0;
        a_1 = a_0;
        a_2 = 0.0;
        b_1 = - gamma;
        b_2 = 0.0;
    }
};

class LPFOrder2 : public BiQuadFilter {
public:
    void calculate_coeffs(double cutoff, double resonance, double sample_rate){
        double theta_c = 2.0 * pi * cutoff / sample_rate;
        double d = 1.0 / resonance;
        double sin_theta_c = sin(theta_c);
        double cos_theta_c = cos(theta_c);
        double beta = 0.5 * (1.0 - (d * sin_theta_c/2.0)) / (1.0 + (d * sin_theta_c/2.0));
        double gamma = (0.5 + beta) * cos_theta_c;
        a_0 = (0.5 + beta - gamma) / 2.0;
        a_1 = (0.5 + beta - gamma);
        a_2 = a_0;
        b_1 = - 2.0 * gamma;
        b_2 = 2.0 * beta;
    }
};

class HPFOrder2 : public BiQuadFilter {
public:
    void calculate_coeffs(double cutoff, double resonance, double sample_rate){
        double theta_c = 2.0 * pi * cutoff / sample_rate;
        double d = 1.0 / resonance;
        double sin_theta_c = sin(theta_c);
        double cos_theta_c = cos(theta_c);
        double beta = 0.5 * (1.0 - (d * sin_theta_c/2.0)) / (1.0 + (d * sin_theta_c/2.0));
        double gamma = (0.5 + beta) * cos_theta_c;
        a_0 = (0.5 + beta + gamma) / 2.0;
        a_1 = -(0.5 + beta + gamma);
        a_2 = a_0;
        b_1 = - 2.0 * gamma;
        b_2 = 2.0 * beta;
    }
};

class FiltersAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    // parameters
    float cutoffFrequency;
    float resonance;
    float blend;
    
    //==============================================================================
    FiltersAudioProcessor();
    ~FiltersAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FiltersAudioProcessor)
    LPFOrder2 filter;
};
