/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"

using namespace juce;
#include"ChorderShifter.h"
#include "ChordExpander.h"
#include "ChordDatas.h"
//==============================================================================
//int main (int argc, char* argv[])
//{
//    // ..your code goes here!
//
//    //36, 36, 36, 36, 40, 40, 40, 40, 38,38,38,38,
//    //Array<int> data = {24,26,31,12,4,7,3,1,31,31};
//    //Array<int>data = {3,3,1,0,12,3,7,13};
//    Array<int>data = {0,2,4,7};
//    //ChordShifter shifter(data);
//    //for (int i = 0; i < data.size();++i)
//    //{
//
//    //    std::cout << data.getReference(i)<<",";
//    //}
//    //std::cout << std::endl;
//    ////上来就给错大小，怎么办
//    //state src=
//    //{
//    //    ModeNum::c,MajstageNum::I,true,true
//    //
//    //};
//    //state tag =
//    //{
//    //    ModeNum::d,MajstageNum::III,true,true
//
//    //};
//    //shifter(data, src, tag);
//    //
//    //for (int i = 0; i < data.size(); ++i)
//    //{
//
//    //    std::cout << data.getReference(i)<<",";
//    //}
//    //std::cout <<std::endl;
//    //int a = 1|2|4|8;
//    
//    //std::cout << a;
//    ChordExpander expander;
//    expander.SetTransMethod(ChordExpander::Transmethod::close_keepbase);
//    expander.expand(data, chordoperation::ChordNames::Maj, chordoperation::ChordNames::Sus2);
//    for (int i = 0; i < data.size(); ++i)
//    {
//        std::cout << data[i]<<std::endl;
//    }
//    std::cout << std::endl;
//    std::cout << chordoperation::chooseOcts(12, 2);
//    system("pause");
//    return 0;
//}
//
