//src和tag的状态

#pragma once

#include<JuceHeader.h>
#include "ChordDatas.h"
using namespace chordoperation;
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
    static void updownOctave(Array<int>&data, bool updown);


private:
    Array<int>dataori;

};
