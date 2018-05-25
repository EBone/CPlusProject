#include "ChordExpander.h"
#include <algorithm>

void ChordExpander::expand(Array<int> &notes, ChordNames s, ChordNames t)
{
    jassert(int(s) <= int(ChordNames::Dom9) && int(t) <= int(ChordNames::Dom9));
     Chords_Def sr = chordwithsize[int(s)];
     Chords_Def ta = chordwithsize[int(t)];
    
    if (!(sr== ta))
    {
        if (sr.size == ta.size)
        {
            
            Chordtrans(notes, sr.c, ta.c);
            //todo 检查音
        }
        else if (sr.size > ta.size)
        {   
            Array<int>colornotes=getcolornote(sr,sr.size-ta.size);
            Array<int>nocolornotes = SplitColornote(sr, sr.size - ta.size);
            Chordtrans(notes,nocolornotes.getRawDataPointer(),ta.c);
            std::set<int> noteset;
            for (int i = 0; i<notes.size(); ++i)
            {
                noteset.insert(notes[i]);
            }
            handlecolornotes(notes, noteset, colornotes, transm);
            
        }
        else if (ta.size > sr.size)
        {

            Array<int>colornotes = getcolornote(ta, ta.size - sr.size);
            Array<int>nocolornotes = SplitColornote(ta, ta.size - sr.size);
            Chordtrans(notes, sr.c,nocolornotes.getRawDataPointer());
            std::set<int> noteset;
            for (int i = 0; i<notes.size(); ++i)
            {
                noteset.insert(notes[i]);
            }
            handlecolornotes(notes, noteset, colornotes, transm);

        }
    }
}

void ChordExpander::handlecolornotes(Array<int>&notes, std::set<int>&noteset, Array<int>&colornotes, Transmethod tm)
{
    Array<int>notesoneocts;
    for (int i = 0; i < notes.size(); ++i)
    {
        notesoneocts.add(notes[i] % 12);
    }
    switch (tm)
    {
    case Transmethod::high:
        for (int i = 0; i < colornotes.size(); ++i)
        {
            if (!notesoneocts.contains(colornotes[i]))
            {
                handlenotehigh(notes, noteset, colornotes[i]);
            }
        }
        break;
    case Transmethod::close:
        for (int i = 0; i < colornotes.size(); ++i)
        {
            if (!notesoneocts.contains(colornotes[i]))
            {
                handlenoteclose(notes, noteset, colornotes[i]);
            }
        }
        break;

    case Transmethod::close_keepbase:
        for (int i = 0; i < colornotes.size(); ++i)
        {
            if (!notesoneocts.contains(colornotes[i]))
            {
                handlenoteclose_kb(notes, noteset, colornotes[i]);
            }
        }

        break;
    default:
        jassert(false);
        break;

    }
}
void ChordExpander::handlenotehigh(Array<int>&notes,std::set<int> &noteset,int colornote)//Array<int>&colornotes)
{
    
    std::set<int>::reverse_iterator si;
    si = noteset.rbegin();
    //while (si != noteset.begin()!colornotes.contains(*si % 12) && )
    //{
    //    --si;
    //}
    for (int r = 0; r < notes.size(); ++r)
    {
        if (notes[r] == *si)
        {
            notes.getReference(r) = colornote + chordoperation::chooseOcts(notes[r],colornote) * 12;//colornote + (notes[r] / 12) * 12;
        }
    }
    noteset.erase(*si);
}


void ChordExpander::handlenoteclose(Array<int>&notes, std::set<int> &noteset,int colornote)
{
       
    std::set<int>::reverse_iterator si;
    int notenumber = -1;
    int minvalue = 108;
    for (si =noteset.rbegin(); si != noteset.rend(); ++si)
    {
        //int temp= rightMo(*si, colornote, 12)
        
        int temp= chooseOctdiff(*si,colornote);
        if (temp < minvalue)
        {
            minvalue = temp;
            notenumber = *si;            
        }
    }
    for (int i = 0; i < notes.size(); ++i)
    {
        if (notes[i] == notenumber)
        {
            //notes.getReference(i) = (notenumber / 12) * 12 + colornote;
            notes.getReference(i) = colornote + chordoperation::chooseOcts(notes[i], colornote) * 12;
        }
    }
    noteset.erase(notenumber);
}

void ChordExpander::handlenoteclose_kb(Array<int>&notes, std::set<int> &noteset, int colornote)
{
    if (noteset.size() > 0)
    {
        std::set<int>::iterator it;
        it = noteset.begin();
        if (it != noteset.end())
        {
            int lowestnote = *(noteset.begin());
            if (lowestnote % 12 == 0)
            {
                noteset.erase(lowestnote);
            }
        }        
    }
    handlenoteclose(notes, noteset, colornote);
}

