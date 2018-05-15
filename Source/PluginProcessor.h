/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "ChorderShifter.h"

//==============================================================================
/**
*/
class ChordShiftMidiPluginAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    ChordShiftMidiPluginAudioProcessor();
    ~ChordShiftMidiPluginAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    void handleMidiBuffer(MidiBuffer &m,state &src,state &tag,int updown);
    void handlenotes(Array<int>&notes, state&src, state &tag,int updown);
    

    AudioParameterChoice *SrcPitchMode;
    AudioParameterChoice *TagPitchMode;
    AudioParameterChoice *SrcIsMajorMode;
    AudioParameterChoice *TagIsMajorMode;
    AudioParameterChoice *SrcStage;
    AudioParameterChoice *TagStage;
    AudioParameterChoice *SrcIsMajorStage;
    AudioParameterChoice *TagIsMajorStage;
    AudioParameterInt *updownOctave;
    state srcstate;    
    state tagstate;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChordShiftMidiPluginAudioProcessor)
};
