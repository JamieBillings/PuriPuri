#include "game.h"

game::game()
{
    //ctor
}

game::~game()
{
    //dtor
}
//
// Variables Used Later in Code
SDL_Texture* heartblockskin = nullptr;
SDL_Rect heartblockpos = {200,200,32,32};

const int STAGE_WIDTH = 11;
const int STAGE_HEIGHT = 16;

SDL_Rect stagePosArr [STAGE_WIDTH][STAGE_HEIGHT];
int stageIDArr [STAGE_WIDTH][STAGE_HEIGHT];


int stageMultiX = 350;
int stageMultiY = 70;

SDL_Texture* backpanel = nullptr;
SDL_Texture* frontpanel = nullptr;

SDL_Texture* cursor = nullptr;
SDL_Rect cursorPos = {251,21,64,32};
SDL_Rect cursorSrcPos = {0,0,64,32};

bool action = false;

int animatecounter = 0;

int renderOffsetX = 0;

int mouseX,mouseY = 0;

SDL_Rect boardPos = {0, 0, 920, 640};

SDL_Texture* blocksheet = nullptr;
SDL_Rect heartSkinPos = {34,0,32,32};
SDL_Rect triangleSkinPos = {66,0,32,32};
SDL_Rect diamondSkinPos = {98,0,32,32};
SDL_Rect starSkinPos = {34,32,32,32};
SDL_Rect pentagonSkinPos = {66,32,32,32};
SDL_Rect circleSkinPos = {98,32,32,32};
SDL_Rect blockborderPos = {0,0,32,32};

SDL_Texture* diamond = nullptr;
SDL_Rect blockpossing = {0,0,32,32};
SDL_Texture* star = nullptr;
SDL_Texture* triangle = nullptr;

int lengthX,lengthY;

int cursorPosX, cursorPosY;
int tempBlock = 0;

int game::counter = 0;
const int COUNTER = 1800;

int subDown = 0;
bool subDownBool = false;

int gameSpeed = 1;
int scoreMulti = 1;

int game::points = 0;

SDL_Rect pointsLoc = {180,110,32,32};
SDL_Rect difficultyLoc = {240,305,32,32};

SDL_Texture* border = nullptr;

bool actionMouse = false;
bool actionMouseButton = false;

SDL_Rect backgroundRunPos = {0,0,1800,640};
SDL_Rect backgroundIMG1Pos = {0,0,920,900};
SDL_Rect backgroundIMG2Pos = {0,0,920,900};
SDL_Texture* backgroundIMG1 = nullptr;
SDL_Texture* backgroundRunnerIMG = nullptr;
SDL_Texture* backgroundIMG2 = nullptr;

bool runnerLeftMove = false;
bool back1LeftMove = false;
bool back2LeftMove = false;

SDL_Texture* overlaySkin = nullptr;

SDL_Texture* mainmenuSkin = nullptr;

int game::menuPlace = 0;

SDL_Texture* highlight = nullptr;
SDL_Rect highlightPos = {0,250,920,80};

SDL_Rect hitbox1 = {0,250,920,80};
SDL_Rect hitbox2 = {0,370,920,80};
SDL_Rect hitbox3 = {0,490,920,80};


SDL_Texture* backarrowskin = nullptr;

Mix_Chunk* music = nullptr;

SDL_Texture* tutorialSkin = nullptr;

//Setting Up the Multi-Dimensional array
void game::stageArray()
{
    //Loops through all of the array
    for (int y = 0; y < STAGE_HEIGHT; y++)
    {
        for (int x = 0 ; x < STAGE_WIDTH; x++)
        {
            stagePosArr[x][y] = {stageMultiX,stageMultiY,32,32};

            stageMultiX += 32;
        }
        stageMultiY += 32;
        stageMultiX = 350;
    }
}

