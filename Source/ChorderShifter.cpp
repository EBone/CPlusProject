/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/


#include<JuceHeader.h>
#include "ChorderShifter.h"
using namespace juce;

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


int rightMo(int l, int r,int moshu)
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




struct ChordXX
{
    constexpr static int Maj[] = { 0,4,7 };
    constexpr static int Min[] = { 0,3,7 };
    /*constexpr static int Maj7[] = { 0,4,7,11,16 };
    constexpr static int Sus4[] = { 0,5,7,12,17 };
    constexpr static int Maj79[] = { 0,4,7,11,14 };*/

    static void trans(Array<int>& input, const int* srcChord, const int* targetChord, ModeNum tag,MajstageNum tags)
    {
        //和弦检查统一为C
        
        int shiftmodsrc = (MajstageDis[tags]+tag)%12 - ModeNum::c;
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
                input.getReference(i) = (diff[temp]+shiftmodsrc)%12+Multi*12;
            }
        }
    }

};

   //调的转换,并转换和弦级数
void ChordShifter::PitchModeshift(Array<int>& data,state &src,state &tag)
{
       
        int modediff = 0;
        if (src.ModisMaj == tag.ModisMaj)
        {
            if (src.ModisMaj)
            {
                //modediff = (tag.mode - src.mode) % 12;
                modediff = rightMo(tag.mode,src.mode,12);
            }
            else//小调变大调
            {
                
                src.mode = ModeNum((int(src.mode) + 3) % 12);
                src.stage = MajstageNum(rightMo(int(src.stage), 2, 7));//MajstageNum((int(tag.stage) -2) % 7);
                tag.mode = ModeNum((int(tag.mode) + 3) % 12);
                tag.stage = MajstageNum(rightMo(int(tag.stage), 2, 7));;
                //modediff = (tag.mode - src.mode) % 12;
                modediff = rightMo(tag.mode, src.mode, 12);
            }
        }
        else
        {
            if (src.ModisMaj)//大转小，先转target为平行大
            {                
                tag.mode=ModeNum((int(tag.mode)+ 3)%12);
                //tag.stage = MajstageNum((int(tag.stage) - 2) % 7);
                tag.stage = MajstageNum(rightMo(int(tag.stage), 2, 7));
                modediff = rightMo(tag.mode, src.mode, 12);
            }
            else//小转大，先把src转为平行大
            {
                src.mode= ModeNum((int(src.mode) +3) % 12);
                //src.stage = MajstageNum((int(tag.stage)-2) % 7);
                src.stage = MajstageNum(rightMo(int(src.stage), 2, 7));
                modediff= rightMo(tag.mode, src.mode, 12);
            }

        }



        for (int i = 0; i < data.size(); ++i)
        {

            data.getReference(i) += modediff;
        }
            
}

    //小转大
void ChordShifter::StageShift(Array<int>&data, state &src, state &tag)
{
       

        int stagedif = MajstageDis[tag.stage] - MajstageDis[src.stage];
        for (int i = 0; i < data.size(); ++i)
        {
            data.getReference(i) +=stagedif;
        }
        
        if (src.stageisMaj != tag.stageisMaj)
        {
            if (src.stageisMaj)
            {
                ChordXX::trans(data, ChordXX::Maj, ChordXX::Min,tag.mode,tag.stage);
            }
            else
            {
                ChordXX::trans(data, ChordXX::Min, ChordXX::Maj,tag.mode,tag.stage);
            }
        }

}


int ChordShifter::resultfix( Array<int>&data)
{
        int ori=dataori[0]/12;
        for (int i = 1; i < dataori.size(); ++i)
        {
            int t1 = dataori[i] / 12;
            if ( t1< ori)
                ori = t1;
        }
        int d = data[0]/12;
        for (int r = 1; r <data.size(); ++r)
        {
            int t2 = data[r] / 12;
            if (t2< d)
                d = t2;
        }
        return d - ori;

}

void ChordShifter::operator()(Array<int>&data, state &src, state &tag)
{
        PitchModeshift(data, src, tag);
        StageShift(data, src, tag);
        int Multi = resultfix(data);
       // if (Multi > 0)
        //{
           /* for (int i = 0; i < data.size(); ++i)
            {
                data.getReference(i) = data.getReference(i) - Multi * 12;
            }*/
        //}

}

    
//==============================================================================
//int main (int argc, char* argv[])
//{
//
//    // ..your code goes here!
//
//    
//    Array<int> data = {0,4,7,11 };
//    ChordShifter shifter(data);
//    for (int i = 0; i < data.size();++i)
//    {
//
//        std::cout << data.getReference(i)<<std::endl;
//    }
//    std::cout << std::endl;
//
//    state src=
//    {
//        ModeNum::g,MajstageNum::I,true,true
//    
//    };
//    state tag =
//    {
//        ModeNum::csharp,MajstageNum::I,true,true
//
//    };
//    shifter(data, src, tag);
//    
//    for (int i = 0; i < data.size(); ++i)
//    {
//
//        std::cout << data.getReference(i)<<std::endl;
//    }
//    std::cout <<std::endl;
//    //int a = 1|2|4|8;
//    
//    std::cout << a;
//    system("pause");
//
//    return 0;
//}

