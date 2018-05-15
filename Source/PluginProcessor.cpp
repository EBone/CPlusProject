/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"



//==============================================================================
ChordShiftMidiPluginAudioProcessor::ChordShiftMidiPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    addParameter(SrcPitchMode = new AudioParameterChoice("srcpitchmode", "SrcPithMode",ModNumNames,0));
    addParameter(TagPitchMode = new AudioParameterChoice("tagpitchmode", "TagPithMode",ModNumNames,0));
    addParameter(SrcIsMajorMode = new AudioParameterChoice("srcismajormode", "SrcIsMajorMode",ModeMajMin,1));
    addParameter(TagIsMajorMode = new AudioParameterChoice("tagismajormode", "TagIsMajorMode",ModeMajMin,1));
    addParameter(SrcStage = new AudioParameterChoice("srcstage", "Srcstage",StageNames,0));
    addParameter(TagStage = new AudioParameterChoice("tagstage", "TagStage", StageNames,0));
    addParameter(SrcIsMajorStage = new AudioParameterChoice("srcismajorstage", "SrcIsMajorStage",StageMajMin,1));
    addParameter(TagIsMajorStage = new AudioParameterChoice("tagismajorstage", "TagIsMajorStage",StageMajMin,1));
    addParameter(updownOctave = new AudioParameterInt("updownoctave", "UpDownOctave", -6, 6, 0));
}

ChordShiftMidiPluginAudioProcessor::~ChordShiftMidiPluginAudioProcessor()
{

}

//==============================================================================
const String ChordShiftMidiPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ChordShiftMidiPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ChordShiftMidiPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double ChordShiftMidiPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ChordShiftMidiPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ChordShiftMidiPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ChordShiftMidiPluginAudioProcessor::setCurrentProgram (int)
{
}

const String ChordShiftMidiPluginAudioProcessor::getProgramName (int)
{
    return {};
}

void ChordShiftMidiPluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void ChordShiftMidiPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    srcstate=
    {
        ModeNum(SrcPitchMode->getIndex()),
            MajstageNum(SrcStage->getIndex()),
            bool(SrcIsMajorMode->getIndex()),
            bool(SrcIsMajorStage->getIndex())
    };
    tagstate=
    {
        ModeNum(TagPitchMode->getIndex()),
        MajstageNum(TagStage->getIndex()),
        bool(TagIsMajorMode->getIndex()),
        bool(TagIsMajorStage->getIndex())
    };

}

void ChordShiftMidiPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ChordShiftMidiPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void ChordShiftMidiPluginAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
  
    
    srcstate.mode = ModeNum(SrcPitchMode->getIndex());
    srcstate.stage = MajstageNum(SrcStage->getIndex());
    srcstate.ModisMaj = bool(SrcIsMajorMode->getIndex());
    srcstate.stageisMaj = bool(SrcIsMajorStage->getIndex());
    tagstate.mode = ModeNum(TagPitchMode->getIndex());
    tagstate.stage = MajstageNum(TagStage->getIndex());
    tagstate.ModisMaj = bool(TagIsMajorMode->getIndex());
    tagstate.stageisMaj = bool(TagIsMajorStage->getIndex());
    int updown=updownOctave->get();
    handleMidiBuffer(midiMessages, srcstate, tagstate,updown); 

    
    //int startSample = 0;
    //int numSamples = buffer.getNumSamples();
    //MidiBuffer::Iterator midiIterator(midiMessages);
    //midiIterator.setNextSamplePosition(startSample);

    //int midiEventPos;
    //MidiMessage m;

    ////const ScopedLock sl(lock);

    //while (numSamples > 0)
    //{
    //    if (!midiIterator.getNextEvent(m, midiEventPos))
    //    {
    //       return;
    //    }

    //    const int samplesToNextMidiMessage = midiEventPos - startSample;

    //    if (samplesToNextMidiMessage >= numSamples)
    //    {
    //        
    //        handleMidiEvent(m);
    //        break;
    //    }

    //    handleMidiEvent(m);
    //    startSample += samplesToNextMidiMessage;
    //    numSamples -= samplesToNextMidiMessage;
    //}

    //while (midiIterator.getNextEvent(m, midiEventPos))
    //    handleMidiEvent(m);
    //midiIterator.
    

}

//==============================================================================
bool ChordShiftMidiPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ChordShiftMidiPluginAudioProcessor::createEditor()
{
    return new ChordShiftMidiPluginAudioProcessorEditor (*this);
}

//==============================================================================
void ChordShiftMidiPluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ChordShiftMidiPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ChordShiftMidiPluginAudioProcessor();
}

void ChordShiftMidiPluginAudioProcessor::handlenotes(Array<int>&notes, state&src, state &tag,int updown)
{
    ChordShifter shifter(notes);
    shifter(notes, src, tag);
    for (int i = 0; i < notes.size(); ++i)
    {
        notes.getReference(i) += updown * 12;
    }
}
void ChordShiftMidiPluginAudioProcessor::handleMidiBuffer(MidiBuffer &m,state&src,state &tag,int updown)
{
    HashMap<int,MidiMessage> recorder;
    MidiBuffer::Iterator i(m);
    int samplepostion = 0;
    i.setNextSamplePosition(0);
    MidiMessage rmessage;
    Array<int> noteNumbers;
    Array<int> pos;
    while (i.getNextEvent(rmessage, samplepostion))
    {
        if (rmessage.isNoteOn() || rmessage.isNoteOff())
        {
            noteNumbers.add(rmessage.getNoteNumber());
            pos.add(samplepostion);

        }
        
        recorder.set(samplepostion,MidiMessage(rmessage));        
    }
    //处理 handlenotes(noteNumbers);
    handlenotes(noteNumbers,src,tag,updown);
    for (int i = 0; i < pos.size(); ++i)
    {
        recorder.getReference(pos[i]).setNoteNumber(noteNumbers[i]);
    }
    m.clear();
    HashMap<int, MidiMessage>::Iterator hit(recorder);

    while (hit.next())
    {
        m.addEvent(hit.getValue(), hit.getKey());
    }
}
