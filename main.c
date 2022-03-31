#include "Main_Fn.h"
#include "Text_Image.h"
#include "Menu.h"
#include "Mouse.h"
#include "ennemy.h"
#include "minimap.h"

int main()
{
    // Declaration & Init
    Config *Confg = (Config *)malloc(sizeof(Config));

    SDL_Surface *screen;
    SDL_Event event;
    Mix_Chunk *sound;
    Mix_Music *music;

    int i = 0, isRunning;
    int last_frame_time = 0;
    float delta_time;
    Image tabM[5];
    Text tabMT[5];
    Text tabMAT[5];

    // Init Image
    InitBackg(&tabM[0], "assets/MainMenu/Level-1-Perso-3.png");
    InitBackg(&tabM[1], "assets/MainMenu/Level-2-Perso-3.png");
    InitBackg(&tabM[2], "assets/MainMenu/Level-2-Perso-2.png");
    InitBackg(&tabM[3], "assets/MainMenu/Level-3-Perso-3.png");
    InitBackg(&tabM[4], "assets/MainMenu/Level-3-Perso-2.png");
    InitBackg(&tabM[5], "assets/MainMenu/Level-3-Perso-1.png");
    // End Init

    Confg->isRunning = Setup(Confg);

    if (Confg->isRunning)
    {
        InitTxt_en(tabMT, tabMAT);
        screen = SDL_SetVideoMode(Width, Height, Bpp, SDL_HWSURFACE | SDL_DOUBLEBUF);
        PlayMusic("assets/Sound/son.wav", music);
        AffichageMainMenu(screen, tabMT, tabMAT, tabM, i, Confg->LevelR, Confg->Player);
        SDL_Flip(screen);
    }

    while (Confg->isRunning)
    {

        // while (!(SDL_GetTicks() > last_frame_time + FRAME_TARGET_TIME));
        // last_frame_time = SDL_GetTicks();
        // delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
        SDL_WaitEvent(&event);

        switch (event.type)
        {
        case SDL_QUIT:
            Confg->isRunning = 0;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                Confg->isRunning = 0;
                break;
            case SDLK_UP:
                PlayChunkMusic("assets/Sound/chunk.wav", sound);
                if (i > 1)
                    i--;
                else
                    i = 4;
                AffichageMainMenu(screen, tabMT, tabMAT, tabM, i, Confg->LevelR, Confg->Player);
                SDL_Flip(screen);
                break;

            case SDLK_DOWN:
                PlayChunkMusic("assets/Sound/chunk.wav", sound);
                if (i < 4)
                    i++;
                else
                    i = 1;
                AffichageMainMenu(screen, tabMT, tabMAT, tabM, i, Confg->LevelR, Confg->Player);
                SDL_Flip(screen);
                break;
            case SDLK_f:
                if (Confg->Fullscr > 0)
                    screen = SDL_SetVideoMode(Width, Height, Bpp, SDL_HWSURFACE | SDL_FULLSCREEN);
                else
                    screen = SDL_SetVideoMode(Width, Height, Bpp, SDL_HWSURFACE);
                Confg->Fullscr *= -1;
                AffichageMainMenu(screen, tabMT, tabMAT, tabM, i, Confg->LevelR, Confg->Player);
                SDL_Flip(screen);
                break;
            case SDLK_RETURN:
                switch (i)
                {
                case 1:
                    MenuNG(screen, Confg);
                    i = 0;
                    AffichageMainMenu(screen, tabMT, tabMAT, tabM, i, Confg->LevelR, Confg->Player);
                    SDL_Flip(screen);

                    break;
                case 2:
                    MenuOpt(screen, Confg);
                    if (Confg->Lang > 0)
                        InitTxt_en(tabMT, tabMAT);
                    else
                        InitTxt_fr(tabMT, tabMAT);
                    i = 0;
                    AffichageMainMenu(screen, tabMT, tabMAT, tabM, i, Confg->LevelR, Confg->Player);
                    SDL_Flip(screen);

                    break;
                case 3:

                    i = 0;
                    break;
                case 4:
                    Confg->isRunning = 0;
                    break;
                }
                break;
            }
            break;

        case SDL_MOUSEMOTION:
            Motion_MM(tabMT, tabMAT, tabM, event, screen, &i, Confg);
            break;

        case SDL_MOUSEBUTTONDOWN:
            switch (i)
            {
            case 1:
                MenuNG(screen, Confg);
                AffichageMainMenu(screen, tabMT, tabMAT, tabM, i, Confg->LevelR, Confg->Player);
                SDL_Flip(screen);
                i = 0;
                break;
            case 2:
                MenuOpt(screen, Confg);
                if (Confg->Lang > 0)
                    InitTxt_en(tabMT, tabMAT);
                else
                    InitTxt_fr(tabMT, tabMAT);
                AffichageMainMenu(screen, tabMT, tabMAT, tabM, i, Confg->LevelR, Confg->Player);
                SDL_Flip(screen);
                i = 0;
                break;
            case 3:
                i = 0;
                break;
            case 4:
                Confg->isRunning = 0;
                break;
            }

            break;
        }
    }

    // Liberer_Mus(music);
    /**/
    /*
        for (int i = 0; i < 6; i++)
            Liberer_Img(tabI->tabMO[i]);

        for (int i = 0; i < 3; i++)
            Liberer_Img(tabI->tabMAO[i]);

        for (int i = 0; i < 11; i++)
            Liberer_Img(tabMG[i]);

        for (int i = 0; i < 5; i++)
        {
            Liberer_txt(tabMT[i]);
            Liberer_txt(tabMAT[i]);
        }
    */

    // TTF_Quit();
    // SDL_Quit();

    printf("\nGame ShutDown !\n");
}