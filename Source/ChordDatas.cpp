
#include"ChordDatas.h"


StringArray ModNumNames({
    "c",
    "csharp",
    "d",
    "dhsarp",
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




int Chord_Maj[] = { 0,4,7 };
int Chord_Min[] = { 0,3,7 };
int Chord_Sus4[] = { 0,5,7 };
int Chord_Sus2[] = { 0,2,7 };
int Chord_Add9[] = { 0,2,4,7 };
int Chord_Maj7[] = { 0,4,7,11 };
int Chord_Min7[] = { 0,3,7,10 };
int Chord_Dom7[] = { 0,4,7,10, };//Dominate?
int Chord_Maj9[] = { 0,2,4,7,11 };
int Chord_Min9[] = { 0,2,3,7,10 };
int Chord_Dom9[] = { 0,2,4,7,10 };//Dominate9?   

Array<int *>Chords =
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
