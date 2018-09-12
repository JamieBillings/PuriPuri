#ifndef GAME_H
#define GAME_H

#include "PE_Exit.h"

class game
{
    public:
        game();
        virtual ~game();

            static void createblock();
            static void render();
            static void quit();
            static void stageArray();
            static void events(SDL_Event* e);
            static void checkcursorbound(char);
            static void cursorAnimate();
            static void parallax(SDL_Event* e);
            static void renderOffset();
            static void blockScan();
            static void startBoard();
            static void resetBoard();
            static void switchBlock();
            static void spawnRow();
            static void timer();
            static void createBlockClass(int,int,int);
            static void blockFallTimer();
            static void difficulty(char);
            static void pointsFun(int,int,int);
            static void background();
            static void obeyGravity();
            static void difficultyFun();
            static void renderMainMenu();
            static void eventMainMenu(SDL_Event*);
            static void tutorialSetup();
            static void tutorialRender();
            static void backgroundMusic();

            static int counter;
            static int points;
            static int menuPlace;
    protected:
    private:

};

#endif // GAME_H


