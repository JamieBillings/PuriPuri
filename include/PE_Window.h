#ifndef PE_WINDOW_H
#define PE_WINDOW_H

#include "PE_Include.h"

class PE_Window
{
    public:
        PE_Window();
        virtual ~PE_Window();

        static int windowCreater(std::string name,unsigned int w, unsigned int h);

        static SDL_Window* window;

    protected:
    private:
};

#endif // PE_WINDOW_H
