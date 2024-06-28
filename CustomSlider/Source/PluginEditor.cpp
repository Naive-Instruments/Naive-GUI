/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CustomSliderAudioProcessorEditor::CustomSliderAudioProcessorEditor (CustomSliderAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    addAndMakeVisible(linearSlider);
    addAndMakeVisible(rotarySlider);
}

CustomSliderAudioProcessorEditor::~CustomSliderAudioProcessorEditor()
{
}

//==============================================================================
void CustomSliderAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void CustomSliderAudioProcessorEditor::resized()
{
    linearSlider.setBounds(10, 10, getWidth() - 20, 20);
    rotarySlider.setBounds(10, 40, 80, 80);
}
