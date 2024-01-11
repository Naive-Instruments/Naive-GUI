/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
XYPadAudioProcessorEditor::XYPadAudioProcessorEditor (XYPadAudioProcessor& p) : 
    AudioProcessorEditor (&p),
    audioProcessor (p),
    gainAttachment(audioProcessor.apvts, "Gain", gainSlider),
    panAttachment(audioProcessor.apvts, "Pan", panSlider)
{
    addAndMakeVisible(gainSlider);
    addAndMakeVisible(panSlider);
    addAndMakeVisible(gainLabel);
    addAndMakeVisible(panLabel);
    addAndMakeVisible(xyPad);

    gainLabel.setJustificationType(juce::Justification::centred);
    panLabel.setJustificationType(juce::Justification::centred);
    gainLabel.attachToComponent(&gainSlider, false);
    panLabel.attachToComponent(&panSlider, false);

    xyPad.registerSlider(&gainSlider, XYPad::Axis::Y);
    xyPad.registerSlider(&panSlider, XYPad::Axis::X);

    setSize (500, 300);
    setResizable(true, true);
}

XYPadAudioProcessorEditor::~XYPadAudioProcessorEditor()
{
    xyPad.deregisterSlider(&gainSlider);
    xyPad.deregisterSlider(&panSlider);
}

//==============================================================================
void XYPadAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void XYPadAudioProcessorEditor::resized()
{
    const auto container = getLocalBounds().reduced(20);
    auto bounds = container;
    gainSlider.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.25f)));
    xyPad.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.5)).reduced(20));
    panSlider.setBounds(bounds);
}
