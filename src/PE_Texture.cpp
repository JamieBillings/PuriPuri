#include "PE_Texture.h"

PE_Texture::PE_Texture()
{
    //ctor
}

PE_Texture::~PE_Texture()
{
    //dtor
}

SDL_Texture* PE_Texture::loadTexture(std::string path)
{

    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );

    if (loadedSurface == nullptr)
    {
        std::cout<<SDL_GetError()<<std::endl;
    }


    newTexture = SDL_CreateTextureFromSurface(PE_Renderer::renderer,loadedSurface);

    if ( newTexture == nullptr )
    {
        std::cout<<"! "<<path.c_str()<<" "<<SDL_GetError()<<std::endl;
    }

    SDL_FreeSurface( loadedSurface );

    return newTexture;
}

SDL_Rect animation = {0,0,0,0};

void PE_Texture::renderAnimation(SDL_Texture* texture,int frames,SDL_Rect posistion,SDL_Rect srcPosistion)
{
    srcPosistion.x = srcPosistion.x + srcPosistion.w;

    if(srcPosistion.x >= srcPosistion.w * frames)
    {
        srcPosistion.x = 0;
    }

    SDL_RenderCopy(PE_Renderer::renderer,texture,&srcPosistion,&posistion);

}

SDL_Texture* PE_Texture::asciisheet = nullptr;
SDL_Rect characters[256];

void PE_Texture::bitMapFont(std::string asciisheetloc,int gridx,int gridy,int lenacross)
{
    PE_Texture::asciisheet = loadTexture(asciisheetloc);

    int x = 0;
    int y = 0;

    for (unsigned int i = 0; i < 256; i++)
    {
        characters[i] = {x, y, gridx, gridy};

        x = x + gridx;

        if( x > gridx * lenacross)
        {
            x = 0;
            y = y + gridy;
        }
    }
}

void PE_Texture::convertIntString(int num, SDL_Rect pos, int spreadX,int spreadY, int lineLength)
{

    //Converting Points (int) to score (string)
    std::string text;

    std::ostringstream convert;

    convert << num;

    text = convert.str();

    renderBitMap(text,pos,spreadX,spreadY,lineLength);

}

void PE_Texture::renderBitMap(std::string str, SDL_Rect pos, int spreadX,int spreadY, int lineLength)
{
    int ascii = 0;

    int currentLineLength = 0;

    int startingXPos = pos.x;

    for (unsigned int i = 0; i < str.length(); i++)
    {
        ascii = static_cast <unsigned char> (str.at(i));
        ascii = ascii + 3;

        SDL_RenderCopy(PE_Renderer::renderer,asciisheet,&characters[ascii],&pos);
        if(lineLength == 0)
        {
            pos.x = pos.x + spreadX;
        }
        else
        {
            if(currentLineLength >= lineLength)
            {
                pos.x = startingXPos;
                pos.y = pos.y + spreadY;
                currentLineLength = 0;
            }
            else
            {
                pos.x = pos.x + spreadX;
                currentLineLength++;
            }
        }
    }
}

