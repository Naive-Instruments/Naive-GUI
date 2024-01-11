/*
  ==============================================================================

    XYPad.h
    Created: 10 Jan 2024 4:29:25pm
    Author:  TaroPie

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class XYPad  : public juce::Component, juce::Slider::Listener
{
public:
    XYPad();
    
    void paint (juce::Graphics&) override;
    void resized() override;

    class Thumb : public Component
    {
    public:
        Thumb();
        void paint(juce::Graphics& g) override;
        void mouseDown(const juce::MouseEvent& event) override;
        void mouseDrag(const juce::MouseEvent& event) override;
        std::function<void(juce::Point<double>)> moveCallback;
    private:
        juce::ComponentDragger dragger;
        juce::ComponentBoundsConstrainer constrainer;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Thumb)
    };

    enum class Axis { X, Y };

    void registerSlider(juce::Slider* slider, Axis axis);
    void deregisterSlider(juce::Slider* slider);

private:
    void sliderValueChanged(juce::Slider* slider) override;

    std::vector<juce::Slider*> xSliders, ySliders;
    Thumb thumb;
    std::mutex vectorMutex;

    static constexpr int thumbSize = 40;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (XYPad)
};
