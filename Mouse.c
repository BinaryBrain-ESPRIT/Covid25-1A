#include "Mouse.h"

void Motion_MM(Text tabMT[], Text tabMAT[], Image tabM[][3], SDL_Event event, SDL_Surface *screen, int *i, Config *Confg)
{
    int x, y, j;
    Mix_Chunk *sound;
    SDL_PollEvent(&event);

    x = event.motion.x;
    y = event.motion.y;

    for (j = 0; j < 6; j++)
    {
        int posX = tabMT[j].pos.x;
        int posX1 = posX + tabMT[j].surfaceText->w;
        int posY = tabMT[j].pos.y;
        int posY1 = posY + tabMT[j].surfaceText->h;
        if (x > posX && x < posX1 && y > posY && y < posY1)
        {
            if (*i != (j + 1))
            {
                PlayChunkMusic("assets/Sound/chunk.wav", sound);
                *i = j + 1;
            }
            break;
        }
    }
    if (j >= 6)
    {
        if (x > 1620 && x < 1920 && y > 300 && y < 415)
        {
            if (*i != 7)
                *i = 7;
        }

        else if (x > 1620 && x < 1920 && y > 730 && y < 850)
        {
            if (*i != 8)
                *i = 8;
        }
        else
        {
            if (i != 0)
            {
                *i = 0;
            }
        }
    }
}

void Motion_MG(Image tabMG[], SDL_Surface *screen, SDL_Event event, int *i)
{
    Mix_Chunk *sound;
    int x, y, j;
    SDL_PollEvent(&event);
    x = event.motion.x;
    y = event.motion.y;

    for (j = 1; j < 6; j++)
    {
        int posX = tabMG[j].pos.x;
        int posX1 = posX + tabMG[j].img->w;
        int posY = tabMG[j].pos.y;
        int posY1 = posY + tabMG[j].img->h;

        if (x > posX && x < posX1 && y > posY && y < posY1)
        {
            if (*i != (j + 1))
            {
                PlayChunkMusic("assets/Sound/chunk.wav", sound);
                *i = j + 1;
                AfficherImg(tabMG[*i + 4], screen);
                SDL_Flip(screen);
            }
            break;
        }
        else
        {
            if (*i != 0)
            {
                *i = 0;
                for (int j = 1; j < 6; j++)
                    AfficherImg(tabMG[j], screen);
                SDL_Flip(screen);
            }
        }
    }
}
void Motion_MO(SDL_Surface *screen, Config *Confg, SDL_Event event, Image *tabMO, Image *tabMAO, int *i)
{
    int x, y;
    x = event.motion.x;
    y = event.motion.y;
    Mix_Chunk *sound;

    if ((x > 715 && x < 1230) && (y > 450 && y < 605))
    {
        if (*i != 1)
        {
            PlayChunkMusic("assets/Sound/chunk.wav", sound);
            *i = 1;
            AffichageMenuOpt(screen, tabMO, tabMAO, *i);

            SDL_Flip(screen);
        }
    }

    else if ((x > 715 && x < 1230) && (y > 701 && y < 860))
    {
        if (*i != 2)
        {
            PlayChunkMusic("assets/Sound/chunk.wav", sound);
            *i = 2;
            AffichageMenuOpt(screen, tabMO, tabMAO, *i);

            SDL_Flip(screen);
        }
    }

    else if ((x > 816 && x < 1101) && (y > 949 && y < 1035))
    {
        if (*i != 3)
        {
            PlayChunkMusic("assets/Sound/chunk.wav", sound);
            *i = 3;
            AffichageMenuOpt(screen, tabMO, tabMAO, *i);

            SDL_Flip(screen);
        }
    }
    else if ((y > tabMO[2].pos.y && y < tabMO[2].pos.y + 41))
    {
        if (*i != 4)
        {
            *i = 4;
        }
    }

    else
    {
        if (*i != 0)
        {
            *i = 0;
            AffichageMenuOpt(screen, tabMO, tabMAO, *i);

            SDL_Flip(screen);
        }
    }
}

int MotionSL(Image LevelBut[], int j, SDL_Event event, int LevelSelected)
{
    SDL_Rect tabPos[20];

    int x = event.motion.x;
    int y = event.motion.y;
    int posX, posX1, posY, posY1;
    switch (LevelSelected)
    {
    case 0:
        for (int i = 0; i < 4; i++)
        {
            posX = LevelBut[i].pos.x;
            posY = LevelBut[i].pos.y;
            posX1 = posX + LevelBut[i].img->w;
            posY1 = posY + LevelBut[i].img->h;

            if (x > posX && x < posX1 && y > posY && y < posY1)
                return i + 10;
        }
        break;

    case 1:
        for (int i = 0; i < 6; i++)
        {
            if (i != 0)
            {
                posX = LevelBut[i].pos.x;
                posY = LevelBut[i].pos.y;
                posX1 = posX + LevelBut[i].img->w;
                posY1 = posY + LevelBut[i].img->h;

                if (x > posX && x < posX1 && y > posY && y < posY1)
                    return i + 10;
            }
        }
        break;
    case 2:
        for (int i = 0; i < 8; i++)
        {
            if (i != 1)
            {
                posX = LevelBut[i].pos.x;
                posY = LevelBut[i].pos.y;
                posX1 = posX + LevelBut[i].img->w;
                posY1 = posY + LevelBut[i].img->h;

                if (x > posX && x < posX1 && y > posY && y < posY1)
                    return i + 10;
            }
        }
        break;
    case 3:
        for (int i = 0; i < 10; i++)
        {
            if (i != 2)
            {
                posX = LevelBut[i].pos.x;
                posY = LevelBut[i].pos.y;
                posX1 = posX + LevelBut[i].img->w;
                posY1 = posY + LevelBut[i].img->h;

                if (x > posX && x < posX1 && y > posY && y < posY1)
                    return i + 10;
            }
        }
        break;
    }

    if (j != -1)
        return -1;
    else
        return -2;
}