#include "Mouse.h"

void Motion_MM(Text tabMT[],Text tabMAT[],Image tabM, SDL_Event event, SDL_Surface *screen, int *i, Config *Confg)
{
    int x, y;
    Mix_Chunk *sound;
    x = event.motion.x;
    y = event.motion.y;
    SDL_PollEvent(&event);
    if ((x > 50 && x < 380) && (y > 430 && y < 480))
    {
        if (*i != 1)
        {
            PlayChunkMusic("assets/Sound/chunk.wav", sound);
            *i = 1;
            AffichageMainMenu(screen, tabMT, tabMAT, tabM, *i, Confg->LevelR, Confg->Player);
            SDL_Flip(screen);
        }
    }

    else if ((x > 50 && x < 380) && (y > 560 && y < 610))
    {
        if (*i != 2)
        {
            PlayChunkMusic("assets/Sound/chunk.wav", sound);
            *i = 2;
            AffichageMainMenu(screen, tabMT, tabMAT, tabM, *i, Confg->LevelR, Confg->Player);
            SDL_Flip(screen);
        }
    }

    else if ((x > 50 && x < 380) && (y > 690 && y < 740))
    {
        if (*i != 3)
        {
            PlayChunkMusic("assets/Sound/chunk.wav", sound);
            *i = 3;
            AffichageMainMenu(screen, tabMT, tabMAT, tabM, *i, Confg->LevelR, Confg->Player);
            SDL_Flip(screen);
        }
    }

    else if ((x > 50 && x < 380) && (y > 820 && y < 870))
    {
        if (*i != 4)
        {
            PlayChunkMusic("assets/Sound/chunk.wav", sound);
            *i = 4;
            AffichageMainMenu(screen, tabMT, tabMAT, tabM, *i, Confg->LevelR, Confg->Player);
            SDL_Flip(screen);
        }
    }

    else
    {
        if (*i != 0)
        {
            *i = 0;
            AffichageMainMenu(screen, tabMT, tabMAT, tabM, *i, Confg->LevelR, Confg->Player);
            SDL_Flip(screen);
        }
    }
}

void Motion_MG(Image *tabMG, SDL_Surface *screen,SDL_Event event, int *i)
{
    int x, y;
    x = event.motion.x;
    y = event.motion.y;
    
    if (x > 819 && x < 1081 && y > 322 && y < 405)
    {
        if (*i != 1)
        {
            *i = 1;
            AfficherImg(tabMG[*i + 5], screen);
            SDL_Flip(screen);
        }
    }

    else if (x > 819 && x < 1081 && y > 437 && y < 521)
    {

        if (*i != 2)
        {
            *i = 2;
            AfficherImg(tabMG[*i + 5], screen);
            SDL_Flip(screen);
        }
    }
    else if (x > 819 && x < 1081 && y > 553 && y < 637)
    {
        if (*i != 3)
        {
            *i = 3;
            AfficherImg(tabMG[*i + 5], screen);
            SDL_Flip(screen);
        }
    }

    else if (x > 819 && x < 1081 && y > 669 && y < 753)
    {
        if (*i != 4)
        {
            *i = 4;
            AfficherImg(tabMG[*i + 5], screen);
            SDL_Flip(screen);
        }
    }
    else if (x > 904 && x < 1016 && y > 801 && y < 900)
    {
        if (*i != 5)
        {
            *i = 5;
            AfficherImg(tabMG[*i + 5], screen);
            SDL_Flip(screen);
        }
    }
    else if (*i != 0)
    {
        *i = 0;
        for (int j = 1; j < 6; j++)
            AfficherImg(tabMG[j], screen);
        SDL_Flip(screen);
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