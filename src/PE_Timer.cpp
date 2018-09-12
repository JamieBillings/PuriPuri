#include "PE_Timer.h"

PE_Timer::PE_Timer()
{
    //ctor
}

PE_Timer::~PE_Timer()
{
    //dtor
}

LTimer PE_Timer::fpsTimer;
LTimer PE_Timer::capsTimer;

int countedFrames = 0;
int SCREEN_FPS = 120;
int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

void PE_Timer::timer()
{

    fpsTimer.start();

    float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
    if ( avgFPS > 2000000 )
    {
        avgFPS = 0;
    }

    ++countedFrames;

    int frameTicks = capsTimer.getTicks();
    if( frameTicks < SCREEN_TICKS_PER_FRAME )
    {
        SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks);
    }

}

LTimer::LTimer()
{

    mStartTicks = 0;
    mPausedTicks = 0;

    mPaused = false;
    mStarted = false;

}

void LTimer::start()
{
    mStarted = true;

    mPaused = true;

    mStartTicks = SDL_GetTicks();
    mPausedTicks = 0;
}

void LTimer::stop()
{

    mStarted = false;

    mPaused = false;

    mStartTicks = 0;
    mPausedTicks = 0;

}

void LTimer::pause()
{

    if( mStarted && !mPaused )
    {

        mPaused = true;

        mPausedTicks = SDL_GetTicks() - mStartTicks;
        mStartTicks = 0;
    }
}

Uint32 LTimer::getTicks()
{
    Uint32 time = 0;

    if(mStarted)
    {
        time = mPausedTicks;
        if(mPaused)
        {
            time = mPausedTicks;
        }
        else
        {
            time = SDL_GetTicks() - mStartTicks;
        }
    }

    return time;
}

bool LTimer::isStarted()
{
    return mStarted;
}

bool LTimer::isPaused()
{
    return mPaused && mStarted;
}
