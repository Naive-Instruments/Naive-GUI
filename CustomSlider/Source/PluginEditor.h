/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "LinearSlider.h"
#include "RotarySlider.h"

//==============================================================================
/**
*/
class CustomSliderAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    CustomSliderAudioProcessorEditor (CustomSliderAudioProcessor&);
    ~CustomSliderAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    CustomSliderAudioProcessor& audioProcessor;

    RotarySlider rotarySlider;
    LinearSlider linearSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomSliderAudioProcessorEditor)
};
