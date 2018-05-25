#include "ShowBall.h"


ShowBalls::ShowBalls() :Thread("play thread"), shouldexit(false),\
play(true),srcname(0),tagname(5),methodname(2)
    {



        srcchordbox.addItemList(chordoperation::ChordNameSA, 1);
        tagchordbox.addItemList(chordoperation::ChordNameSA, 1);
        expandmethodbox.addItemList(chordoperation::ExpandMethod, 1);
        addAndMakeVisible(srcchordbox);
        addAndMakeVisible(tagchordbox);
        addAndMakeVisible(expandmethodbox);
        srcchordbox.addListener(this);
        tagchordbox.addListener(this);
        expandmethodbox.addListener(this);
        tagchordbox.setSelectedItemIndex(tagname);
        srcchordbox.setSelectedItemIndex(srcname);
        expandmethodbox.setSelectedItemIndex(methodname);
        chordexpander.SetTransMethod(ChordExpander::close_keepbase);
        button.setButtonText(String("Play"));
        addAndMakeVisible(button);
        button.addListener(this);
        addAndMakeVisible(balls);
        addAndMakeVisible(expanderball);
        setSize(600, 800);
        audiomanager.initialise(0, 2, nullptr, true);
        audiomanager.addAudioCallback(&player);
        startThread();
    }
ShowBalls ::~ShowBalls()
    {
        audiomanager.removeAudioCallback(&player);
        audiomanager.closeAudioDevice();
        stopThread(100);

    }
    void ShowBalls::resized()
    {
        balls.setBounds(getLocalBounds().removeFromTop(600).removeFromLeft(300).removeFromTop(300));
        expanderball.setBounds(getLocalBounds().removeFromTop(600).removeFromRight(280).removeFromTop(280));
        button.setBounds(getLocalBounds().removeFromBottom(100));
        Rectangle<int> recforbox = getLocalBounds().removeFromBottom(200).removeFromTop(100);
        srcchordbox.setBounds(recforbox.removeFromLeft(200));
        tagchordbox.setBounds(recforbox.removeFromLeft(200));
        expandmethodbox.setBounds(recforbox.removeFromLeft(200));
    }
    void ShowBalls::paint(Graphics &g)
    {
        g.fillAll(Colours::grey);
        g.setColour(Colours::blue);
        g.drawLine(310, 0, 310, 600, 1.0);
    }
    void ShowBalls::run()
    {

        while (!shouldexit)
        {
            if (play) {
                Array<SinBall*> bison = balls.getballsison();

                int n = bison.size();
                Array<int> notestochange;
                for (int i = 0; i < n; ++i)
                {
                    notestochange.add(bison[i]->getnote());
                }
                chordexpander.expand(notestochange, chordoperation::ChordNames(srcname), chordoperation::ChordNames(tagname));
                    juce::MessageManager::callAsync([this]()
                    {
                       this->expanderball.setalloff();
                    });
                    
                    for (int i = 0; i < n; ++i)
                    {
                        juce::MessageManager::callAsync([i, notestochange, this]()
                        {
                            this->expanderball.setballon(notestochange[i]);
                        });
                    }
                while (n > 0)
                {
                    handleaudiosource(bison[n - 1]);
                    /*{
                    MessageManagerLock mml(Thread::getCurrentThread());
                    bison[n-1]->setplaying();
                    }*/
                    --n;
                    wait(500);
                }
            }
            else
            {
                player.setSource(nullptr);
                wait(-1);
            }

        }
    }
    void ShowBalls::handleaudiosource(SinBall*s)
    {
        juce::MessageManager::callAsync([s, this]() 
        {
            s->setplaying();
            this->player.setSource(s);
        });
    }
    void ShowBalls::buttonClicked(Button*b)
    {
        if (b == &button)
        {
            if (!play)
            {
                notify();
            }
            play = !play;

        }

    }
    void ShowBalls::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
    {
        if (comboBoxThatHasChanged == &srcchordbox)
        {
            srcname = srcchordbox.getSelectedItemIndex();
        }
        else if (comboBoxThatHasChanged == &tagchordbox)
        {
            tagname = tagchordbox.getSelectedItemIndex();
        }
        else if (comboBoxThatHasChanged == &expandmethodbox)
        {
            methodname = expandmethodbox.getSelectedItemIndex();
            chordexpander.SetTransMethod(ChordExpander::Transmethod(methodname));
        }

    }
