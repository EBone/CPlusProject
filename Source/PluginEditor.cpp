/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
ChordShiftMidiPluginAudioProcessorEditor::ChordShiftMidiPluginAudioProcessorEditor (ChordShiftMidiPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    const OwnedArray<AudioProcessorParameter> &temp = processor.getParameters();
    for (int i = 0; i < processor.getNumParameters(); ++i)
    {
        if (AudioParameterChoice *pr = dynamic_cast<AudioParameterChoice*>(temp[i]))
        {
            ComboBox *box = new ComboBox;
            box->addItemList(pr->choices, 1);
            box->setSelectedId(pr->getIndex() + 1);
            addAndMakeVisible(box);
            box->addListener(this);
            ParamBoxes.add(box);
            Label *label = new Label(pr->name,pr->name);
            ParamLabels.add(label);
            addAndMakeVisible(label);            

        } 
        if (AudioParameterInt *pr = dynamic_cast<AudioParameterInt*>(temp[i]))
        {
            OctaveSlider = new Slider(Slider::SliderStyle::LinearHorizontal, Slider::TextEntryBoxPosition::TextBoxLeft);
            OctaveSlider->setValue(double(pr->get()));
            OctaveSlider->setRange(-6.0, 6.0);
            addAndMakeVisible(OctaveSlider);
            OctaveSlider->addListener(this);
            Label *label = new Label(pr->name, pr->name);
            ParamLabels.add(label);
            addAndMakeVisible(label);
        }

    }

    setSize (600,800 );
}

ChordShiftMidiPluginAudioProcessorEditor::~ChordShiftMidiPluginAudioProcessorEditor()
{
  

    delete OctaveSlider;
}

//==============================================================================
void ChordShiftMidiPluginAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the backgrounSSd with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

   /* g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);*/
}

void ChordShiftMidiPluginAudioProcessorEditor::resized()
{
    for (int i = 0; i < ParamBoxes.size(); ++i)
    {
        ParamLabels[i]->setBounds(0, i * 50, 100,80);
        ParamBoxes[i]->setBounds(160, i *50 ,200, 80);
    }
    ParamLabels[ParamBoxes.size()]->setBounds(0, ParamBoxes.size() * 50, 100, 80);
    OctaveSlider->setBounds(160, ParamBoxes.size() * 50, 300, 100);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void ChordShiftMidiPluginAudioProcessorEditor::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{


    if (ParamBoxes.contains(comboBoxThatHasChanged))
    {

        int index = ParamBoxes.indexOf(comboBoxThatHasChanged);
        const OwnedArray<AudioProcessorParameter>&params = processor.getParameters();

        if (AudioParameterChoice*pc = dynamic_cast<AudioParameterChoice*>(params.getUnchecked(index)))
        {
            *pc = comboBoxThatHasChanged->getSelectedItemIndex();
        }
    }

}

void ChordShiftMidiPluginAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider == OctaveSlider)
    {
        const OwnedArray<AudioProcessorParameter>&params = processor.getParameters();
        for (int i = 0; i < params.size(); ++i)
        {
            if (AudioParameterInt *pi = dynamic_cast<AudioParameterInt*>(params.getUnchecked(i)))
            {

                pi->beginChangeGesture();
                *pi = int(OctaveSlider->getValue());
                pi->endChangeGesture();

            }


        }
    }

}