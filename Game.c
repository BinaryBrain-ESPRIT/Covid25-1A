#include "Game.h"
#include "Main_Fn.h"
#include "minimap.h"
#include "enigme_image.h"
#include "enigme.h"
#include "time.h"

void AffichageMainMenu(SDL_Surface *screen, Text tabT[], Text tabAT[], Image tabI[][3], int j, int l, int p)
{
    AfficherImg(tabI[l - 1][p - 1], screen);
    if (j != 0)
    {
        for (int i = 0; i < 6; i++)
            if (i != j - 1)
                Afficher_txt(tabT[i], screen);

        Afficher_txt(tabAT[j - 1], screen);
    }
    else
    {
        for (int i = 0; i < 6; i++)
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

void ChoosePlayerName(Player *p, Config *Confg, SDL_Surface *screen)
{
    int isRunning = 1, x, y, i = 0;
    char c;

    SDL_Event event;
    SDL_Color PlayerNameColor = {0, 142, 118};

    Text PlayerName;
    Image Backg;
    Image But[2];

    SDL_EnableUNICODE(SDL_ENABLE);

    strcpy(PlayerName.Texte, "");
    InitBackg(&Backg, "assets/PlayerName/Backg.jpg");
    initImg(&But[0], 906, 595, "assets/PlayerName/ok.png");
    initImg(&But[1], 906, 595, "assets/PlayerName/okS.png");
    AfficherImg(Backg, screen);
    AfficherImg(But[0], screen);
    SDL_Flip(screen);

    while (isRunning)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            Confg->isRunning = 0;
            isRunning = 0;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_BACKSPACE && strlen(PlayerName.Texte) > 0)
                PlayerName.Texte[strlen(PlayerName.Texte) - 1] = '\0';
            else if (strlen(PlayerName.Texte) < 19)
            {
                c = (char)event.key.keysym.unicode;
                c = toupper(c);
                if (c > 64 && c < 91)
                    strncat(PlayerName.Texte, &c, 1);
                initTxt(&PlayerName, 775, 470, PlayerNameColor, 35, "assets/Font/AznKnucklesTrial-z85pa.otf", PlayerName.Texte);
                AfficherImg(Backg, screen);
                AfficherImg(But[0], screen);
                Afficher_txt(PlayerName, screen);
                SDL_Flip(screen);
            }

            if (event.key.keysym.sym == SDLK_RETURN)
            {
                if (strlen(PlayerName.Texte) > 1)
                {
                    strcpy(p->PlayerName, PlayerName.Texte);
                    isRunning = 0;
                }
            }
            break;
        case SDL_MOUSEMOTION:
            x = event.button.x;
            y = event.button.y;
            int posX = But[0].pos.x;
            int posY = But[0].pos.y;
            int posX1 = posX + But[0].img->w;
            int posY1 = posY + But[0].img->h;

            if (x > posX && x < posX1 && y > posY && y < posY1)
            {
                AfficherImg(Backg, screen);
                AfficherImg(But[1], screen);
                Afficher_txt(PlayerName, screen);
                SDL_Flip(screen);
                i = 1;
            }
            else if (i != 0)
            {
                AfficherImg(Backg, screen);
                AfficherImg(But[0], screen);
                Afficher_txt(PlayerName, screen);
                SDL_Flip(screen);
                i = 0;
            }

            break;
        case SDL_MOUSEBUTTONDOWN:
            x = event.button.x;
            y = event.button.y;
            posX = But[0].pos.x;
            posY = But[0].pos.y;
            posX1 = posX + But[0].img->w;
            posY1 = posX + But[0].img->h;

            if (x > posX && x < posX1 && y > posY && y < posY1)
            {
                if (strlen(PlayerName.Texte) > 1)
                {
                    strcpy(p->PlayerName, PlayerName.Texte);
                    isRunning = 0;
                }
            }
            break;
        }
    }

    Liberer_Img(Backg);
    Liberer_txt(PlayerName);
    SDL_EnableUNICODE(SDL_DISABLE);
}

