#pragma once

#include "ChordDatas.h"
#include <set>

using namespace chordoperation;

class ChordExpander
{
       
public:
    enum Transmethod
    {
        high,
        close,
        close_keepbase
    };
    void expand(Array<int> &notes,ChordNames s,ChordNames t);    
    const int* getChordNotes(ChordNames c)
    {
        return Chords[int(c)];
    }
    void SetTransMethod(Transmethod t)
    {
        transm = t;
    }
    
private:
    void handlecolornotes(Array<int>&notes, std::set<int>&noteset, Array<int>&colornotes, Transmethod tm);
    void handlenotehigh(Array<int>&notes, std::set<int> &noteset, int colornote); //Array<int>&colornotes);
    Transmethod transm;
    void handlenoteclose(Array<int>&notes, std::set<int> &noteset, int colornote);
    void handlenoteclose_kb(Array<int>&notes, std::set<int> &noteset, int colornote);
    int getMiddOct(Array<int>&notes)
    {
        Array<int>octs;
        for (int i = 0; i < notes.size(); ++i)
        {
            octs.add(notes[i] / 12);
        }
        octs.sort();
        return octs[octs.size() / 2];
    }
};

