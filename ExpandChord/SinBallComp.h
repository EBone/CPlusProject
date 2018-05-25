
#include <JuceHeader.h>
#include "SinBall.h"


class SinBallComp :public Component,public Timer
{
public:
    SinBallComp();

    ~SinBallComp();
    void resized()override;
    void paint(Graphics &g)override;
    void timerCallback()override;
    Array<SinBall*> getballsison()
    {
        ScopedLock mylock(clock);
        return ballison;
    }
    void setballon(int index)
    {

        balls[index].setonof();
    }
    void setalloff()
    {
        for (int i = 0; i < row*colum; ++i)
        {
            balls[i].setoff();
        }
    }
private:
    static const  int row = 12;
    static const  int colum =12;
    SinBall balls[row*colum];
    Array<SinBall*> ballison;
    CriticalSection clock;

};

