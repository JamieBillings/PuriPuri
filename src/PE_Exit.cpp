#include "PE_Exit.h"

PE_Exit::PE_Exit()
{
    //ctor
}

PE_Exit::~PE_Exit()
{
    //dtor
}

void PE_Exit::close()
{
    SDL_DestroyTexture(PE_Texture::asciisheet);
    PE_Texture::asciisheet = nullptr;

    SDL_DestroyRenderer(PE_Renderer::renderer);
    SDL_DestroyWindow(PE_Window::window);

    PE_Window::window = nullptr;
    PE_Renderer::renderer = nullptr;

    Mix_Quit();
    IMG_Quit();
    SDL_Quit();

}
