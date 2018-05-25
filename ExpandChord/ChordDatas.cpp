
#include"ChordDatas.h"


namespace chordoperation
{
    StringArray ExpandMethod({
        "high",
        "close",
        "close_keepbase"
    });
    StringArray ModNumNames({
        "c",
        "csharp",
        "d",
        "dsharp",
        "e",
        "f",
        "fsharp",
        "g",
        "gsharp",
        "a",
        "asharp",
        "b",
    });
    StringArray StageNames({
        "I",
        "II",
        "III",
        "IV",
        "V",
        "VI",
        "VII"
    });
    StringArray NoteNames(
    {
        "c",
        "#c",
        "d",
        "#d",
        "e",
        "f",
        "#f",
        "g",
        "#g",
        "a",
        "#a",
        "b",

    }
    );
    StringArray ModeMajMin(
    {
        "Minor_Mode",
        "Major_Mode"
    }
    );
    StringArray StageMajMin(
    {
        "Minor_Chord",
        "Major_Chord"
    }
    );
    StringArray ChordNameSA(
    {
        "Chord_Maj",
        "Chord_Min",
        "Chord_Sus4",
        "Chord_Sus2",
        "Chord_Add9",
        "Chord_Maj7",
        "Chord_Min7",
        "Chord_Dom7", //Dominate?
        "Chord_Maj9",
        "Chord_Min9",
        "Chord_Dom9",//Dominate    
    }
    );
    int MajstageDis[7] = {
        0,
        2,
        4,
        5,
        7,
        9,
        11
    };
    //int Majdis[7] = { 0,2,4,5,7,9,11 };
    //int Mindis[7] = { 0,2,3,5,7,8,10 };

    int rightMo(int l, int r, int moshu)
    {
        jassert(l >= 0 && r >= 0);
        int temp = l - r;
        if (temp < 0)
        {
            return moshu - (abs(temp) % moshu);

        }
        else
        {
            return temp%moshu;
        }
    }
    static const int Chord_Maj[] = { 0,7,4 };
    static const int Chord_Min[] = { 0,7,3 };
    static const int Chord_Sus4[] = { 0,7,5 };
    static const int Chord_Sus2[] = { 0,7,2 };
    static const int Chord_Add9[] = { 0,7,4,2 };
    static const int Chord_Maj7[] = { 0,7,4,11 };
    static const int Chord_Min7[] = { 0,7,3,10 };
    static const int Chord_Dom7[] = { 0,7,4,10, };//Dominate?
    static const int Chord_Maj9[] = { 0,7,4,11,2 };
    static const int Chord_Min9[] = { 0,7,3,10,2 };
    static const int Chord_Dom9[] = { 0,7,4,10,2 };//Dominate9?     

    Array<const int *>Chords =
    {
        Chord_Maj,
        Chord_Min,
        Chord_Sus4,
        Chord_Sus2,
        Chord_Add9,
        Chord_Maj7,
        Chord_Min7,
        Chord_Dom7, //Dominate?
        Chord_Maj9,
        Chord_Min9,
        Chord_Dom9,//Dominate
    };
    
    const Chords_Def chordwithsize[] =
    {
        
        {Chord_Maj,3},
        {Chord_Min,3},
        {Chord_Sus4,3},
        {Chord_Sus2,3},
        {Chord_Add9,4},
        {Chord_Maj7,4},
        {Chord_Min7,4},
        {Chord_Dom7,4},
        {Chord_Maj9,5},
        {Chord_Min9,5},
        {Chord_Dom9,5},

    };

    Array<int> getcolornote(Chords_Def &hl,int diff)
    {
        Array<int>colornotes;        
        
        for (int r = (hl.size - diff); r < hl.size; ++r)
        {
            colornotes.add(hl.c[r]);
        }
        return colornotes;
    }

    Array<int>SplitColornote(Chords_Def&hl, int diff)
    {
        Array<int>nocolornote;
        for (int i = 0; i < hl.size - diff; ++i)
        {
            nocolornote.add(hl.c[i]);
        }
        return nocolornote;

    }
    void Chordtrans(Array<int>& input, const int* srcChord, const int* targetChord, ModeNum tag , MajstageNum tags)
    {
        //和弦检查统一为C

        int shiftmodsrc = (MajstageDis[tags] + tag) % 12 - ModeNum::c;
        jassert(shiftmodsrc >= 0);
        HashMap<int, int> diff;
        for (int i = 0; i < 3; ++i)
        {
            diff.set(srcChord[i], targetChord[i]);
        }

        for (int i = 0; i < input.size(); i++)
        {
            //int temp = (input.getReference(i) - shiftmodsrc) % 12;
            int temp = rightMo(input.getReference(i), shiftmodsrc, 12);
            int Multi = input.getReference(i) / 12;
            if (!diff.contains(temp))
            {
                continue;
            }
            else
            {
                input.getReference(i) = (diff[temp] + shiftmodsrc) % 12 + Multi * 12;
            }
        }
    }

    int chooseOcts(int note, int colornote)
    {
        jassert(0<=note&&note< 128 && 0<=colornote&&colornote < 12);
        if (note <12)
        {
            if (note > colornote)
            {
                return note - colornote < (colornote + 12 - note) ? 0 : 1;
            }
            else
            {
                return 0;
            }
        }
        else if (note >= 12)
        {
            for (int i = 0; i < 10; ++i)
            {
                if (abs(note - (colornote + i * 12)) <= 6)
                {
                    return i;
                }
            }
        }
        jassert(false);
        return -1;

    }
    int chooseOctdiff(int note, int colornote)
    {
        jassert(note < 128 && colornote < 12);
        note = note % 12;
        return abs(note - colornote)>(note-colornote+12)? (note - colornote + 12):abs(note - colornote);    

    }

};