void SelectLevel(SDL_Surface *screen, Config *Confg)
{
    SDL_Event event;
    Image LevelBut[20];
    Image Backg;
    int isRunning = 1;
    int x, y;
    int j = -2;
    int LevelSelected = 0;
    int Mode = 0;
    // Init

    InitBackg(&Backg, "assets/SelectLevel/Background.png");
    initImg(&LevelBut[0], 574, 764, "assets/SelectLevel/level1.png");
    initImg(&LevelBut[1], 841, 764, "assets/SelectLevel/level2.png");
    initImg(&LevelBut[2], 1112, 764, "assets/SelectLevel/level3.png");
    initImg(&LevelBut[3], 829, 879, "assets/SelectLevel/Cancel.png");
    initImg(&LevelBut[4], 574, 764, "assets/SelectLevel/Solo.png");
    initImg(&LevelBut[5], 697, 764, "assets/SelectLevel/Multi.png");
    initImg(&LevelBut[6], 841, 764, "assets/SelectLevel/Solo.png");
    initImg(&LevelBut[7], 964, 764, "assets/SelectLevel/Multi.png");
    initImg(&LevelBut[8], 1112, 764, "assets/SelectLevel/Solo.png");
    initImg(&LevelBut[9], 1235, 764, "assets/SelectLevel/Multi.png");
    initImg(&LevelBut[10], 574, 764, "assets/SelectLevel/level1S.png");
    initImg(&LevelBut[11], 841, 764, "assets/SelectLevel/level2S.png");
    initImg(&LevelBut[12], 1112, 764, "assets/SelectLevel/level3S.png");
    initImg(&LevelBut[13], 829, 879, "assets/SelectLevel/CancelS.png");
    initImg(&LevelBut[14], 574, 764, "assets/SelectLevel/SoloS.png");
    initImg(&LevelBut[15], 697, 764, "assets/SelectLevel/MultiS.png");
    initImg(&LevelBut[16], 841, 764, "assets/SelectLevel/SoloS.png");
    initImg(&LevelBut[17], 964, 764, "assets/SelectLevel/MultiS.png");
    initImg(&LevelBut[18], 1112, 764, "assets/SelectLevel/SoloS.png");
    initImg(&LevelBut[19], 1235, 764, "assets/SelectLevel/MultiS.png");

    // Affichage
    AfficherImg(Backg, screen);
    for (int i = 0; i < 4; i++)
        AfficherImg(LevelBut[i], screen);

    while (isRunning)
    {
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            Confg->isRunning = 0;
            isRunning = 0;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                isRunning = 0;
        case SDL_MOUSEMOTION:
            j = MotionSL(LevelBut, j, event, LevelSelected);

            switch (LevelSelected)
            {
            case 0:
                if (j != -1)
                {
                    AfficherImg(LevelBut[j], screen);
                }
                else if (j == -1)
                {
                    AfficherImg(Backg, screen);
                    for (int i = 0; i < 4; i++)
                        AfficherImg(LevelBut[i], screen);
                }
                break;

            case 1:
                if (j != -1)
                {
                    AfficherImg(LevelBut[j], screen);
                }
                else if (j == -1)
                {
                    AfficherImg(Backg, screen);
                    for (int i = 1; i < 6; i++)
                        AfficherImg(LevelBut[i], screen);
                }
                break;
            case 2:
                if (j != -1)
                {
                    AfficherImg(LevelBut[j], screen);
                }
                else if (j == -1)
                {
                    AfficherImg(Backg, screen);
                    for (int i = 0; i < 8; i++)
                    {
                        if (i != 1 && (i < 4 || i > 5))
                            AfficherImg(LevelBut[i], screen);
                    }
                }
                break;
            case 3:
                if (j != -1)
                {
                    AfficherImg(LevelBut[j], screen);
                }
                else if (j == -1)
                {
                    AfficherImg(Backg, screen);
                    for (int i = 0; i < 10; i++)
                    {
                        if (i != 2 && (i < 4 || i > 7))
                            AfficherImg(LevelBut[i], screen);
                    }
                }
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            switch (j)
            {
            case 10:
                AfficherImg(Backg, screen);
                for (int i = 1; i < 6; i++)
                    AfficherImg(LevelBut[i], screen);

                LevelSelected = 1;
                break;
            case 11:
                AfficherImg(Backg, screen);
                for (int i = 0; i < 8; i++)
                {
                    if (i != j - 10 && i != 5 && i != 4)
                        AfficherImg(LevelBut[i], screen);
                }

                LevelSelected = 2;
                break;
            case 12:
                AfficherImg(Backg, screen);
                for (int i = 0; i < 10; i++)
                {
                    if (i != j - 10 && i != 4 && i != 5 && i != 6 && i != 7)
                        AfficherImg(LevelBut[i], screen);
                }

                LevelSelected = 3;
                break;
            case 14:
                Confg->Level = 1;
                Game(screen, Confg);
                isRunning = 0;
                break;
            case 16:
                Confg->Level = 2;
                Game(screen, Confg);
                isRunning = 0;
                break;
            case 18:
                Confg->Level = 3;
                Game(screen, Confg);
                isRunning = 0;
                break;
            case 15:
                Confg->Level = 1;
                MultiPlayerGame(screen, Confg);
                isRunning = 0;
                break;
            case 17:
                Confg->Level = 2;
                MultiPlayerGame(screen, Confg);
                isRunning = 0;
                break;
            case 19:
                Confg->Level = 3;
                MultiPlayerGame(screen, Confg);
                isRunning = 0;
                break;
            }

            break;
        }
        SDL_Flip(screen);
    }

    Liberer_Img(Backg);
    for (int i = 0; i < 20; i++)
        Liberer_Img(LevelBut[i]);
}

