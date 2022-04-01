#include "Menu.h"
#include "Main_Fn.h"
#include "minimap.h"
#include "enigme_image.h"
#include "enigme.h"
void AffichageMainMenu(SDL_Surface *screen, Text tabT[], Text tabAT[], Image tabI[], int j, int l, int p)
{
    AfficherImg(tabI[0], screen);
    if (j != 0)
    {
        for (int i = 1; i < 5; i++)
            if (i != j)
                Afficher_txt(tabT[i], screen);

        Afficher_txt(tabAT[j], screen);
    }
    else
    {
        for (int i = 1; i < 5; i++)
            Afficher_txt(tabT[i], screen);
    }
}

void AffichageMenuOpt(SDL_Surface *screen, Image tabMO[], Image tabMAO[], int j)
{
    if (j != 0)
    {
        for (int i = 1; i < 6; i++)
            if (i != j + 2)
                AfficherImg(tabMO[i], screen);

        AfficherImg(tabMAO[j - 1], screen);
    }
    else
        for (int i = 0; i < 6; i++)
            AfficherImg(tabMO[i], screen);
}

void MenuNG(SDL_Surface *screen, Config *Confg)
{

    SDL_Event event;
    int isRunning = 1;
    int Opened = 0;
    int i = 0, a = 0, x = 0;
    int last_frame_time = 0;
    int diff;
    int NoEnnemyAround;
    SDL_Rect cam = {0, 0, Width, Height};
    Player p;
    Ennemy e[5];
    minimap map;
    Enigme enig;
    enigme enig1;
    background tabG[3];
    Image tabGameUI[5];
    // Init LevelBackg
    InitGameBackg(&tabG[0], "assets/Levels/Backg/Level1.png");

    // Init GameUI
    initImg(&tabGameUI[0], 10, 20, "assets/Menu/Menu_But.png");

    // Init Ennemi
    initEnnemy(&e[0], 2500, 575, 5, 0, 2);
    initEnnemy(&e[1], 4270, 575, 5, 0, 2);
    initEnnemy(&e[2], 5640, 575, 5, 0, 2);
    initEnnemy(&e[3], 8120, 575, 5, 0, 2);
    initEnnemy(&e[4], 8800, 575, 5, 0, 2);

    // Init Player
    initPerso(&p, Confg->Player);

    // Init MiniMap
    initminimap(&map, "assets/Levels/Backg/level1mini.png", p, e);
    SDL_ShowCursor(SDL_DISABLE);

    while (isRunning)
    {
        last_frame_time = SDL_GetTicks();

        // while (!(SDL_GetTicks() > last_frame_time + FRAME_TARGET_TIME));

        if (Confg->isRunning == 0)
            isRunning = 0;

        AfficherBackg(tabG[0], screen);
        AfficherImg(tabGameUI[0], screen);
        afficherminimap(map, screen);

        MAJMinimap(p.posABS, e, &map, Redim);
        // Perso
        animerPerso(&p);
        if (p.pos.x >= screen->w / 2 && p.direction == 1)
        {
            scrolling(&tabG[0], p.direction, 10);
            p.posABS.x += 10;
            for (int i = 0; i < 5; i++)
            {
                e[i].posInit -= 10;
                e[i].pos.x -= 10;
            }
        }
        else if (p.direction == -1 && p.pos.x <= 500 && p.posABS.x > 500)
        {
            scrolling(&tabG[0], p.direction, 10);
            p.posABS.x -= 10;
            for (int i = 0; i < 5; i++)
            {
                e[i].posInit += 10;
                e[i].pos.x += 10;
            }
        }
        else
            deplacerPerso(&p, Confg->deltaTime);
        afficherPerso(p, screen);

        for (int i = 0; i < 5; i++)
        {
            if (collisionBB(e[i], p))
            {
                e[i].direction = 0;
                e[i].attack = 1;
                animerEnnemy(&e[i], Confg);
                afficherEnnemy(e[i], screen);
            }
            else
            {
                e[i].attack = 0;
                animerEnnemy(&e[i], Confg);
                deplacerIA(&e[i], p.pos);
                deplacerEnnemy(&e[i], Confg);
                afficherEnnemy(e[i], screen);
            }
        }
        // MiniMap Functions

        SDL_Flip(screen);
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_MOUSEMOTION:
            break;
        case SDL_QUIT:
            Confg->isRunning = 0;
            isRunning = 0;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_RIGHT:
                p.direction = 1;
                break;
            case SDLK_LEFT:
                p.direction = -1;
                break;
            case SDLK_TAB:
                if (!Opened)
                {
                    Opened = 1;
                    MenuInGame(screen, Confg, &Opened, &isRunning);
                    SDL_WaitEvent(&event);
                }

                break;
            case SDLK_ESCAPE:
                isRunning = 0;
                break;
            case SDLK_e:
                InitEnigme(&enig, "enigmeImg.txt");
                afficherEnigme(enig, screen);
                SDL_Flip(screen);
                int done = 0;
                int TimeSec = 0;
                int TimerInit = SDL_GetTicks();
                int Rep = 0;
                SDL_ShowCursor(SDL_ENABLE);
                while (!done)
                {
                    SDL_PollEvent(&event);
                    switch (event.type)
                    {
                    case SDL_QUIT:
                        done = 1;
                        Confg->isRunning = 0;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        if (event.button.x > 1070 && event.button.x < 1232 && event.button.y > 105 && event.button.y < 270)
                            Rep = 1;
                        else if (event.button.x > 1356 && event.button.x < 1518 && event.button.y > 105 && event.button.y < 270)
                            Rep = 2;
                        else if (event.button.x > 1212 && event.button.x < 1374 && event.button.y > 363 && event.button.y < 527)
                            Rep = 3;

                        if (Rep > 0 && Rep < 4)
                        {
                            if (Rep == enig.NumRC)
                            {
                                AfficherImg(enig.Backg[1], screen);
                                SDL_Flip(screen);
                                SDL_Delay(2000);
                            }
                            else
                            {
                                AfficherImg(enig.Backg[2], screen);
                                SDL_Flip(screen);
                                SDL_Delay(2000);
                            }
                            done = 1;
                        }
                        break;
                    }

                    int timer = (SDL_GetTicks() - TimerInit) / 1000;

                    if (timer != TimeSec)
                    {
                        TimeSec = timer;
                        animer(&enig, screen);
                        SDL_Flip(screen);
                        if (enig.TimerI >= 10)
                            done = 1;
                    }
                }
                SDL_ShowCursor(SDL_DISABLE);
                break;
            case SDLK_t:
                InitEnigme1(&enig1, "enigme.txt");
                afficherEnigme1(enig1, screen);
                SDL_Flip(screen);
                done = 0;
                TimeSec = 0;
                TimerInit = SDL_GetTicks();
                Rep = 0;
                SDL_ShowCursor(SDL_ENABLE);
                while (!done)
                {
                    SDL_PollEvent(&event);
                    switch (event.type)
                    {
                    case SDL_QUIT:
                        done = 1;
                        Confg->isRunning = 0;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        if (event.button.x > 261 && event.button.x < 1232 && event.button.y > 409 && event.button.y < 270)
                            Rep = 1;
                        else if (event.button.x > 1340 && event.button.x < 1518 && event.button.y > 409 && event.button.y < 270)
                            Rep = 2;
                        else if (event.button.x > 775 && event.button.x < 1374 && event.button.y > 661 && event.button.y < 527)
                            Rep = 3;

                        if (Rep > 0 && Rep < 4)
                        {
                            if (Rep == enig1.NumRepC)
                            {
                                AfficherImg(enig1.Backg[1], screen);
                                printf("Winner\n");
                                SDL_Flip(screen);
                                SDL_Delay(2000);
                            }
                            else
                            {
                                AfficherImg(enig1.Backg[2], screen);
                                printf("Looser\n");
                                SDL_Flip(screen);
                                SDL_Delay(2000);
                            }
                            // done = 1;
                        }
                        break;
                    }

                    int timer = (SDL_GetTicks() - TimerInit) / 1000;

                    if (timer != TimeSec)
                    {
                        TimeSec = timer;
                        animer1(&enig1, screen);
                        SDL_Flip(screen);
                        if (enig1.TimerI >= 10)
                            done = 1;
                    }
                }
                SDL_ShowCursor(SDL_DISABLE);
                break;
                break;
            case SDLK_f:
                if (Confg->Fullscr > 0)
                    screen = SDL_SetVideoMode(Width, Height, Bpp, SDL_HWSURFACE | SDL_FULLSCREEN);
                else
                    screen = SDL_SetVideoMode(Width, Height, Bpp, SDL_HWSURFACE);
                Confg->Fullscr *= -1;
                AfficherBackg(tabG[0], screen);
                AfficherImg(tabGameUI[0], screen);
                SDL_Flip(screen);
                break;
            }
            break;
        case SDL_KEYUP:

            if (p.direction == 1)
                p.flipped = 0;
            else if (p.direction == -1)
                p.flipped = 1;

            p.direction = 0;

            break;
        }

        Confg->deltaTime = (SDL_GetTicks() - last_frame_time);
    }
    SDL_ShowCursor(SDL_ENABLE);
}

