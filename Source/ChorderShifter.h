//src和tag的状态

#pragma once

#include<JuceHeader.h>

extern StringArray ModNumNames;

extern StringArray StageNames;
extern StringArray ModeMajMin;
extern StringArray StageMajMin;






enum ModeNum
{
    c = 0,
    csharp,
    d,
    dhsarp,
    e,
    f,
    fsharp,
    g,
    gsharp,
    a,
    asharp,
    b,
};

//级数
enum MajstageNum
{
    I = 0,
    II,
    III,
    IV,
    V,
    VI,
    VII
};
extern int MajstageDis[7];

struct state
{
    ModeNum mode;
    MajstageNum stage;
    bool ModisMaj;//true is major
    bool stageisMaj;
};


class ChordShifter
{
public:

    ChordShifter(Array<int>&data) :dataori(data) {
    }
    //调的转换,并转换和弦级数
    void PitchModeshift(Array<int>& data, state &src, state &tag); 

    //小转大
    void StageShift(Array<int>&data, state &src, state &tag);
    int resultfix(Array<int>&data);
    void operator()(Array<int>&data, state &src, state &tag);
    
private:
    Array<int>dataori;

};