void Game(SDL_Surface *screen, Config *Confg)
{
    srand(time(NULL));
    const Uint8 *state = SDL_GetKeyState(NULL);
    char NameAnimImg[50];
    SDL_Event event;
    int Anim = 0;
    SDL_Color MoneyColor = {57, 181, 74};
    SDL_Color TimeColor = {193, 39, 45};
    SDL_Color Black = {0, 0, 0};
    SDL_Color Red = {193, 39, 45};
    // Declara Player
    Player p;
    // Declara Ennemy
    Ennemy e[5];

    minimap map;

    // Init Backround Masque
    background Backg;
    SDL_Surface *Masque[3];
    Masque[0] = IMG_Load("assets/Levels/Masque.jpg");

    Image1 AnimBackg[10];

    Image tabGameUI[5];
    Text MoneyTxt, GameTimeTxt;

    // Enigme
    int EnigmeTimeInit = 0;
    int EnigmeTimeS = 0;
    int DurationEnigme;

    int isRunning = 1;
    int Opened = 0;
    int last_frame_time = 0;
    int GameTimeInit, GameTimeS, GameTimeM, GameTimeSPred;
    int done, Rep;

    // Init Player
    initPerso(&p, 250, 510, Confg->Player);
    ChoosePlayerName(&p, Confg, screen);

    // Init LevelBackg
    InitGameBackg(&Backg, 0, 0, Width, Height, "assets/Levels/Level1.png");

    // Init GameUI
    initImg(&tabGameUI[0], 31, 53, "assets/GameUi/Health3.png");
    initImg(&tabGameUI[1], 1654, 81, "assets/GameUi/MoneyTime.png");

    sprintf(MoneyTxt.Texte, "%d $", p.score);
    initTxt(&MoneyTxt, 1775, 91, MoneyColor, 35, "assets/Font/AznKnucklesTrial-z85pa.otf", MoneyTxt.Texte);
    initTxt(&MoneyTxt, 1775 - (MoneyTxt.surfaceText->w / 3), 91, MoneyColor, 35, "assets/Font/AznKnucklesTrial-z85pa.otf", MoneyTxt.Texte);
    initTxt(&GameTimeTxt, 1745, 154, TimeColor, 35, "assets/Font/AznKnucklesTrial-z85pa.otf", "00:00");
    // Init Ennemi
    initEnnemy(&e[0], 2500, 575, 5, 2);
    initEnnemy(&e[1], 4270, 575, 5, 2);
    initEnnemy(&e[2], 5640, 575, 5, 2);
    initEnnemy(&e[3], 8120, 575, 5, 2);
    initEnnemy(&e[4], 8800, 575, 5, 2);

    // Init MiniMap
    initminimap(&map, "assets/MiniMap/Level1Mini.jpg", p, e);

    SDL_ShowCursor(SDL_DISABLE);

    GameTimeInit = SDL_GetTicks();

    // GameLoop
    while (isRunning)
    {
        // MAJTime(&GameTimeTxt,GameTimeInit);
        GameTimeS = ((SDL_GetTicks() - GameTimeInit) / 1000) % 60;
        GameTimeM = ((SDL_GetTicks() - GameTimeInit) / 1000) / 60;

        if (GameTimeSPred != GameTimeS)
        {
            sprintf(GameTimeTxt.Texte, "%02d:%02d", GameTimeM, GameTimeS);
            initTxt(&GameTimeTxt, 1745, 154, Red, 35, "assets/Font/AznKnucklesTrial-z85pa.otf", GameTimeTxt.Texte);
        }

        GameTimeSPred = GameTimeS;
        // last_frame_time = SDL_GetTicks();
        //  while (!(SDL_GetTicks() > last_frame_time + FRAME_TARGET_TIME));

        if (Confg->isRunning == 0)
            isRunning = 0;

        // Affichage Backg
        AfficherBackg(Backg, screen);
        Anim = animer_background(&Backg, screen, Anim);

        afficherminimap(map, screen);
        // Affichage GameUI
        for (int i = 0; i < 2; i++)
            AfficherImg(tabGameUI[i], screen);

        MAJMinimap(p.posABS, e, &map, Redim);

        // Perso
        animerPerso(&p);
        afficherPerso(p, screen);

        int n = 0;
        if (isTrapped(p, Masque[0]) && p.nbreVie != 0)
            p.nbreVie = 0;

        // PlayerDie
        if (p.nbreVie == 0)
        {
            if (p.AnimP_Die > 3)
            {
                if (!p.flipped)
                    p.animI = 6;
                else
                    p.animI = 7;
                if (p.NumPlayer != 3)
                    n = 8;
                else
                    n = 5;
                if (p.animJ >= n)
                {
                    p.score -= 50;
                    sprintf(MoneyTxt.Texte, "%d $", p.score);
                    initTxt(&MoneyTxt, 1775 - (MoneyTxt.surfaceText->w / 3), 91, MoneyColor, 35, "assets/Font/AznKnucklesTrial-z85pa.otf", MoneyTxt.Texte);
                    isRunning = 0;
                    SDL_Delay(2000);
                }
                else
                    p.animJ++;

                p.AnimP_Die = 0;
            }
            p.AnimP_Die++;
        }
        else
        {
            // Scrolling
            if (collisionPH(p, Masque[0]) != p.direction)
            {
                if (p.pos.x >= screen->w / 2 && p.direction == 1)
                {
                    scrolling(&Backg, p.direction, 10);
                    p.posABS.x += 10;
                    for (int i = 0; i < 5; i++)
                    {
                        e[i].posInit -= 10;
                        e[i].pos.x -= 10;
                    }
                }
                else if (p.direction == -1 && p.pos.x <= 500 && p.posABS.x > 500)
                {
                    scrolling(&Backg, p.direction, 10);
                    p.posABS.x -= 10;
                    for (int i = 0; i < 5; i++)
                    {
                        e[i].posInit += 10;
                        e[i].pos.x += 10;
                    }
                }
                else if (p.direction == -2)
                {
                    scrolling(&Backg, p.direction, 10);
                    p.posABS.y += 10;
                    for (int i = 0; i < 5; i++)
                    {
                        e[i].pos.y -= 10;
                    }
                }
                else if (p.direction == 2)
                {
                    scrolling(&Backg, p.direction, 10);
                    p.posABS.y -= 10;
                    for (int i = 0; i < 5; i++)
                    {
                        e[i].pos.y += 10;
                    }
                }
                else
                    deplacerPerso(&p, Confg->deltaTime);
            }
        }

        // Ennemy
        for (int i = 0; i < 5; i++)
        {
            if (BehindEnnemy(p, e[i]) != 2)
            {
                if (event.type == SDL_KEYDOWN)
                {
                    if (event.key.keysym.sym == SDLK_a)
                    {

                        e[i].nbreVie--;
                    }
                }
            }
            if (e[i].nbreVie == 0 && !e[i].isKilled)
            {
                p.score += 150;
                sprintf(MoneyTxt.Texte, "%d $", p.score);
                initTxt(&MoneyTxt, 1775 - (MoneyTxt.surfaceText->w / 3), 91, MoneyColor, 35, "assets/Font/AznKnucklesTrial-z85pa.otf", MoneyTxt.Texte);
                e[i].isKilled = 1;
            }

            if (collisionBB(e[i], p) && p.nbreVie > 0 && BehindEnnemy(p, e[i]) != 2)
            {
                e[i].direction = 0;
                e[i].attack = 1;
                if (e[i].anim_j == 2 && e[i].AnimE_Attack % 10 == 0)
                    p.nbreVie--;
                animerEnnemy(&e[i], Confg);
                afficherEnnemy(e[i], screen);
                sprintf(tabGameUI[0].NameImg, "assets/GameUi/Health%d.png", p.nbreVie);
                initImg(&tabGameUI[0], 31, 53, tabGameUI[0].NameImg);
            }
            else
            {
                e[i].attack = 0;
                animerEnnemy(&e[i], Confg);
                deplacerIA(&e[i], p);
                deplacerEnnemy(&e[i], Confg);
                afficherEnnemy(e[i], screen);
            }
        }

        // Affichage MiniMap

        Afficher_txt(MoneyTxt, screen);
        Afficher_txt(GameTimeTxt, screen);
        SDL_Flip(screen);

        // PlayerMovement
        if (state[SDLK_UP])
        {
            if (Interaction(p, Masque[0]) > 2)
                p.direction = 2;
            else
                p.direction = 0;
        }
        if (state[SDLK_DOWN])
        {
            if (Interaction(p, Masque[0]) && !isGround(p, Masque[0]))
                p.direction = -2;
            else
                p.direction = 0;
        }
        if (state[SDLK_RIGHT])
        {
            p.direction = 1;
        }
        if (state[SDLK_LEFT])
        {
            p.direction = -1;
        }
        if (state[SDLK_SPACE])
        {
            if (isGround(p, Masque[0]) && !Interaction(p, Masque[0]))
            {
                p.posInit = p.pos.y;
                p.isJumped = 1;
            }
        }
        saut(&p, Masque[0]);

        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            Confg->isRunning = 0;
            isRunning = 0;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_t:
                // EnigmeTexte
                AfficherEnigmeTexte(screen, Confg, GameTimeInit, Masque[0]);
                SDL_WaitEvent(&event);

                break;
            case SDLK_TAB:
                if (!Opened)
                {
                    Opened = 1;
                    int etat = MenuInGame(screen, Confg, &Opened, &isRunning);
                    if (etat == 1)
                    {
                        AfficherBackg(Backg, screen);
                        afficherPerso(p, screen);
                        for (int i = 0; i < 5; i++)
                            afficherEnnemy(e[i], screen);
                        afficherminimap(map, screen);
                        MenuInGame(screen, Confg, &Opened, &isRunning);
                    }
                    else if (etat == -1)
                    {
                        for (int i = 0; i < 5; i++)
                            LibererEnnemy(e[i]);

                        LibererPlayer(p);

                        LibererBackg(Backg);

                        for (int i = 0; i < 2; i++)
                            Liberer_Img(tabGameUI[i]);
                        Game(screen, Confg);
                        isRunning = 0;
                    }
                    Opened = 0;
                    SDL_WaitEvent(&event);
                }

                break;
            case SDLK_ESCAPE:
                isRunning = 0;
                break;
            case SDLK_e:
                // EnigmeImage
                AfficherEnigmeImage(screen, Confg, GameTimeInit, Masque[0], p);
                SDL_WaitEvent(&event);
                break;

            case SDLK_f:
                if (Confg->Fullscr > 0)
                    screen = SDL_SetVideoMode(Width, Height, Bpp, SDL_HWSURFACE | SDL_FULLSCREEN);
                else
                    screen = SDL_SetVideoMode(Width, Height, Bpp, SDL_HWSURFACE);
                Confg->Fullscr *= -1;
                AfficherBackg(Backg, screen);
                Anim = animer_background(&Backg, screen, Anim);

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

    // Initialise SelectedEnigme
    FILE *f1 = fopen("SelectedEnigme.txt", "w");
    fclose(f1);

    // SaveScore
    SaveScore(p.PlayerName, p.score, GameTimeTxt.Texte);
    Confg->Money += p.score;
    SDL_ShowCursor(SDL_ENABLE);

    // FreeSurfaces
    for (int i = 0; i < 5; i++)
        LibererEnnemy(e[i]);

    LibererPlayer(p);

    LibererBackg(Backg);

    Liberer(&map);

    for (int i = 0; i < 3; i++)
        SDL_FreeSurface(Masque[i]);

    for (int i = 0; i < 2; i++)
        Liberer_Img(tabGameUI[i]);

    for (int i = 0; i < 10; i++)
        SDL_FreeSurface(AnimBackg[i].img);

    Liberer_txt(MoneyTxt);
    Liberer_txt(GameTimeTxt);
}

void MultiPlayerGame(SDL_Surface *screen, Config *Confg)
{
    srand(time(NULL));
    const Uint8 *state = SDL_GetKeyState(NULL);

    SDL_Event event;

    SDL_Color MoneyColor = {57, 181, 74};
    SDL_Color TimeColor = {193, 39, 45};
    SDL_Color Black = {0, 0, 0};
    SDL_Color Red = {193, 39, 45};

    Player p;
    Player p1;
    Ennemy e[5];
    Ennemy e1[5];

    minimap map;

    background Backg;
    background Backg1;

    SDL_Surface *Masque[3];
    Masque[0] = IMG_Load("assets/Levels/Masque.jpg");
    Image tabGameUI[5];
    Text MoneyTxt, GameTimeTxt;

    // Enigme
    int EnigmeTimeInit = 0;
    int EnigmeTimeS = 0;
    int DurationEnigme;

    int isRunning = 1;
    int Opened = 0;
    int last_frame_time = 0;
    int GameTimeInit, GameTimeS, GameTimeM, GameTimeSPred;
    int done, Rep;

    // Init Player
    initPerso(&p, 250, 510, Confg->Player);
    initPerso(&p1, Width / 2 + 250, 510, Confg->Player);
    ChoosePlayerName(&p, Confg, screen);
    ChoosePlayerName(&p1, Confg, screen);

    // Init LevelBackg
    InitGameBackg(&Backg, 0, 0, Width / 2, Height, "assets/Levels/Level1.png");
    InitGameBackg(&Backg1, Width / 2, 0, Width / 2, Height, "assets/Levels/Level1.png");

    // Init GameUI
    initImg(&tabGameUI[0], 31, 53, "assets/GameUi/Health3.png");
    initImg(&tabGameUI[1], 1654, 81, "assets/GameUi/MoneyTime.png");

    sprintf(MoneyTxt.Texte, "%d $", p.score);
    initTxt(&MoneyTxt, 1775, 91, MoneyColor, 35, "assets/Font/AznKnucklesTrial-z85pa.otf", MoneyTxt.Texte);
    initTxt(&MoneyTxt, 1775 - (MoneyTxt.surfaceText->w / 3), 91, MoneyColor, 35, "assets/Font/AznKnucklesTrial-z85pa.otf", MoneyTxt.Texte);
    initTxt(&GameTimeTxt, 1745, 154, TimeColor, 35, "assets/Font/AznKnucklesTrial-z85pa.otf", "00:00");
    // Init Ennemi
    initEnnemy(&e[0], 2500, 575, 5, 2);
    initEnnemy(&e[1], 4270, 575, 5, 2);
    initEnnemy(&e[2], 5640, 575, 5, 2);
    initEnnemy(&e[3], 8120, 575, 5, 2);
    initEnnemy(&e[4], 8800, 575, 5, 2);

    initEnnemy(&e1[0], 2500, 575, 5, 2);
    initEnnemy(&e1[1], 4270, 575, 5, 2);
    initEnnemy(&e1[2], 5640, 575, 5, 2);
    initEnnemy(&e1[3], 8120, 575, 5, 2);
    initEnnemy(&e1[4], 8800, 575, 5, 2);

    // Init MiniMap
    initminimap(&map, "assets/MiniMap/Level1Mini.jpg", p, e);

    SDL_ShowCursor(SDL_DISABLE);

    GameTimeInit = SDL_GetTicks();
    while (isRunning)
    {
        // MAJTime(&GameTimeTxt,GameTimeInit);
        GameTimeS = ((SDL_GetTicks() - GameTimeInit) / 1000) % 60;
        GameTimeM = ((SDL_GetTicks() - GameTimeInit) / 1000) / 60;

        if (GameTimeSPred != GameTimeS)
        {
            sprintf(GameTimeTxt.Texte, "%02d:%02d", GameTimeM, GameTimeS);
            initTxt(&GameTimeTxt, 1745, 154, Red, 35, "assets/Font/AznKnucklesTrial-z85pa.otf", GameTimeTxt.Texte);
        }

        GameTimeSPred = GameTimeS;
        // last_frame_time = SDL_GetTicks();
        //  while (!(SDL_GetTicks() > last_frame_time + FRAME_TARGET_TIME));

        if (Confg->isRunning == 0)
            isRunning = 0;

        // Affichage Backg
        AfficherBackg(Backg, screen);
        AfficherBackg(Backg1, screen);
        afficherminimap(map, screen);
        // Affichage GameUI
        for (int i = 0; i < 2; i++)
            AfficherImg(tabGameUI[i], screen);

        MAJMinimap(p.posABS, e, &map, Redim);

        // Perso
        animerPerso(&p);
        animerPerso(&p1);
        afficherPerso(p, screen);
        afficherPerso(p1, screen);

        int n = 0;
        if (isTrapped(p, Masque[0]) && p.nbreVie != 0)
            p.nbreVie = 0;
        if (isTrapped(p1, Masque[0]) && p1.nbreVie != 0)
            p1.nbreVie = 0;

        // PlayerDie
        if (p.nbreVie == 0)
        {
            if (p.AnimP_Die > 3)
            {
                if (!p.flipped)
                    p.animI = 6;
                else
                    p.animI = 7;
                if (p.NumPlayer != 3)
                    n = 8;
                else
                    n = 5;
                if (p.animJ >= n)
                {
                    p.score -= 50;
                    sprintf(MoneyTxt.Texte, "%d $", p.score);
                    initTxt(&MoneyTxt, 1775 - (MoneyTxt.surfaceText->w / 3), 91, MoneyColor, 35, "assets/Font/AznKnucklesTrial-z85pa.otf", MoneyTxt.Texte);
                    isRunning = 0;
                    SDL_Delay(2000);
                }
                else
                    p.animJ++;

                p.AnimP_Die = 0;
            }
            p.AnimP_Die++;
        }
        else
        {
            if (collisionPH(p, Masque[0]) != p.direction)
            {
                if (p.pos.x >= (Width / 2) / 2 && p.direction == 1 && p.posABS.x < 9390 && !(p.posABS.y > 530 && p.posABS.y < 1310))
                {
                    scrolling(&Backg, p.direction, 10);
                    p.posABS.x += 10;
                    for (int i = 0; i < 5; i++)
                    {
                        e[i].posInit -= 10;
                        e[i].pos.x -= 10;
                    }
                }
                else if (p.direction == -1 && p.pos.x <= 500 && p.posABS.x > 500)
                {
                    scrolling(&Backg, p.direction, 10);
                    p.posABS.x -= 10;
                    for (int i = 0; i < 5; i++)
                    {
                        e[i].posInit += 10;
                        e[i].pos.x += 10;
                    }
                }
                else if (p.direction == -2)
                {
                    scrolling(&Backg, p.direction, 10);
                    p.posABS.y += 10;
                    for (int i = 0; i < 5; i++)
                    {
                        e[i].pos.y -= 10;
                    }
                }
                else if (p.direction == 2)
                {
                    scrolling(&Backg, p.direction, 10);
                    p.posABS.y -= 10;
                    for (int i = 0; i < 5; i++)
                    {
                        e[i].pos.y += 10;
                    }
                }
                else
                    deplacerPerso(&p, Confg->deltaTime);
            }
        }
        // Player 2
        if (p1.nbreVie == 0)
        {
            if (p1.AnimP_Die > 3)
            {
                if (!p1.flipped)
                    p1.animI = 6;
                else
                    p1.animI = 7;
                if (p1.NumPlayer != 3)
                    n = 8;
                else
                    n = 4;
                if (p1.animJ >= n)
                {
                    p1.score -= 50;
                    sprintf(MoneyTxt.Texte, "%d $", p1.score);
                    initTxt(&MoneyTxt, 1775 - (MoneyTxt.surfaceText->w / 3), 91, MoneyColor, 35, "assets/Font/AznKnucklesTrial-z85pa.otf", MoneyTxt.Texte);
                    isRunning = 0;
                    SDL_Delay(2000);
                }
                else
                    p1.animJ++;

                p1.AnimP_Die = 0;
            }
            p1.AnimP_Die++;
        }
        else
        {
            if (collisionPH(p1, Masque[0]) != p1.direction)
            {
                if (p1.pos.x >= (Width / 2) + (Width / 4) && p1.direction == 1 && p1.posABS.x < 9390 && !(p1.posABS.y > 530 && p1.posABS.y < 1310))
                {
                    scrolling(&Backg1, p1.direction, 10);
                    p1.posABS.x += 10;
                    for (int i = 0; i < 5; i++)
                    {
                        e1[i].posInit -= 10;
                        e1[i].pos.x -= 10;
                    }
                }
                else if (p1.direction == -1 && p1.pos.x <= Width / 2 + 500 && p1.posABS.x > 500)
                {
                    scrolling(&Backg1, p1.direction, 10);
                    p1.posABS.x -= 10;
                    for (int i = 0; i < 5; i++)
                    {
                        e1[i].posInit += 10;
                        e1[i].pos.x += 10;
                    }
                }
                else if (p1.direction == -2)
                {
                    scrolling(&Backg, p1.direction, 10);
                    p1.posABS.y += 10;
                    for (int i = 0; i < 5; i++)
                    {
                        e1[i].pos.y -= 10;
                    }
                }
                else if (p1.direction == 2)
                {
                    scrolling(&Backg, p.direction, 10);
                    p1.posABS.y -= 10;
                    for (int i = 0; i < 5; i++)
                    {
                        e1[i].pos.y += 10;
                    }
                }
                else
                {
                    if (p1.direction == -1 && p1.pos.x < (Width / 2))
                    {
                        p1.direction = 0;
                    }
                    else
                        deplacerPerso(&p1, Confg->deltaTime);
                }
            }
        }

        // Ennemy
        for (int i = 0; i < 5; i++)
        {
            if (BehindEnnemy(p, e[i]) != 2)
            {
                if (event.type == SDL_KEYDOWN)
                {
                    if (event.key.keysym.sym == SDLK_a)
                    {
                        e[i].nbreVie--;
                    }
                }
            }
            // Ennemy2
            if (BehindEnnemy(p1, e1[i]) != 2)
            {
                if (event.type == SDL_KEYDOWN)
                {
                    if (event.key.keysym.sym == SDLK_a)
                    {
                        e1[i].nbreVie--;
                    }
                }
            }
            if (e[i].nbreVie == 0 && !e[i].isKilled)
            {
                p.score += 150;
                sprintf(MoneyTxt.Texte, "%d $", p.score);
                initTxt(&MoneyTxt, 1775 - (MoneyTxt.surfaceText->w / 3), 91, MoneyColor, 35, "assets/Font/AznKnucklesTrial-z85pa.otf", MoneyTxt.Texte);
                e[i].isKilled = 1;
            }
            // Ennemy2
            if (e1[i].nbreVie == 0 && !e1[i].isKilled)
            {
                p1.score += 150;
                sprintf(MoneyTxt.Texte, "%d $", p1.score);
                initTxt(&MoneyTxt, 1775 - (MoneyTxt.surfaceText->w / 3), 91, MoneyColor, 35, "assets/Font/AznKnucklesTrial-z85pa.otf", MoneyTxt.Texte);
                e1[i].isKilled = 1;
            }

            if (collisionBB(e[i], p) && p.nbreVie > 0 && BehindEnnemy(p, e[i]) != 2)
            {
                e[i].direction = 0;
                e[i].attack = 1;
                if (e[i].anim_j == 2 && e[i].AnimE_Attack % 10 == 0)
                    p.nbreVie--;
                animerEnnemy(&e[i], Confg);
                if (e[i].pos.x < (1000 - e[i].img[e->anim_i][e->anim_j]->w))
                    afficherEnnemy(e[i], screen);
                sprintf(tabGameUI[0].NameImg, "assets/GameUi/Health%d.png", p.nbreVie);
                initImg(&tabGameUI[0], 31, 53, tabGameUI[0].NameImg);
            }
            else
            {
                e[i].attack = 0;
                animerEnnemy(&e[i], Confg);
                deplacerIA(&e[i], p);
                deplacerEnnemy(&e[i], Confg);
                if (e[i].pos.x < (1000 - e[i].img[e->anim_i][e->anim_j]->w))
                    afficherEnnemy(e[i], screen);
            }
            // Ennemy2

            if (collisionBB(e1[i], p1) && p1.nbreVie > 0 && BehindEnnemy(p1, e1[i]) != 2)
            {
                e1[i].direction = 0;
                e1[i].attack = 1;
                if (e1[i].anim_j == 2 && e1[i].AnimE_Attack % 10 == 0)
                    p1.nbreVie--;
                animerEnnemy(&e[i], Confg);
                if (e1[i].pos.x > Width / 2)
                    afficherEnnemy(e1[i], screen);
                sprintf(tabGameUI[0].NameImg, "assets/GameUi/Health%d.png", p1.nbreVie);
                initImg(&tabGameUI[0], 31, 53, tabGameUI[0].NameImg);
            }
            else
            {
                e1[i].attack = 0;
                animerEnnemy(&e1[i], Confg);
                deplacerIA(&e1[i], p);
                deplacerEnnemy(&e1[i], Confg);
                if (e1[i].pos.x > Width / 2)
                    afficherEnnemy(e1[i], screen);
            }
        }

        // Affichage MiniMap

        Afficher_txt(MoneyTxt, screen);
        Afficher_txt(GameTimeTxt, screen);
        SDL_Flip(screen);

        // PlayerMovement
        if (state[SDLK_UP])
        {
            if (Interaction(p, Masque[0]) > 2)
                p.direction = 2;
            else
                p.direction = 0;
        }
        if (state[SDLK_z])
        {
            if (Interaction(p1, Masque[0]) > 2)
                p1.direction = 2;
            else
                p1.direction = 0;
        }
        if (state[SDLK_DOWN])
        {
            if (Interaction(p, Masque[0]) && !isGround(p, Masque[0]))
                p.direction = -2;
            else
                p.direction = 0;
        }
        if (state[SDLK_s])
        {
            if (Interaction(p1, Masque[0]) && !isGround(p1, Masque[0]))
                p1.direction = -2;
            else
                p1.direction = 0;
        }
        if (state[SDLK_RIGHT])
        {
            p.direction = 1;
        }
        if (state[SDLK_d])
        {
            p1.direction = 1;
        }
        if (state[SDLK_LEFT])
        {
            p.direction = -1;
        }
        if (state[SDLK_q])
        {
            p1.direction = -1;
        }
        if (state[SDLK_SPACE])
        {
            if (isGround(p, Masque[0]) && !Interaction(p, Masque[0]))
            {
                p.posInit = p.pos.y;
                p.isJumped = 1;
            }
        }
        if (state[SDLK_LSHIFT])
        {
            if (isGround(p1, Masque[0]) && !Interaction(p1, Masque[0]))
            {
                p1.posInit = p1.pos.y;
                p1.isJumped = 1;
            }
        }

        saut(&p, Masque[0]);
        saut(&p1, Masque[0]);
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            Confg->isRunning = 0;
            isRunning = 0;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
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
                // EnigmeImage
                AfficherEnigmeImage(screen, Confg, GameTimeInit, Masque[0], p);
                break;
            case SDLK_t:
                // EnigmeTexte
                // AfficherEnigmeTexte(screen, Confg, GameTimeInit, Masque[0]);
                printf("Test\n");
                break;
            case SDLK_f:
                if (Confg->Fullscr > 0)
                    screen = SDL_SetVideoMode(Width, Height, Bpp, SDL_HWSURFACE | SDL_FULLSCREEN);
                else
                    screen = SDL_SetVideoMode(Width, Height, Bpp, SDL_HWSURFACE);
                Confg->Fullscr *= -1;
                AfficherBackg(Backg, screen);
                AfficherBackg(Backg1, screen);
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

            if (p1.direction == 1)
                p1.flipped = 0;
            else if (p1.direction == -1)
                p1.flipped = 1;

            p1.direction = 0;

            break;
        }
        Confg->deltaTime = (SDL_GetTicks() - last_frame_time);
    }

    // Initialise SelectedEnigme
    FILE *f1 = fopen("SelectedEnigme.txt", "w");
    fclose(f1);

    // SaveScore
    SaveScore(p.PlayerName, p.score, GameTimeTxt.Texte);
    Confg->Money += p.score;
    SDL_ShowCursor(SDL_ENABLE);

    // FreeSurfaces
    for (int i = 0; i < 5; i++)
        LibererEnnemy(e[i]);
    for (int i = 0; i < 5; i++)
        LibererEnnemy(e1[i]);

    LibererPlayer(p);
    LibererPlayer(p1);

    LibererBackg(Backg);
    LibererBackg(Backg1);

    for (int i = 0; i < 2; i++)
        Liberer_Img(tabGameUI[i]);
}