void MenuInGame(SDL_Surface *screen, Config *Confg, int *Opened, int *isRunning)
{
    Image tabMG[11];

    // Init Image menu In Game

    initImg(&tabMG[0], Width / 2 - 333, Height / 2 - 430, "assets/Menu/Board.png");
    initImg(&tabMG[1], Width / 2 - 212, 338 - 51, "assets/Menu/Level.png");
    initImg(&tabMG[2], Width / 2 - 212, 475 - 51, "assets/Menu/Restart.png");
    initImg(&tabMG[3], Width / 2 - 212, 613 - 51, "assets/Menu/Options.png");
    initImg(&tabMG[4], Width / 2 - 212, 752 - 51, "assets/Menu/Quit.png");
    initImg(&tabMG[5], Width / 2 - 57, 855, "assets/Menu/CloseBord.png");
    initImg(&tabMG[6], Width / 2 - 212, 336 - 51, "assets/Menu/A_Level.png");
    initImg(&tabMG[7], Width / 2 - 212, 475 - 51, "assets/Menu/A_Restart.png");
    initImg(&tabMG[8], Width / 2 - 212, 613 - 51, "assets/Menu/A_Options.png");
    initImg(&tabMG[9], Width / 2 - 212, 752 - 51, "assets/Menu/A_Quit.png");
    initImg(&tabMG[10], Width / 2 - 57, 855, "assets/Menu/A_CloseBord.png");

    // End Init

    SDL_ShowCursor(SDL_ENABLE);
    SDL_Event event;
    int done = 0, x, y, i = 0;
    for (int j = 0; j < 6; j++)
        AfficherImg(tabMG[j], screen);
    SDL_Flip(screen);
    while (!done)
    {
        if (Confg->isRunning == 0)
            done = 1;
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            Confg->isRunning = 0;
        case SDL_KEYDOWN:

            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                *Opened = 0;
                done = 1;
                break;
            }
            break;
        case SDL_MOUSEMOTION:
            Motion_MG(tabMG, screen, event, &i);
            break;
        case SDL_MOUSEBUTTONDOWN:
            switch (i)
            {
            case 3:
                MenuOpt(screen, Confg);
                for (int j = 0; j < 6; j++)
                    AfficherImg(tabMG[j], screen);
                SDL_Flip(screen);
                break;
            case 4:
                done = 1;
                *isRunning = 0;
                break;
            case 5:
                done = 1;
                *Opened = 0;
                break;
            }
            break;
        }
    }
    for (int i = 0; i < 11; i++)
        Liberer_Img(tabMG[i]);

    SDL_ShowCursor(SDL_DISABLE);
}

