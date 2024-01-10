/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WaveformVisualiserAudioProcessorEditor::WaveformVisualiserAudioProcessorEditor (WaveformVisualiserAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    addAndMakeVisible(audioProcessor.waveViewer);
    audioProcessor.waveViewer.setColours(juce::Colours::black, juce::Colours::white);

    setSize (800, 600);
}

WaveformVisualiserAudioProcessorEditor::~WaveformVisualiserAudioProcessorEditor()
{
}

//==============================================================================
void WaveformVisualiserAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void WaveformVisualiserAudioProcessorEditor::resized()
{
    audioProcessor.waveViewer.setBounds(getLocalBounds());
    //audioProcessor.waveViewer.setBounds(getLocalBounds().withSizeKeepingCentre(getWidth() * 0.5, getHeight() * 0.5));
}