int MenuInGame(SDL_Surface *screen, Config *Confg, int *Opened, int *isRunning)
{
    Image tabMG[11];

    // Init Image menu In Game

    InitBackg(&tabMG[0], "assets/MenuInGame/Board.png");
    initImg(&tabMG[1], 819, 322, "assets/MenuInGame/Resume.png");
    initImg(&tabMG[2], 819, 437, "assets/MenuInGame/Replay.png");
    initImg(&tabMG[3], 819, 553, "assets/MenuInGame/Option.png");
    initImg(&tabMG[4], 819, 669, "assets/MenuInGame/Exit.png");
    initImg(&tabMG[5], 795, 801, "assets/MenuInGame/Cancel.png");
    initImg(&tabMG[6], 819, 322, "assets/MenuInGame/ResumeS.png");
    initImg(&tabMG[7], 819, 437, "assets/MenuInGame/ReplayS.png");
    initImg(&tabMG[8], 819, 553, "assets/MenuInGame/OptionS.png");
    initImg(&tabMG[9], 819, 669, "assets/MenuInGame/ExitS.png");
    initImg(&tabMG[10], 795, 801, "assets/MenuInGame/CancelS.png");

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
            case 1:
                return 0;
            case 2:
                return -1;
            case 3:
                MenuOpt(screen, Confg);
                return 1;
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
    return 0;
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
    initImg(&tabMO[2], Confg->posVol, 356.5, "assets/MenuOpt/volumebut.png");

    if (Confg->Lang > 0)
        InitImg_en(tabMO, tabMAO);
    else
        InitImg_fr(tabMO, tabMAO);

    // Config Volume

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
                    if (x < 750)
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
    Confg->posVol = tabMO[2].pos.x;
    for (int i = 0; i < 6; i++)
        Liberer_Img(tabMO[i]);
    for (int i = 0; i < 3; i++)
        Liberer_Img(tabMAO[i]);
}