//Creates the Textures
void game::createblock()
{
    cursor = PE_Texture::loadTexture("assets\\cursor2.png");
    blocksheet = PE_Texture::loadTexture("assets\\blocksheet.png");
    border = PE_Texture::loadTexture("assets\\border.png");
    backgroundIMG1 = PE_Texture::loadTexture("assets\\backgroundlayer1.png");
    backgroundRunnerIMG = PE_Texture::loadTexture("assets\\backgroundrunner.png");
    backgroundIMG2 = PE_Texture::loadTexture("assets\\backgroundlayer2.png");
    overlaySkin = PE_Texture::loadTexture("assets\\screenover.png");
    mainmenuSkin = PE_Texture::loadTexture("assets\\text.png");
    highlight = PE_Texture::loadTexture("assets\\highlight.png");
    backarrowskin = PE_Texture::loadTexture("assets\\back.png");
    music = Mix_LoadWAV("assets\\Vapour.wav");
    tutorialSkin = PE_Texture::loadTexture("assets\\tutorial.png");
    Mix_PlayChannel(-1, music, 0);
}

void game::startBoard()
{
    for(int y = STAGE_HEIGHT -1; y >= 14; y--)
    {
        for(int x = STAGE_WIDTH -1 ; x >= 0; x--)
        {
            stageIDArr[x][y] = rand() % 7;
            cursorPosX = 0;
            cursorPosY = 0;
        }
    }
}

void game::resetBoard()
{
    for(int y = 0; y < STAGE_HEIGHT; y++)
    {
        for(int x = 0; x < STAGE_WIDTH ; x++)
        {
            stageIDArr[x][y] = 0;
        }
    }
    scoreMulti = 1;
    gameSpeed = 1;
    game::points = 0;
    startBoard();
}

//Renders things onto screen
void game::render()
{

    cursorPos.x = stagePosArr[cursorPosX][cursorPosY].x;
    cursorPos.y = stagePosArr[cursorPosX][cursorPosY].y;

    SDL_RenderClear(PE_Renderer::renderer);

    SDL_RenderCopy(PE_Renderer::renderer, backgroundIMG1, nullptr, &backgroundIMG1Pos);
    SDL_RenderCopy(PE_Renderer::renderer, backgroundRunnerIMG, nullptr, &backgroundRunPos);
    SDL_RenderCopy(PE_Renderer::renderer, backgroundIMG2, nullptr, &backgroundIMG2Pos);

    //Back Panel to add Depth
    //SDL_RenderCopy(PE_Renderer::renderer,backpanel,nullptr,&boardPos);

    SDL_RenderCopy(PE_Renderer::renderer,border,nullptr,nullptr);

    PE_Texture::convertIntString(game::points,pointsLoc,32,16,0);
    PE_Texture::convertIntString(gameSpeed,difficultyLoc,32,0,0);

    //Multi-Dimensional Array
    for(int y = 0; y < STAGE_HEIGHT; y++)
    {
        for (int x = 0; x < STAGE_WIDTH; x++)
        {
            //Render the block and boarders
            switch(stageIDArr[x][y])
            {
                case(1):
                    SDL_RenderCopy(PE_Renderer::renderer,blocksheet,&heartSkinPos,&stagePosArr[x][y]);
                    break;
                case(2):
                    SDL_RenderCopy(PE_Renderer::renderer,blocksheet,&triangleSkinPos,&stagePosArr[x][y]);
                    break;
                case(3):
                    SDL_RenderCopy(PE_Renderer::renderer,blocksheet,&diamondSkinPos,&stagePosArr[x][y]);
                    break;
                case(4):
                    SDL_RenderCopy(PE_Renderer::renderer,blocksheet,&starSkinPos,&stagePosArr[x][y]);
                    break;
                case(5):
                    SDL_RenderCopy(PE_Renderer::renderer,blocksheet,&pentagonSkinPos,&stagePosArr[x][y]);
                    break;
                case(6):
                    SDL_RenderCopy(PE_Renderer::renderer,blocksheet,&circleSkinPos,&stagePosArr[x][y]);
                    break;

            }

            SDL_RenderCopy(PE_Renderer::renderer,blocksheet,&blockborderPos,&stagePosArr[x][y]);
        }
    }


    //Front Panel to add Depth
    //SDL_RenderCopy(PE_Renderer::renderer,frontpanel,nullptr,&boardPos);


    //Cursor
    SDL_RenderCopy(PE_Renderer::renderer,cursor,&cursorSrcPos,&cursorPos);

    SDL_RenderCopy(PE_Renderer::renderer,overlaySkin,nullptr,nullptr);

    SDL_RenderPresent(PE_Renderer::renderer);
}

