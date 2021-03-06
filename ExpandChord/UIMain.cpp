#include <JuceHeader.h>
#include "ShowBall.h"
class MyApp :public JUCEApplication
{
    const String getApplicationName() override { return ProjectInfo::projectName; }
    const String getApplicationVersion() override { return ProjectInfo::versionString; }
    // bool moreThanOneInstanceAllowed() override { return true; }

    //==============================================================================
    void initialise(const String& commandLine) override
    {
        // This method is where you should put your application's initialisation code..

        mainwindow = new MainWindow;


    }

    void shutdown() override
    {
        // Add your application's shutdown code here..

        mainwindow = nullptr; // (deletes our window)
    }

    //==============================================================================
    void systemRequestedQuit() override
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted(const String& commandLine) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }
    

private:
    class MainWindow :public DocumentWindow
    {
    public:
        MainWindow() :DocumentWindow(String(""), Desktop::getInstance().getDefaultLookAndFeel().findColour(ResizableWindow::backgroundColourId),
            DocumentWindow::allButtons)
        {
            setContentOwned(new ShowBalls, true);
            centreWithSize(getWidth(), getHeight());
            setVisible(true);

        }
        void closeButtonPressed()override
        {

            //dynamic_cast<Thread*>(getContentComponent())->stopThread(2000);
            dynamic_cast<ShowBalls*>(getContentComponent())->exitthread();
            Thread::sleep(2000);
            
            JUCEApplication::getInstance()->systemRequestedQuit();
        }
    };
    ScopedPointer<MainWindow> mainwindow;
};

START_JUCE_APPLICATION(MyApp)
