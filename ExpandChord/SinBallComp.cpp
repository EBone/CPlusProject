#include "SinBallComp.h"

SinBallComp::SinBallComp()
{
    for (int i = 0; i < row*colum; ++i)
    {
        balls[i].setnote(i);
        addAndMakeVisible(balls[i]);
        
    }
    startTimer(1000);
    
 }

SinBallComp::~SinBallComp()
{
    stopTimer();

}

void SinBallComp::resized()
{
    int stepx = getWidth() / colum;
    int stepy = getHeight() /row;

    for (int y = 0; y < row;++y)
    {
        for (int x = 0; x < colum; ++x)
        {
            Rectangle<int> ballbounds(x*stepx,y*stepy,stepx,stepy);
            balls[x+y*row].setBounds(ballbounds);
        }
    }

}

void SinBallComp::paint(Graphics &g)
{
}
void SinBallComp::timerCallback()
{
    ScopedLock mylock(clock);
    ballison.clear();
    for (int i = 0; i < row*colum; ++i)
    {
        if (balls[i].isonoff())
        {
            ballison.add(balls+i);
        }
    }
}