void game::difficultyFun()
{
    if(game::points <= 1000)
    {
        scoreMulti = 1;
        gameSpeed = 1;
    }
    else if(game::points <= 2000)
    {
        scoreMulti = 2;
        gameSpeed = 2;
    }
    else if(game::points <= 3000)
    {
        scoreMulti = 3;
        gameSpeed = 3;
    }
    else if(game::points <= 4000)
    {
        scoreMulti = 4;
        gameSpeed = 4;
    }
    else if(game::points <= 5000)
    {
        scoreMulti = 5;
        gameSpeed = 5;
    }
    else
    {
        scoreMulti = 6;
        gameSpeed = 6;
    }
}

void game::difficulty(char input)
{
    if(input == '+')
    {
        if(gameSpeed < 5)
        {
            gameSpeed++;
            scoreMulti++;
        }
        else
        {
            gameSpeed = 5;
            scoreMulti = 5;
        }
    }
    if(input == '-')
    {
        if(gameSpeed > 1)
        {
            gameSpeed--;
            scoreMulti--;
        }
        else
        {
            gameSpeed = 1;
            scoreMulti = 1;
        }

    }
}

/*
//Offsets the renderer (WIP)
void game::renderOffset()
{
    if(boardPos.x >= -3)
    {
        boardPos.x = boardPos.x + renderOffsetX;
    }
    else if(boardPos.x <= 3)
    {
        boardPos.x = boardPos.x - renderOffsetX;
    }
}
*/

//Handles Events
void game::events(SDL_Event* e)
{
    //Checks if Key is released
    if (e->type == SDL_KEYUP || e->type == SDL_MOUSEBUTTONUP)
    {
        action = true;
    }
    if(e->type == SDL_MOUSEMOTION)
    {
        actionMouse = true;
    }
    if(e->type == SDL_MOUSEBUTTONUP)
    {
        actionMouseButton = true;
    }
    // If key has been released take action
    if(action == true)
    {
        //Check which key was triggered
        switch(e->key.keysym.sym)
        {
        case SDLK_w:
            //Check if the cursor will be out of bounds
            checkcursorbound('w');
            //Action Finished
            action = false;
            break;
        case SDLK_a:
            checkcursorbound('a');
            action = false;
            break;
        case SDLK_s:
            checkcursorbound('s');
            action = false;
            break;
        case SDLK_d:
            checkcursorbound('d');
            action = false;
            break;
        case SDLK_r:
            resetBoard();
            break;
        case SDLK_SPACE:
            switchBlock();
            break;
        case SDLK_b:
            spawnRow();
            break;
        case SDLK_PERIOD:
            difficulty('+');
            break;
        case SDLK_COMMA:
            difficulty('-');
            break;
        case SDLK_ESCAPE:
            game::menuPlace = 0;
        }
        //Action Finished
        action = false;
    }

    if(actionMouse == true)
    {
        SDL_GetMouseState(&mouseX,&mouseY);

        for(int x = 0; x < STAGE_WIDTH; x++)
        {
            for(int y = 0; y < STAGE_HEIGHT; y++)
            {
                //  Min.                               Max.
                if((stagePosArr[x][y].x <= mouseX) && (stagePosArr[x][y].x + stagePosArr[x][y].w >= mouseX))
                {
                    if((stagePosArr[x][y].y <= mouseY) && (stagePosArr[x][y].y + stagePosArr[x][y].h >= mouseY))
                    {
                        if(x >= 10)
                        {
                            cursorPosX = x - 1;
                        }
                        else
                        {
                            cursorPosX = x;
                        }
                        cursorPosY = y;
                    }
                }
            }
        }

        actionMouse = false;

    }

    if(actionMouseButton == true)
    {

        if( e->button.button == SDL_BUTTON_LEFT || e->button.button == SDL_BUTTON_RIGHT)
        {
            switchBlock();
        }
        actionMouseButton = false;

    }
}

