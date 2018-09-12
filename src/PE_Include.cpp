#include "PE_Include.h"

PE_Include::PE_Include()
{
    //ctor
}

PE_Include::~PE_Include()
{
    //dtor
}

void PE_Include::Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout<<"Error in PE_Include: "<<"SDL could not be initialised! "<<SDL_GetError();
    }
}
