/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "XYPad.h"

//==============================================================================
/**
*/
class XYPadAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    XYPadAudioProcessorEditor (XYPadAudioProcessor&);
    ~XYPadAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    XYPadAudioProcessor& audioProcessor;

    using APVTS = juce::AudioProcessorValueTreeState;
    using SliderAttachment = APVTS::SliderAttachment;

    juce::Slider gainSlider{ juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::TextBoxBelow };
    juce::Slider panSlider{ juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::TextBoxBelow };

    SliderAttachment gainAttachment, panAttachment;
    juce::Label gainLabel{ "gainLabel", "Gain" };
    juce::Label panLabel{ "panLabel", "Pan" };

    XYPad xyPad;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (XYPadAudioProcessorEditor)
};
