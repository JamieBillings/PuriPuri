#include "game.h"

SDL_Event e;

bool quit = false;

int main(int argc, char* argv[])
{

    PE_Window::windowCreater("Puri-Puri", 920, 640);

    PE_Renderer::renderCreater(-1, SDL_RENDERER_ACCELERATED);

    PE_Music::init();

    PE_Texture::bitMapFont("assets\\bitmapfont.png",16,16,16);

    game::stageArray();

    game::createblock();

    game::startBoard();

    while ( !quit )
    {
        while ( SDL_PollEvent( &e ) !=0 )
        {
            if ( e.type == SDL_QUIT )
            {
                quit = true;
            }

            switch(game::menuPlace)
            {
            case 0:
                    game::eventMainMenu(&e);
                break;
            case 1:

                break;
            case 2:
                    game::events(&e);
                break;
            case 4:

                break;
            }

        }


        switch(game::menuPlace)
        {
        case 0:
                game::renderMainMenu();
                game::background();
            break;
        case 1:
                game::tutorialRender();
                game::background();
            break;
        case 2:
                game::cursorAnimate();
                game::blockScan();
                game::timer();
                game::obeyGravity();
                game::difficultyFun();
                game::render();
                game::background();
            break;
        case 3:
                quit = true;
            break;
        case 4:

            break;
        }


        PE_Timer::timer();

    }
    game::quit();
    PE_Exit::close();
    return 0;
}