void MenuOpt(SDL_Surface *screen, Config *Confg)
{
    Mix_Chunk *sound;
    Image tabMO[6];
    Image tabMAO[3];
    int TimeSec = 0;
    int isRunning = 1;
    int i = 0;
    SDL_Event event;

    // Init Img
    InitBackg(&tabMO[0], "assets/MenuOpt/Background.png");
    initImg(&tabMO[1], Width / 2 - 245, 356.5, "assets/MenuOpt/volumebar.png");
    initImg(&tabMO[2], 1175, 356.5, "assets/MenuOpt/volumebut.png");

    if (Confg->Lang > 0)
        InitImg_en(tabMO, tabMAO);
    else
        InitImg_fr(tabMO, tabMAO);

    // End Init

    AffichageMenuOpt(screen, tabMO, tabMAO, i);
    SDL_Flip(screen);

    while (isRunning)
    {
        if (Confg->isRunning == 0)
            isRunning = 0;

        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            isRunning = 0;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                isRunning = 0;
                break;

            case SDLK_f:
                if (Confg->Fullscr > 0)
                    screen = SDL_SetVideoMode(Width, Height, Bpp, SDL_HWSURFACE | SDL_FULLSCREEN);
                else
                    screen = SDL_SetVideoMode(Width, Height, Bpp, SDL_HWSURFACE);
                Confg->Fullscr *= -1;

                AffichageMenuOpt(screen, tabMO, tabMAO, i);
                SDL_Flip(screen);
                break;

            case SDLK_UP:
                PlayChunkMusic("assets/Sound/chunk.wav", sound);
                if (i > 1)
                    i--;
                else
                    i = 4;
                AffichageMenuOpt(screen, tabMO, tabMAO, i);
                SDL_Flip(screen);
                break;

            case SDLK_DOWN:
                PlayChunkMusic("assets/Sound/chunk.wav", sound);
                if (i < 4)
                    i++;
                else
                    i = 1;
                AffichageMenuOpt(screen, tabMO, tabMAO, i);
                SDL_Flip(screen);
                break;
            case SDLK_RETURN:
                switch (i)
                {
                case 1:
                    if (Confg->Lang > 0)
                        InitImg_fr(tabMO, tabMAO);
                    else
                        InitImg_en(tabMO, tabMAO);
                    Confg->Lang *= -1;
                    AffichageMenuOpt(screen, tabMO, tabMAO, i);
                    SDL_Flip(screen);
                    break;
                case 2:
                    if (Confg->Fullscr > 0)
                        screen = SDL_SetVideoMode(Width, Height, Bpp, SDL_HWSURFACE | SDL_FULLSCREEN);
                    else
                        screen = SDL_SetVideoMode(Width, Height, Bpp, SDL_HWSURFACE);
                    Confg->Fullscr *= -1;

                    AffichageMenuOpt(screen, tabMO, tabMAO, i);
                    SDL_Flip(screen);
                    break;
                case 3:
                    isRunning = 0;
                    break;
                }
                break;
            }
            break;
        case SDL_MOUSEMOTION:
            Motion_MO(screen, Confg, event, tabMO, tabMAO, &i);
            break;
        case SDL_MOUSEBUTTONDOWN:
            switch (i)
            {
            case 1:
                if (Confg->Lang > 0)
                    InitImg_fr(tabMO, tabMAO);
                else
                    InitImg_en(tabMO, tabMAO);

                Confg->Lang *= -1;
                AffichageMenuOpt(screen, tabMO, tabMAO, i);
                SDL_Flip(screen);
                break;
            case 2:
                if (Confg->Fullscr > 0)
                    screen = SDL_SetVideoMode(Width, Height, Bpp, SDL_HWSURFACE | SDL_FULLSCREEN);
                else
                    screen = SDL_SetVideoMode(Width, Height, Bpp, SDL_HWSURFACE);
                Confg->Fullscr *= -1;

                AffichageMenuOpt(screen, tabMO, tabMAO, 0);
                SDL_Flip(screen);
                break;
            case 3:
                isRunning = 0;
                break;
            case 4:
                while (event.type != SDL_MOUSEBUTTONUP)
                {
                    if (event.motion.x > 725 && event.motion.x < 1180)
                    {
                        tabMO[2].pos.x = event.motion.x;

                        AffichageMenuOpt(screen, tabMO, tabMAO, 0);
                        SDL_Flip(screen);
                    }
                    int x = tabMO[2].pos.x;
                    if (x < 730)
                    {
                        // Mix_VolumeChunk(sound, 0);
                        Mix_VolumeMusic(0);
                    }
                    else if (x < 770)
                    {
                        // Mix_VolumeChunk(sound, 1 * MIX_MAX_VOLUME / 11);
                        Mix_VolumeMusic(1 * MIX_MAX_VOLUME / 11);
                    }
                    else if (x < 815)
                    {
                        // Mix_VolumeChunk(sound, 2 * MIX_MAX_VOLUME / 11);
                        Mix_VolumeMusic(2 * MIX_MAX_VOLUME / 11);
                    }
                    else if (x < 860)
                    {
                        // Mix_VolumeChunk(sound, 3 * MIX_MAX_VOLUME / 11);
                        Mix_VolumeMusic(3 * MIX_MAX_VOLUME / 11);
                    }
                    else if (x < 905)
                    {
                        // Mix_VolumeChunk(sound, 4 * MIX_MAX_VOLUME / 11);
                        Mix_VolumeMusic(4 * MIX_MAX_VOLUME / 11);
                    }
                    else if (x < 950)
                    {
                        // Mix_VolumeChunk(sound, 5 * MIX_MAX_VOLUME / 11);
                        Mix_VolumeMusic(5 * MIX_MAX_VOLUME / 11);
                    }
                    else if (x < 995)
                    {
                        // Mix_VolumeChunk(sound, 6 * MIX_MAX_VOLUME / 11);
                        Mix_VolumeMusic(6 * MIX_MAX_VOLUME / 11);
                    }
                    else if (x < 1040)
                    {
                        // Mix_VolumeChunk(sound, 7 * MIX_MAX_VOLUME / 11);
                        Mix_VolumeMusic(7 * MIX_MAX_VOLUME / 11);
                    }
                    else if (x < 1085)
                    {
                        // Mix_VolumeChunk(sound, 8 * MIX_MAX_VOLUME / 11);
                        Mix_VolumeMusic(8 * MIX_MAX_VOLUME / 11);
                    }
                    else if (x < 1130)
                    {
                        // Mix_VolumeChunk(sound, 9 * MIX_MAX_VOLUME / 11);
                        Mix_VolumeMusic(9 * MIX_MAX_VOLUME / 11);
                    }
                    else if (x < 1175)
                    {
                        // Mix_VolumeChunk(sound, 10 * MIX_MAX_VOLUME / 11);
                        Mix_VolumeMusic(10 * MIX_MAX_VOLUME / 11);
                    }
                    else if (x < 1180)
                    {
                        // Mix_VolumeChunk(sound, MIX_MAX_VOLUME);
                        Mix_VolumeMusic(MIX_MAX_VOLUME);
                    }
                    SDL_PollEvent(&event);
                }
                break;
            }
        }
    }

    for (int i = 0; i < 6; i++)
        Liberer_Img(tabMO[i]);
    for (int i = 0; i < 3; i++)
        Liberer_Img(tabMAO[i]);
}