//Checks if cursors out of bounds
void game::checkcursorbound(char letter)
{
    //Checks the Character Passed
    if (letter == 'w')
    {
        //Checks if it will go out of bounds
        if (cursorPosY > 0)
        {
            //Move the cursor
            cursorPosY--;
        }
    }
    if (letter == 'a')
    {
        if (cursorPosX > 0)
        {
            cursorPosX--;
        }
    }
    if (letter == 's')
    {
        if (cursorPosY < 15)
        {
            cursorPosY++;
        }
    }
    if (letter == 'd')
    {
        if (cursorPosX < 9)
        {
            cursorPosX++;
        }
    }
}

//Animate the Cursor
void game::cursorAnimate()
{
    //Counter to delay the animation
    if (animatecounter == 20)
    {
        //Move the SrcPos up or down depending
        if (cursorSrcPos.y == 0)
        {
            cursorSrcPos.y = cursorSrcPos.y + 32;
            animatecounter = 0;
        }
        else if (cursorSrcPos.y == 32)
        {
            cursorSrcPos.y = cursorSrcPos.y - 32;
            animatecounter = 0;
        }
    }
    else
    {
        //Add to counter
        animatecounter++;
    }

}

void game::parallax(SDL_Event* e)
{
    SDL_GetMouseState( &mouseX, &mouseY);
     renderOffsetX = mouseX - 460;
}

// Garbage Collection
void game::quit()
{
    //Destroy and free Textures
    SDL_DestroyTexture(heartblockskin);
    heartblockskin = nullptr;
    SDL_DestroyTexture(backpanel);
    backpanel = nullptr;
    SDL_DestroyTexture(frontpanel);
    frontpanel = nullptr;
    SDL_DestroyTexture(cursor);
    cursor = nullptr;
    SDL_DestroyTexture(blocksheet);
    blocksheet = nullptr;
    SDL_DestroyTexture(diamond);
    diamond = nullptr;
    SDL_DestroyTexture(star);
    star = nullptr;
    SDL_DestroyTexture(triangle);
    triangle = nullptr;
    SDL_DestroyTexture(border);
    border = nullptr;


}

