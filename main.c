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
    char NomBackg[40];
    int i = 0, isRunning;
    int last_frame_time = 0;
    float delta_time;
    Image tabM[3][3];
    Text tabMT[6];
    Text tabMAT[6], MoneyTxt;
    SDL_Color MoneyColor = {57, 181, 74};
    char Money[5];
    Image MoneyImg;
    // Init Image

    // End Init

    Confg->isRunning = Setup(Confg);

    if (Confg->isRunning)
    {
        if (Confg->Lang > 0)
            InitTxt_en(tabMT, tabMAT);
        else
            InitTxt_fr(tabMT, tabMAT);

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < i + 1; j++)
            {
                sprintf(NomBackg, "assets/MainMenu/Level-%d-Perso-%d.png", i + 1, j + 1);
                InitBackg(&tabM[i][j], NomBackg);
            }
        }
        if (Confg->Fullscr > 0)
            screen = SDL_SetVideoMode(Width, Height, Bpp, SDL_HWSURFACE);
        else
            screen = SDL_SetVideoMode(Width, Height, Bpp, SDL_HWSURFACE | SDL_FULLSCREEN);

        sprintf(Money, "%d $", Confg->Money);
        initTxt(&MoneyTxt, 1692, 57, MoneyColor, 35, "assets/Font/AznKnucklesTrial-z85pa.otf", Money);
        initImg(&MoneyImg, 1596, 43, "assets/MainMenu/Money.png");
        PlayMusic("assets/Sound/son.wav", music);

        AffichageMainMenu(screen, tabMT, tabMAT, tabM, i, Confg->LevelR, Confg->Player);
        AfficherImg(MoneyImg, screen);
        Afficher_txt(MoneyTxt, screen);

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
                Afficher_txt(MoneyTxt, screen);
                SDL_Flip(screen);
                break;
            case SDLK_f:
                if (Confg->Fullscr > 0)
                    screen = SDL_SetVideoMode(Width, Height, Bpp, SDL_HWSURFACE | SDL_FULLSCREEN);
                else
                    screen = SDL_SetVideoMode(Width, Height, Bpp, SDL_HWSURFACE);
                Confg->Fullscr *= -1;
                AffichageMainMenu(screen, tabMT, tabMAT, tabM, i, Confg->LevelR, Confg->Player);
                Afficher_txt(MoneyTxt, screen);
                SDL_Flip(screen);
                break;
            case SDLK_RETURN:
                switch (i)
                {
                case 1:
                    SelectLevel(screen, Confg);
                    i = 0;
                    AffichageMainMenu(screen, tabMT, tabMAT, tabM, i, Confg->LevelR, Confg->Player);
                    Afficher_txt(MoneyTxt, screen);
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
                    Afficher_txt(MoneyTxt, screen);
                    SDL_Flip(screen);

                    break;
                case 5:
                    AffichageCredits(screen, Confg);
                    i = 0;
                    AffichageMainMenu(screen, tabMT, tabMAT, tabM, i, Confg->LevelR, Confg->Player);
                    Afficher_txt(MoneyTxt, screen);
                    SDL_Flip(screen);
                    break;
                case 6:
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
                SelectLevel(screen, Confg);

                AffichageMainMenu(screen, tabMT, tabMAT, tabM, i, Confg->LevelR, Confg->Player);
                Afficher_txt(MoneyTxt, screen);
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
                Afficher_txt(MoneyTxt, screen);
                SDL_Flip(screen);
                i = 0;
                break;
            case 5:
                AffichageCredits(screen, Confg);
                i = 0;
                AffichageMainMenu(screen, tabMT, tabMAT, tabM, i, Confg->LevelR, Confg->Player);
                Afficher_txt(MoneyTxt, screen);
                SDL_Flip(screen);
                break;
            case 6:
                Confg->isRunning = 0;
                break;
            case 7:
                if (Confg->LevelR == 2)
                    if (Confg->Player == 3)
                        Confg->Player = 2;
                    else
                        Confg->Player = 3;
                else if (Confg->LevelR == 3)
                    if (Confg->Player == 3)
                        Confg->Player = 1;
                    else if (Confg->Player == 2)
                        Confg->Player = 3;
                    else
                        Confg->Player = 2;
                AffichageMainMenu(screen, tabMT, tabMAT, tabM, 0, Confg->LevelR, Confg->Player);
                Afficher_txt(MoneyTxt, screen);
                SDL_Flip(screen);
                break;
            case 8:
                if (Confg->LevelR == 3)
                    if (Confg->Player == 3)
                        Confg->Player = 2;
                    else if (Confg->Player == 2)
                        Confg->Player = 1;
                    else
                        Confg->Player = 3;
                AffichageMainMenu(screen, tabMT, tabMAT, tabM, 0, Confg->LevelR, Confg->Player);
                Afficher_txt(MoneyTxt, screen);
                SDL_Flip(screen);
                break;
            }

            break;
        }
    }
    // SaveSetting
    SaveSetting(Confg);

    // Liberer_Mus(music);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < i + 1; j++)
            Liberer_Img(tabM[i][j]);

    for (int i = 0; i < 5; i++)
    {
        // Liberer_txt(tabMT[i]);
        // Liberer_txt(tabMAT[i]);
    }

    free(Confg);
    TTF_Quit();
    SDL_Quit();

    printf("\nGame ShutDown !\n");
}