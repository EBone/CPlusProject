
#include <JuceHeader.h>
#include "sinewavegen.h"
#include "ChordDatas.h"
class SinBall :public Component,public AudioSource
{
public:
    SinBall();
    ~SinBall();

    void resized() override;
    void paint(Graphics &g)override;
    void mouseDoubleClick(const MouseEvent& event);
    void setnote(int n)
    {
        note = n;
    }
    virtual void prepareToPlay(int samplesPerBlockExpected,
        double sampleRate)override;

    
    virtual void releaseResources()override;
    virtual void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)override;
    float getFreq()
    {
        return 131.0*powf(2.0f, float(note) / 12.0f);
    }
    bool isonoff()
    {
        return ison;
    }
    String notename()
    {
        return chordoperation::NoteNames[note % 12] + String(note / 12);
    }
    int getnote()
    {
        return note;
    }
    void setplaying()
    {
        playing = !playing;
        repaint();
    }
    void setonof()
    {
        ison = !ison;
        repaint();
    }
    void setoff()
    {
        if (ison)
        {
            ison = false;
            repaint();
        }
    }
private:
    bool ison;
    bool playing;
    int note;
    float SampleRate;
    WDL_SineWaveGenerator singen;
};