void AffichageCredits(SDL_Surface *screen, Config *Confg)
{
    Image tab[181];
    int isRunning = 1;
    SDL_Event event;
    for (int i = 0; i < 181; i++)
    {
        if (i > 0)
            Liberer_Img(tab[i - 1]);
        sprintf(tab[i].NameImg, "assets/Credits/%d.jpg", i);
        InitBackg(&tab[i], tab[i].NameImg);
        AfficherImg(tab[i], screen);
        SDL_Flip(screen);
        SDL_Delay(10);
        if (i == 89)
            SDL_Delay(5000);
        if (i == 179)
            SDL_Delay(5000);
    }

    while (isRunning)
    {
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            Confg->isRunning = 0;
            isRunning = 0;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                isRunning = 0;
            break;
        }
    }
    Liberer_Img(tab[180]);
}

void AfficherEnigmeImage(SDL_Surface *screen, Config *Confg, int GameTimeInit, SDL_Surface *Masque, Player p)
{
    int done = 0, GameTimeS, Rep, GameTimeM;
    SDL_Event event;
    Enigme e;
    if (EnigmeDetected(p, Masque))
    {
        InitEnigme(&e, "enigmeImg.txt");
        afficherEnigme(e, screen);
        SDL_Flip(screen);
        done = 0;

        e.TimeInit = SDL_GetTicks();
        Rep = 0;
        SDL_ShowCursor(SDL_ENABLE);
        while (!done)
        {
            GameTimeS = ((SDL_GetTicks() - GameTimeInit) / 1000) % 60;
            GameTimeM = ((SDL_GetTicks() - GameTimeInit) / 1000) / 60;

            animer(&e, screen);

            SDL_PollEvent(&event);
            switch (event.type)
            {
            case SDL_QUIT:
                done = 1;
                Confg->isRunning = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (e.NumE >= 2 && e.NumE <= 4)
                {
                    if (event.button.x > 18 && event.button.x < 576 && event.button.y > 687 && event.button.y < 1056)
                        Rep = 1;
                    else if (event.button.x > 682 && event.button.x < 1245 && event.button.y > 556 && event.button.y < 924)
                        Rep = 2;
                    else if (event.button.x > 1334 && event.button.x < 1903 && event.button.y > 687 && event.button.y < 1057)
                        Rep = 3;
                }
                else
                {
                    if (event.button.x > 1070 && event.button.x < 1232 && event.button.y > 105 && event.button.y < 270)
                        Rep = 1;
                    else if (event.button.x > 1356 && event.button.x < 1518 && event.button.y > 105 && event.button.y < 270)
                        Rep = 2;
                    else if (event.button.x > 1212 && event.button.x < 1374 && event.button.y > 363 && event.button.y < 527)
                        Rep = 3;
                }
                break;
            }

            if ((Rep > 0 && Rep < 4) || e.TimeOut)
            {
                if (Rep == e.NumRC && !e.TimeOut)
                {
                    AfficherImg(e.Backg[1], screen);
                    SDL_Flip(screen);
                    SDL_Delay(2000);
                }
                else
                {
                    AfficherImg(e.Backg[2], screen);
                    SDL_Flip(screen);
                    SDL_Delay(2000);
                }
                done = 1;
            }
        }
        Free_Enigme(&e);
    }
    SDL_ShowCursor(SDL_DISABLE);
}

