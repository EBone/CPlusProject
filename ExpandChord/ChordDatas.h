#pragma once

#include <JuceHeader.h>
namespace chordoperation
{
    extern int rightMo(int l, int r, int moshu);
    extern StringArray ModNumNames;

    extern StringArray StageNames;
    extern StringArray ModeMajMin;
    extern StringArray StageMajMin;
    extern StringArray NoteNames;
    extern StringArray ChordNameSA;
    extern StringArray ExpandMethod;

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

    extern Array<const int *>Chords;
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
    struct Chords_Def
    {
        const int* c;
        int size;
        bool operator ==(const Chords_Def &rh)const
        {
            if (this->c == rh.c &&this->size == rh.size)
                return true;
            else
                return false;
        }
    };
    extern const Chords_Def chordwithsize[];
    extern void Chordtrans(Array<int>& input, const int* srcChord, const int* targetChord, ModeNum tag = ModeNum(0), MajstageNum tags = MajstageNum(0));
    extern Array<int> getcolornote(Chords_Def &hl,int diff);
    extern Array<int>SplitColornote(Chords_Def&hl, int diff);
    extern int chooseOcts(int note, int colornote);
    extern int chooseOctdiff(int note, int colornote);
};