#ifndef PE_INCLUDE_H
#define PE_INCLUDE_H


#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <time.h>
#include <vector>


class PE_Include
{
    public:
        PE_Include();
        virtual ~PE_Include();

        static void Init();
    protected:
    private:
};

#endif // PE_INCLUDE_H
