#pragma once

#include <JuceHeader.h>
extern int rightMo(int l, int r, int moshu);
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

extern Array<int *>Chords;
enum ChordNames
{
    Maj,
    Min,
    Sus4,
    Sus2,
    Add9,
    Maj7,
    Min7,
    Dom7,
    Maj9,
    Min9,
    Dom9
};