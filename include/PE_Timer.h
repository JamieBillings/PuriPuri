#ifndef PE_TIMER_H
#define PE_TIMER_H

#include "PE_Renderer.h"

class LTimer
{
public:
    LTimer();

    void start();
    void stop();
    void pause();
    void unpause();

    Uint32 getTicks();

    bool isStarted();
    bool isPaused();

private:

    Uint32 mStartTicks;

    Uint32 mPausedTicks;

    bool mPaused;
    bool mStarted;
};

class PE_Timer
{
    public:
        PE_Timer();
        virtual ~PE_Timer();

        static LTimer fpsTimer;
        static LTimer capsTimer;

        static void timer();
    protected:
    private:
};

#endif // PE_TIMER_H
