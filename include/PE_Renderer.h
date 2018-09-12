#ifndef PE_RENDERER_H
#define PE_RENDERER_H

#include "PE_Window.h"

class PE_Renderer
{
    public:
        PE_Renderer();
        virtual ~PE_Renderer();

        static int renderCreater(int index, unsigned int flags);
        static SDL_Renderer* renderer;
    protected:
    private:
};

#endif // PE_RENDERER_H