void game::blockScan()
{
    for(int y = 0; y < STAGE_HEIGHT; y++ )
    {
        for(int x = 0; x < STAGE_WIDTH; x++)
        {
            if(stageIDArr[x][y] != 0)
            {
                //Check Recurring Blocks
                    //check below
                    if(stageIDArr[x][y] == stageIDArr[x][y + 1] && y + 1 <= 16)
                    {
                        for(int multi = 1; multi <= 11; multi++)
                        {
                            if((stageIDArr[x][y] != stageIDArr[x][y + multi])||(y + multi >= 19))
                            {
                                if(multi >= 3)
                                {
                                    subDown = multi;
                                    subDownBool = true;
                                    /*
                                    std::cout<<multi<<std::endl;
                                    for(int temp = 0; temp <= multi - 1; temp++)
                                    {
                                        stageIDArr[x][y + temp] = 0;
                                        std::cout<<"block removed at " << x <<" "<< y + temp <<std::endl;
                                    }
                                    */
                                    break;
                                }
                                else
                                {
                                    break;
                                }
                            }
                        }
                    }
                    //check right
                    if(stageIDArr[x][y] == stageIDArr[x + 1][y] && x + 1 <= 12)
                    {
                        for(int multi = 1; multi <= 10; multi++)
                        {
                            if((stageIDArr[x][y] != stageIDArr[x + multi][y])||(x + multi >= 11))
                            {
                                if(multi >= 3)
                                {
                                    for(int temp = 0; temp <= multi - 1; temp++)
                                    {
                                        stageIDArr[x + temp][y] = 0;
                                    }
                                    game::points = game::points + (multi * 10) * scoreMulti;
                                    std::cout<<"Points: "<<game::points<<std::endl;
                                    break;
                                }
                                else
                                {

                                    break;
                                }
                            }
                        }
                    }
                    if(subDownBool == true)
                    {
                        for (int dtemp = 0; dtemp <= subDown - 1; dtemp++)
                        {
                            stageIDArr[x][y + dtemp] = 0;
                        }
                        game::points = game::points + (subDown * 10) * scoreMulti;
                        std::cout<<"Points: "<<game::points<<std::endl;
                        subDownBool = false;
                    }
            }
        }
    }
}





void game::obeyGravity()
{
    for(int y = STAGE_HEIGHT - 1; y >= 0; y-- )
    {
        for(int x = STAGE_WIDTH - 1; x >= 0; x--)
        {
            // only run when above the 18 y zone
            if(y < 15)
            {
                //Checks if the space under the block is clear, if it is move it down one
                if(stageIDArr[x][y+1] == 0)
                {
                    stageIDArr[x][y + 1] = stageIDArr[x][y];
                    stageIDArr[x][y] = 0;
                }
            }
        }
    }
}

void game::switchBlock()
{
    tempBlock = stageIDArr[cursorPosX][cursorPosY];

    stageIDArr[cursorPosX][cursorPosY] = stageIDArr[cursorPosX + 1][cursorPosY];

    stageIDArr[cursorPosX + 1][cursorPosY] = tempBlock;
}

void game::spawnRow()
{
    for(int ix = 0; ix < STAGE_WIDTH; ix++)
    {
        if(stageIDArr[ix][STAGE_HEIGHT] != 0)
        {
            game::menuPlace = 4;
        }
    }
    for(int x = 0; x < STAGE_WIDTH; x++)
    {
        std::cout<<x<<std::endl;
        for(int y = 0; y < STAGE_HEIGHT; y++)
        {
            if(stageIDArr[x][y] > 0)
            {
                stageIDArr[x][y - 1] = stageIDArr[x][y];
                stageIDArr[x][y] = 0;
            }
            if(y == STAGE_HEIGHT - 1)
            {
                stageIDArr[x][STAGE_HEIGHT - 1] =  rand()% 7;
            }
        }
    }
}

void game::timer()
{
    if (game::counter == 0)
    {
        game::spawnRow();
        game::counter = COUNTER / gameSpeed;
    }
    else
    {
        game::counter--;
    }
}

void game::background()
{
    //Comparitors
    //Background Purple
    if(backgroundIMG1Pos.y >= -100)
    {
        back1LeftMove = true;
    }
    else if(backgroundIMG1Pos.y <= -250)
    {
        back1LeftMove = false;
    }

    //Background Blue
    if(backgroundIMG2Pos.y >= 0)
    {
        back2LeftMove = true;
    }
    else if(backgroundIMG2Pos.y <= 300)
    {
        back2LeftMove = false;
    }

    //Background Runner
    if(backgroundRunPos.x >= -800)
    {
        runnerLeftMove = true;
    }
    else if(backgroundRunPos.x <= -1500)
    {
        runnerLeftMove = false;
    }


    //Bools
    if(runnerLeftMove == true)
    {
        backgroundRunPos.x-= 10 * gameSpeed;
    }
    else if(runnerLeftMove == false)
    {
    backgroundRunPos.x = 800;
    }

    if(back1LeftMove == true)
    {
        backgroundIMG1Pos.y--;
    }
    else if(back1LeftMove == false)
    {
        backgroundIMG1Pos.y++;
    }

    if(back2LeftMove == true)
    {
        backgroundIMG2Pos.y--;
    }
    else if(back2LeftMove == false)
    {
        backgroundIMG2Pos.y++;
    }
}