void AfficherEnigmeTexte(SDL_Surface *screen, Config *Confg, int GameTimeInit, SDL_Surface *Masque)
{
    enigme e;
    int done = 0, GameTimeS, Rep = 0, GameTimeM;
    SDL_Event event;

    if (InitEnigme1(&e, "enigme.txt"))
    {
        afficherEnigme1(e, screen);
        SDL_Flip(screen);
        done = 0;

        e.TimeInit = SDL_GetTicks();

        SDL_ShowCursor(SDL_ENABLE);
        while (!done)
        {
            GameTimeS = ((SDL_GetTicks() - GameTimeInit) / 1000) % 60;
            GameTimeM = ((SDL_GetTicks() - GameTimeInit) / 1000) / 60;

            animer1(&e, screen);

            SDL_PollEvent(&event);
            switch (event.type)
            {
            case SDL_QUIT:
                done = 1;
                Confg->isRunning = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_1:
                    Rep = 1;
                    break;
                case SDLK_2:
                    Rep = 2;
                    break;
                case SDLK_3:
                    Rep = 3;
                    break;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.x > 261 && event.button.x < 596 && event.button.y > 427 && event.button.y < 565)
                    Rep = 1;
                else if (event.button.x > 1340 && event.button.x < 1700 && event.button.y > 427 && event.button.y < 565)
                    Rep = 2;
                else if (event.button.x > 775 && event.button.x < 1132 && event.button.y > 661 && event.button.y < 820)
                    Rep = 3;
                break;
            }
            if ((Rep > 0 && Rep < 4) || e.TimeOut)
            {
                if (Rep == e.NumRepC && !e.TimeOut)
                {
                    AfficherImg(e.Backg[1], screen);
                    SDL_Flip(screen);
                    SDL_Delay(2000);
                }
                else
                {
                    AfficherImg(e.Backg[2], screen);
                    SDL_Flip(screen);
                    SDL_Delay(2000);
                }
                done = 1;
            }
        }
        SDL_ShowCursor(SDL_DISABLE);
        Free_Enigme1(&e);
    }
    else
        printf("Out Of Choice\n");
}