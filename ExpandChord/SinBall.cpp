#include "SinBall.h"

SinBall::SinBall():ison(false),note(0),playing(false)
{

}

SinBall::~SinBall()
{

}

void SinBall::resized()
{

}
void SinBall::paint(Graphics &g)
{
    g.setColour(Colours::grey);
    g.fillAll();
    if (ison)
    {
        g.setColour(Colours::red);
        g.fillEllipse(getLocalBounds().toFloat());
        if (playing)
        {
            g.setColour(Colours::yellowgreen);
            g.fillEllipse(getLocalBounds().toFloat());
        }

    }
    else
    {
        g.fillEllipse(getLocalBounds().toFloat());
    }

    g.setColour(Colours::white);
    g.drawFittedText(notename(), getLocalBounds(), Justification::centred, 3);

}
void SinBall::mouseDoubleClick(const MouseEvent& event)
{
    ison = !ison;
    repaint();
}

 void SinBall::prepareToPlay(int samplesPerBlockExpected,double sampleRate)
{
     SampleRate = sampleRate;
     singen.Reset();
     singen.SetFreq(getFreq() / SampleRate*0.5);
     
    
 }


 void SinBall::releaseResources()
{
     
 }
 void SinBall::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{

     for (int i = 0; i < bufferToFill.numSamples; ++i)
     {
         bufferToFill.buffer->getWritePointer(0)[i] = singen.Gen();
         bufferToFill.buffer->getWritePointer(1)[i] = bufferToFill.buffer->getWritePointer(0)[i];
     }
     

 }