/** Main Menu **/



void game::renderMainMenu()
{
    SDL_RenderClear(PE_Renderer::renderer);

    SDL_RenderCopy(PE_Renderer::renderer, backgroundIMG1, nullptr, &backgroundIMG1Pos);
    SDL_RenderCopy(PE_Renderer::renderer, backgroundRunnerIMG, nullptr, &backgroundRunPos);
    SDL_RenderCopy(PE_Renderer::renderer, backgroundIMG2, nullptr, &backgroundIMG2Pos);

    SDL_RenderCopy(PE_Renderer::renderer,mainmenuSkin,nullptr,nullptr);

    SDL_RenderCopy(PE_Renderer::renderer,highlight,nullptr,&highlightPos);

    SDL_RenderCopy(PE_Renderer::renderer,overlaySkin,nullptr,nullptr);

    SDL_RenderPresent(PE_Renderer::renderer);
}

void game::eventMainMenu(SDL_Event* e)
{
    SDL_GetMouseState(&mouseX,&mouseY);
    if(e->type == SDL_MOUSEMOTION)
    {
        actionMouse = true;
    }
    if(e->type == SDL_MOUSEBUTTONUP)
    {
        actionMouseButton = true;
    }

    if(actionMouse == true)
    {

        if(mouseY >= hitbox1.y && mouseY <= hitbox1.y + hitbox1.h)
        {
            highlightPos.y = hitbox1.y;
        }
        if(mouseY >= hitbox2.y && mouseY <= hitbox2.y + hitbox2.h)
        {
            highlightPos.y = hitbox2.y;
        }
        if(mouseY >= hitbox3.y && mouseY <= hitbox3.y + hitbox3.h)
        {
            highlightPos.y = hitbox3.y;
        }
        actionMouse = false;
    }

    if(actionMouseButton == true)
    {
        if( e->button.button == SDL_BUTTON_LEFT || e->button.button == SDL_BUTTON_RIGHT)
        {
            if(highlightPos.y == hitbox1.y)
            {
                game::menuPlace = 2;
            }
            if(highlightPos.y == hitbox2.y)
            {
                game::menuPlace = 1;
            }
            if(highlightPos.y == hitbox3.y)
            {
                game::menuPlace = 3;
            }
        }
    }

}

void game::backgroundMusic()
{

}

void game::tutorialSetup()
{
     for(int y = 0; y < STAGE_HEIGHT - 1; y++ )
    {
        for(int x = 0; x < STAGE_WIDTH - 1; x++)
        {
            stageIDArr[x][y] = 0;
        }
    }
}

void game::tutorialRender()
{
    SDL_RenderClear(PE_Renderer::renderer);

    SDL_RenderCopy(PE_Renderer::renderer, backgroundIMG1, nullptr, &backgroundIMG1Pos);
    SDL_RenderCopy(PE_Renderer::renderer, backgroundRunnerIMG, nullptr, &backgroundRunPos);
    SDL_RenderCopy(PE_Renderer::renderer, backgroundIMG2, nullptr, &backgroundIMG2Pos);

    SDL_RenderCopy(PE_Renderer::renderer, tutorialSkin, nullptr, nullptr);

    SDL_RenderCopy(PE_Renderer::renderer,overlaySkin,nullptr,nullptr);

    SDL_RenderPresent(PE_Renderer::renderer);
}
