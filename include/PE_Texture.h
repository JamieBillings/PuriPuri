#ifndef PE_TEXTURE_H
#define PE_TEXTURE_H

#include "PE_Timer.h"

class PE_Texture
{
    public:
        PE_Texture();
        virtual ~PE_Texture();

        static SDL_Texture* loadTexture(std::string);
        static void renderAnimation(SDL_Texture* texture,int frames,SDL_Rect posistion,SDL_Rect srcPosistion);
        static void bitMapFont(std::string asciisheetloc,int gridx,int gridy,int lenacross);
        static void renderBitMap(std::string, SDL_Rect , int ,int , int);
        static void convertIntString(int num, SDL_Rect , int ,int , int);
        static void reverseRenderBitMap(std::string, SDL_Rect , int ,int , int);

        static SDL_Texture* asciisheet;

    protected:
    private:
};

#endif // PE_TEXTURE_H
