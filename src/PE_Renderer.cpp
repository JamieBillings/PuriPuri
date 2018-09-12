#include "PE_Renderer.h"

PE_Renderer::PE_Renderer()
{
    //ctor
}

PE_Renderer::~PE_Renderer()
{
    //dtor
}

SDL_Renderer* PE_Renderer::renderer = nullptr;

int PE_Renderer::renderCreater(int index, unsigned int flags)
{
    renderer = SDL_CreateRenderer(
                                  PE_Window::window,
                                  index,
                                  flags
                                  );

    if (PE_Renderer::renderer == nullptr)
    {
        std::cout<<"Error in PE_RENDERER: "<<SDL_GetError()<<std::endl;
        return 1;
    }

    SDL_RenderPresent(PE_Renderer::renderer);
    return 0;

}
