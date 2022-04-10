#include "Mouse.h"

void Motion_MM(Text tabMT[], Text tabMAT[], Image tabM[][3], SDL_Event event, SDL_Surface *screen, int *i, Config *Confg)
{
    int x, y;
    Mix_Chunk *sound;
    x = event.motion.x;
    y = event.motion.y;
    // printf("x= %d y =%d\n",x,y);
    SDL_PollEvent(&event);
    if ((x > 27 && x < 432) && (y > 371 && y < 454))
    {
        if (*i != 1)
        {
            PlayChunkMusic("assets/Sound/chunk.wav", sound);
            *i = 1;
            AffichageMainMenu(screen, tabMT, tabMAT, tabM, *i, Confg->LevelR, Confg->Player);
            SDL_Flip(screen);
        }
    }

    else if ((x > 27 && x < 342) && (y > 482 && y < 565))
    {
        if (*i != 2)
        {
            PlayChunkMusic("assets/Sound/chunk.wav", sound);
            *i = 2;
            AffichageMainMenu(screen, tabMT, tabMAT, tabM, *i, Confg->LevelR, Confg->Player);
            SDL_Flip(screen);
        }
    }

    else if ((x > 27 && x < 269) && (y > 594 && y < 676))
    {
        if (*i != 3)
        {
            PlayChunkMusic("assets/Sound/chunk.wav", sound);
            *i = 3;
            AffichageMainMenu(screen, tabMT, tabMAT, tabM, *i, Confg->LevelR, Confg->Player);
            SDL_Flip(screen);
        }
    }

    else if ((x > 27 && x < 223) && (y > 705 && y < 788))
    {
        if (*i != 4)
        {
            PlayChunkMusic("assets/Sound/chunk.wav", sound);
            *i = 4;
            AffichageMainMenu(screen, tabMT, tabMAT, tabM, *i, Confg->LevelR, Confg->Player);
            SDL_Flip(screen);
        }
    }
    else if ((x > 27 && x < 363) && (y > 816 && y < 899))
    {
        if (*i != 5)
        {
            PlayChunkMusic("assets/Sound/chunk.wav", sound);
            *i = 5;
            AffichageMainMenu(screen, tabMT, tabMAT, tabM, *i, Confg->LevelR, Confg->Player);
            SDL_Flip(screen);
        }
    }
    else if ((x > 27 && x < 193) && (y > 927 && y < 1010))
    {
        if (*i != 6)
        {
            PlayChunkMusic("assets/Sound/chunk.wav", sound);
            *i = 6;
            AffichageMainMenu(screen, tabMT, tabMAT, tabM, *i, Confg->LevelR, Confg->Player);
            SDL_Flip(screen);
        }
    }
    else if (x > 1620 && x < 1920 && y > 300 && y < 415)
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
        if (*i != 0)
        {
            *i = 0;
            AffichageMainMenu(screen, tabMT, tabMAT, tabM, *i, Confg->LevelR, Confg->Player);
            SDL_Flip(screen);
        }
    }
}

void Motion_MG(Image *tabMG, SDL_Surface *screen, SDL_Event event, int *i)
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