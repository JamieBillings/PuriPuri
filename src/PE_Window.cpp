#include "PE_Window.h"

PE_Window::PE_Window()
{
    //ctor
}

PE_Window::~PE_Window()
{
    //dtor
}

SDL_Window* PE_Window::window = nullptr;

int PE_Window::windowCreater(std::string name,unsigned int w, unsigned int h)
{
    PE_Window::window = SDL_CreateWindow(
                                         name.c_str(),
                                         SDL_WINDOWPOS_CENTERED,
                                         SDL_WINDOWPOS_CENTERED,
                                         w,
                                         h,
                                         SDL_WINDOW_SHOWN
                                        );

    if ( PE_Window::window == nullptr )
    {
        std::cout<<"Error in PE_WINDOW: "<<SDL_GetError()<<std::endl;
        return 1;
    }

    return 0;

}


