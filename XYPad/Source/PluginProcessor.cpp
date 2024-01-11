/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
XYPadAudioProcessor::XYPadAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

XYPadAudioProcessor::~XYPadAudioProcessor()
{
}

//==============================================================================
const juce::String XYPadAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool XYPadAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool XYPadAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool XYPadAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double XYPadAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int XYPadAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int XYPadAudioProcessor::getCurrentProgram()
{
    return 0;
}

void XYPadAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String XYPadAudioProcessor::getProgramName (int index)
{
    return {};
}

void XYPadAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void XYPadAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    const juce::dsp::ProcessSpec spec{ sampleRate, samplesPerBlock, getTotalNumInputChannels() };
    gainProcessor.prepare(spec);
    panProcessor.prepare(spec);

    gainProcessor.setGainDecibels(*apvts.getRawParameterValue("Gain"));
    panProcessor.setPan(*apvts.getRawParameterValue("Pan"));
}

void XYPadAudioProcessor::releaseResources()
{
    gainProcessor.reset();
    panProcessor.reset();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool XYPadAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void XYPadAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    
    gainProcessor.setGainDecibels(*apvts.getRawParameterValue("Gain"));
    panProcessor.setPan(*apvts.getRawParameterValue("Pan"));

    juce::dsp::AudioBlock<float> audioBlock{ buffer };
    juce::dsp::ProcessContextReplacing<float> context{ audioBlock };
    gainProcessor.process(context);
    panProcessor.process(context);
}

//==============================================================================
bool XYPadAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* XYPadAudioProcessor::createEditor()
{
    return new XYPadAudioProcessorEditor (*this);
}

//==============================================================================
void XYPadAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void XYPadAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

juce::AudioProcessorValueTreeState::ParameterLayout XYPadAudioProcessor::createParameterLayout()
{
    APVTS::ParameterLayout layout;

    using namespace juce;

    layout.add(std::make_unique<AudioParameterFloat>(ParameterID{ "Gain", 1 },
        "Gain",
        NormalisableRange<float>(-60.f, 0.f, 0.01f, 1.f), 0.f));
    layout.add(std::make_unique<AudioParameterFloat>(ParameterID{ "Pan", 1 },
        "Pan",
        NormalisableRange<float>(-1.f, 1.f, 0.01f, 1.f), 0.f));

    return layout;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new XYPadAudioProcessor();
}
