#include "PE_Music.h"

PE_Music::PE_Music()
{
    //ctor
}

PE_Music::~PE_Music()
{
    //dtor
}

int PE_Music::init()
{
    if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cout<<"SDL_mixer could not be initalised! SDL_mixer Error: ", Mix_GetError();
        return 1;
    }
    return 0;
}
