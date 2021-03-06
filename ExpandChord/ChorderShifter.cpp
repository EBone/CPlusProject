﻿/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/


#include<JuceHeader.h>
#include "ChorderShifter.h"
#include "ChordDatas.h"


    


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
                Chordtrans(data, Chords[ChordNames::Maj], Chords[ChordNames::Min],tag.mode,tag.stage);
            }
            else
            {
                Chordtrans(data, Chords[ChordNames::Min], Chords[ChordNames::Maj],tag.mode,tag.stage);
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
    StageShift(data, src, tag); /*int Multi = resultfix(data);
        for (int i = 0; i < data.size(); ++i)
        {
            data.getReference(i) = data.getReference(i) - Multi * 12;
        }*/
}

 void ChordShifter::updownOctave(Array<int>&data, bool updown)
{
     if (updown)
     {

         for (int i = 0; i < data.size(); ++i)
         {
             data.getReference(i) += 12;
         }
     }
     else
     {
         for (int i = 0; i < data.size(); ++i)
         {
             data.getReference(i) -= 12;
         }

     }
}
 