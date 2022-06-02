/**
 * @file minimap.c
 * @author oussamaawledsalem
 * @brief
 * @version 0.1
 * @date 2022-04-22
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "minimap.h"
#include "Main_Fn.h"
#include <time.h>
#include <stdlib.h>
/**
 * @brief to initialize minilap
 *
 * @param m the map
 * @param nameimg name of the minimap to use
 * @param p player
 * @param e ennemy
 */
void initminimap(minimap *m, char nameimg[], Player p, Ennemy e[], int Lvl)
{
    int redim;
    if (Lvl > 1)
        redim = Redim1;
    else
        redim = Redim;
    m->image = IMG_Load(nameimg);
    m->image1 = IMG_Load("assets/MiniMap/MinimapFrame.png");
    m->pos1.x = 0;
    m->pos1.y = 0;
    
    if (Lvl > 1)
    {
        m->pos.x = 99;
        m->pos.y = 58;
        m->image1 = IMG_Load("assets/MiniMap/Level2/MiniMapFrame.png");
    }
    else
    {
        m->pos.x = 382;
        m->pos.y = 45;
        m->image1 = IMG_Load("assets/MiniMap/MinimapFrame.png");
    }

    m->playerTag = IMG_Load("assets/MiniMap/PlayerTag.png");
    m->playerTagPos.x = ((p.pos.x * redim) / 100) + m->pos.x;
    m->playerTagPos.y = (((p.pos.y + p.img[p.animI][p.animJ]->h) * redim) / 100) + m->pos.y ;
    for (int i = 0; i < 5; i++)
    {
        m->zombieTag[i] = IMG_Load("assets/MiniMap/ZombieTag.png");
        m->zombieTagPos[i].x = ((e[i].pos.x * redim) / 100) + m->pos.x;
        m->zombieTagPos[i].y = ((e[i].pos.y * redim) / 100) + m->pos.y;
    }
}
/**
 * @brief to display the minimap
 *
 * @param m minimap
 * @param screen screen display
 */
void afficherminimap(minimap m, SDL_Surface *screen)
{
    SDL_BlitSurface(m.image1, NULL, screen, &m.pos1);
    SDL_BlitSurface(m.image, NULL, screen, &m.pos);

    SDL_BlitSurface(m.playerTag, NULL, screen, &m.playerTagPos);
    for (int i = 0; i < 5; i++)
    {
        if (!m.EnnemyDie[i])
            SDL_BlitSurface(m.zombieTag[i], NULL, screen, &m.zombieTagPos[i]);
    }
}
/**
 * @brief minimap update
 *
 * @param PosJoueur player position
 * @param e ennemy
 * @param m minimap
 * @param redimensionnement recizing percentage
 */
void MAJMinimap(SDL_Rect PosJoueur, Ennemy e[], minimap *m, int redimensionnement)
{
    m->playerTagPos.x = m->pos.x + ((PosJoueur.x * redimensionnement) / 100);
    m->playerTagPos.y = m->pos.y + ((PosJoueur.y * redimensionnement) / 100);
    for (int i = 0; i < 5; i++)
    {
        if (e[i].isKilled)
            m->EnnemyDie[i] = 1;
        m->zombieTagPos[i].x = m->pos.x + ((e[i].posABS.x * redimensionnement) / 100);
        m->zombieTagPos[i].y = m->pos.y + ((e[i].posABS.y * redimensionnement) / 100);
    }
}
/**
 * @brief time management
 *
 * @param GameTimeTxt to display the time
 * @param GameTimeInit time inisialisation
 */
void MAJTime(Text *GameTimeTxt, int GameTimeInit)
{
    SDL_Color Red = {193, 39, 45};
    int GameTimeS, GameTimeM, GameTimeSPred;

    GameTimeS = ((SDL_GetTicks() - GameTimeInit) / 1000) % 60;
    GameTimeM = ((SDL_GetTicks() - GameTimeInit) / 1000) / 60;

    if (GameTimeSPred != GameTimeS)
    {
        sprintf(GameTimeTxt->Texte, "%02d:%02d", GameTimeM, GameTimeS);
        initTxt(GameTimeTxt, 1745, 154, Red, 35, "assets/Font/AznKnucklesTrial-z85pa.otf", GameTimeTxt->Texte);
    }

    GameTimeSPred = GameTimeS;
}
/**
 * @brief score saving
 *
 * @param PlayerName name of the player
 * @param Score score
 * @param Time time
 */
void SaveScore(char PlayerName[], int Score, char Time[])
{
    FILE *f = fopen("Data/Score.txt", "a");

    fprintf(f, "%s %s %d\n", PlayerName, Time, Score);
    fclose(f);
}
/**
 * @brief best score display
 *
 * @param screen screen display
 * @param Confg
 */
void LeaderBoard(SDL_Surface *screen, Config *Confg)
{
    Image Backg;
    FILE *f = fopen("Data/Score.txt", "r");
    Score tabS[6];
    SDL_Color Blue = {16, 16, 73};
    SDL_Color Gold = {214, 165, 101};
    SDL_Color Red = {193, 39, 45};
    SDL_Rect tabPos[6];
    SDL_Event event;

    int n = 0;
    int Done = 0;

    tabPos[0].x = 754;
    tabPos[0].y = 271;
    tabPos[1].x = 754;
    tabPos[1].y = 394;
    tabPos[2].x = 754;
    tabPos[2].y = 517;
    tabPos[3].x = 754;
    tabPos[3].y = 640;
    tabPos[4].x = 754;
    tabPos[4].y = 763;
    tabPos[5].x = 754;
    tabPos[5].y = 887;
    InitBackg(&Backg, "assets/LeaderBoard/Background.jpg");
    AfficherImg(Backg, screen);

    while (fscanf(f, "%s %s %d", tabS[n].PlayerName.Texte, tabS[n].Time.Texte, &tabS[n].Score) != EOF)
        n++;

    int permut;
    Score temp;
    do
    {
        permut = 0;
        for (int i = 0; i < n - 1; i++)
        {
            if (tabS[i].Score < tabS[i + 1].Score)
            {
                temp = tabS[i];
                tabS[i] = tabS[i + 1];
                tabS[i + 1] = temp;
                permut = 1;
            }
        }
    } while (permut);

    if (n > 6)
        n = 6;
    for (int i = 0; i < n; i++)
    {
        initTxt(&tabS[i].PlayerName, tabPos[i].x, tabPos[i].y, Blue, 29, "assets/Font/Montserrat-Bold.ttf", tabS[i].PlayerName.Texte);
        initTxt(&tabS[i].Time, tabPos[i].x + 277, tabPos[i].y, Gold, 29, "assets/Font/Montserrat-Bold.ttf", tabS[i].Time.Texte);
        sprintf(tabS[i].ScoreTxt.Texte, "%d", tabS[i].Score);
        initTxt(&tabS[i].ScoreTxt, tabPos[i].x + 489, tabPos[i].y, Red, 29, "assets/Font/Montserrat-Bold.ttf", tabS[i].ScoreTxt.Texte);
        Afficher_txt(tabS[i].PlayerName, screen);
        Afficher_txt(tabS[i].Time, screen);
        Afficher_txt(tabS[i].ScoreTxt, screen);
    }
    SDL_Flip(screen);

    while (!Done)
    {
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            Done = 1;
            Confg->isRunning = 0;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                Done = 1;
            break;
        }
    }

    SDL_FreeSurface(Backg.img);
    for (int i = 0; i < n; i++)
    {
        SDL_FreeSurface(tabS[i].PlayerName.surfaceText);
        SDL_FreeSurface(tabS[i].Time.surfaceText);
        SDL_FreeSurface(tabS[i].ScoreTxt.surfaceText);
    }

    fclose(f);
}
/**
 * @brief free memory space
 *
 * @param m minimap
 */
void Liberer(minimap *m)
{
    SDL_FreeSurface(m->image);
    SDL_FreeSurface(m->image1);
}

// **********************************MiniGame*******************************************************//

// CardGame
/**
 * @brief MiniGame
 *
 * @param screen screen display
 * @param Confg Configuration Variable
 * @return int Win Or Loose
 */

int MiniGameCard(SDL_Surface *screen, Config *Confg)
{
    SDL_ShowCursor(SDL_ENABLE);

    SDL_Event event;
    SDL_Color White = {255, 255, 255};

    Image Backg;
    card Card1[6];
    card Card[2][3];
    card TurnedCard[2];
    Text ChanceT, ScoreT;

    int n = 0, Score = 0, Chance = 5;
    int RandNum, isRunning = 1, posX, posX1, posY, posY1;

    Card[0][0].Image.pos.x = 153;
    Card[0][0].Image.pos.y = 29;
    Card[0][0].Turned = 0;
    Card[0][0].Done = 0;
    Card[0][0].CardNumber = 0;

    Card[0][1].Image.pos.x = 809;
    Card[0][1].Image.pos.y = 29;
    Card[0][1].Turned = 0;
    Card[0][1].Done = 0;
    Card[0][1].CardNumber = 1;

    Card[0][2].Image.pos.x = 1465;
    Card[0][2].Image.pos.y = 29;
    Card[0][2].Turned = 0;
    Card[0][2].Done = 0;
    Card[0][2].CardNumber = 2;

    Card[1][0].Image.pos.x = 153;
    Card[1][0].Image.pos.y = 644;
    Card[1][0].Turned = 0;
    Card[1][0].Done = 0;
    Card[1][0].CardNumber = 3;

    Card[1][1].Image.pos.x = 809;
    Card[1][1].Image.pos.y = 644;
    Card[1][1].Turned = 0;
    Card[1][1].Done = 0;
    Card[1][1].CardNumber = 4;

    Card[1][2].Image.pos.x = 1465;
    Card[1][2].Image.pos.y = 644;
    Card[1][2].Turned = 0;
    Card[1][2].Done = 0;
    Card[1][2].CardNumber = 5;

    strcpy(Card1[0].Image.NameImg, "assets/MiniGame/Card/appleCard.png");
    strcpy(Card1[1].Image.NameImg, "assets/MiniGame/Card/appleCard.png");

    strcpy(Card1[2].Image.NameImg, "assets/MiniGame/Card/bananaCard.png");
    strcpy(Card1[3].Image.NameImg, "assets/MiniGame/Card/bananaCard.png");

    strcpy(Card1[4].Image.NameImg, "assets/MiniGame/Card/watermelonCard.png");
    strcpy(Card1[5].Image.NameImg, "assets/MiniGame/Card/watermelonCard.png");

    InitBackg(&Backg, "assets/MiniGame/Card/Background.png");

    sprintf(ScoreT.Texte, "Score: %d", Score);
    initTxt(&ScoreT, 150, 520, White, 50, "assets/Font/AznKnucklesTrial-z85pa.otf", ScoreT.Texte);

    sprintf(ChanceT.Texte, "Chance: %d", Chance);
    initTxt(&ChanceT, 1481, 520, White, 50, "assets/Font/AznKnucklesTrial-z85pa.otf", ChanceT.Texte);
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            do
                RandNum = rand() % 6;
            while (strcmp(Card1[RandNum].Image.NameImg, "") == 0);

            strcpy(Card[i][j].Image.NameImg, Card1[RandNum].Image.NameImg);
            Card[i][j].RImage = Card[i][j].Image;
            initImg(&Card[i][j].Image, Card[i][j].Image.pos.x, Card[i][j].Image.pos.y, Card[i][j].Image.NameImg);
            initImg(&Card[i][j].RImage, Card[i][j].RImage.pos.x, Card[i][j].RImage.pos.y, "assets/MiniGame/Card/cardBack.png");

            strcpy(Card1[RandNum].Image.NameImg, "");
        }
    }

    AfficherImg(Backg, screen);
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            AfficherImg(Card[i][j].RImage, screen);
    Afficher_txt(ScoreT, screen);
    Afficher_txt(ChanceT, screen);

    SDL_Flip(screen);
    while (isRunning)
    {
        if (Chance == 0 || Score == 150)
            isRunning = 0;
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (Card[i][j].Turned && !Card[i][j].Done)
                {
                    TurnedCard[n] = Card[i][j];
                    Card[i][j].Done = 1;
                    n++;
                }
            }
        }
        if (n == 2)
        {
            if (strcmp(TurnedCard[0].Image.NameImg, TurnedCard[1].Image.NameImg) == 0)
            {
                Score += 50;
                sprintf(ScoreT.Texte, "Score: %d", Score);
                initTxt(&ScoreT, 150, 520, White, 50, "assets/Font/AznKnucklesTrial-z85pa.otf", ScoreT.Texte);
                AfficherImg(Backg, screen);
                for (int i = 0; i < 2; i++)
                    for (int j = 0; j < 3; j++)
                        if (!Card[i][j].Turned)
                            AfficherImg(Card[i][j].RImage, screen);
                        else
                            AfficherImg(Card[i][j].Image, screen);

                Afficher_txt(ScoreT, screen);
                Afficher_txt(ChanceT, screen);
                SDL_Flip(screen);

                n = 0;
            }
            else
            {
                n = 0;
                Chance--;

                for (int i = 0; i < 2; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        if (Card[i][j].CardNumber == TurnedCard[0].CardNumber || Card[i][j].CardNumber == TurnedCard[1].CardNumber)
                        {
                            Card[i][j].Turned = 0;
                            Card[i][j].Done = 0;
                            AfficherImg(Card[i][j].RImage, screen);
                            SDL_Flip(screen);
                        }
                    }
                }

                sprintf(ChanceT.Texte, "Chance: %d", Chance);
                initTxt(&ChanceT, 1481, 520, White, 50, "assets/Font/AznKnucklesTrial-z85pa.otf", ChanceT.Texte);
                AfficherImg(Backg, screen);
                for (int i = 0; i < 2; i++)
                    for (int j = 0; j < 3; j++)
                        if (!Card[i][j].Turned)
                            AfficherImg(Card[i][j].RImage, screen);
                        else
                            AfficherImg(Card[i][j].Image, screen);

                Afficher_txt(ScoreT, screen);
                Afficher_txt(ChanceT, screen);
                SDL_Flip(screen);

                SDL_Delay(50);
            }
        }
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            isRunning = 0;
            Confg->isRunning = 0;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                isRunning = 0;
            break;
        case SDL_MOUSEBUTTONDOWN:

            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    posX = Card[i][j].RImage.pos.x;
                    posX1 = posX + Card[i][j].RImage.img->w;
                    posY = Card[i][j].RImage.pos.y;
                    posY1 = posY + Card[i][j].RImage.img->h;

                    int x = event.motion.x;
                    int y = event.motion.y;
                    if (x > posX && x < posX1 && y > posY && y < posY1 && !Card[i][j].Turned)
                    {
                        Card[i][j].Turned = 1;
                        AfficherImg(Card[i][j].Image, screen);
                        SDL_Flip(screen);
                        SDL_Delay(500);
                    }
                }
            }
            break;
        }
        SDL_Flip(screen);
    }
    if (Chance == 0)
        return 0;
    else
        return 1;
    SDL_ShowCursor(SDL_DISABLE);
}

void TicTacToe(SDL_Surface *screen, Config *Confg, char PlayerN[])
{
    SDL_Event event;
    Image Backg;
    Image X[9], O[9], Win, Loose;
    SDL_Rect pos[9];
    Text PlayerName;
    SDL_Color White = {255, 255, 255};
    int i,x,y, isMarked[9] = {0}, Winner = 0;

    SDL_ShowCursor(SDL_ENABLE);

    initTxt(&PlayerName, 387, 667, White, 69, "assets/Font/agency-fb.ttf", PlayerN);

    InitBackg(&Backg, "assets/MiniGame/TicTacToe/Background.jpg");
    InitBackg(&Win, "assets/MiniGame/Win.png");
    InitBackg(&Loose, "assets/MiniGame/Loose.png");

    pos[0].x = 712;
    pos[0].y = 294;

    pos[1].x = 896;
    pos[1].y = 294;

    pos[2].x = 1075;
    pos[2].y = 294;

    pos[3].x = 712;
    pos[3].y = 468;

    pos[4].x = 896;
    pos[4].y = 468;

    pos[5].x = 1075;
    pos[5].y = 468;

    pos[6].x = 712;
    pos[6].y = 659;

    pos[7].x = 896;
    pos[7].y = 659;

    pos[8].x = 1075;
    pos[8].y = 659;

    for (int i = 0; i < 9; i++)
        initImg(&X[i], pos[i].x, pos[i].y, "assets/MiniGame/TicTacToe/x.png");
    for (int i = 0; i < 9; i++)
        initImg(&O[i], pos[i].x, pos[i].y, "assets/MiniGame/TicTacToe/o.png");

    AfficherImg(Backg, screen);
    Afficher_txt(PlayerName, screen);

    SDL_Flip(screen);
    int isRunning = 1;
    while (isRunning)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            isRunning = 0;
            break;
        case SDL_MOUSEBUTTONDOWN:
             x = event.button.x;
             y = event.button.y;
            for (i = 0; i < 9; i++)
                if (x > pos[i].x && x < pos[i].x + 130 && y > pos[i].y && y < pos[i].y + 140)
                    break;
            if (i < 9 && !isMarked[i])
            {

                isMarked[i] = 1;
                AfficherImg(X[i], screen);
                SDL_Flip(screen);
                SDL_Delay(500);
                if (!Winner)
                {
                    for (i = 0; i < 9; i++)
                    {
                        if (isMarked[i] == 2)
                        {
                            if (!isMarked[i + 1] && i != 2 && i != 5 && i != 8)
                            {
                                isMarked[i + 1] = 2;
                                AfficherImg(O[i + 1], screen);
                                SDL_Flip(screen);
                                break;
                            }
                            else if (!isMarked[i - 1] && i != 0 && i != 3 && i != 6)
                            {
                                isMarked[i - 1] = 2;
                                AfficherImg(O[i - 1], screen);
                                SDL_Flip(screen);
                                break;
                            }
                            else if (!isMarked[i + 3] && i >= 0 && i < 6)
                            {
                                isMarked[i + 3] = 2;
                                AfficherImg(O[i + 3], screen);
                                SDL_Flip(screen);
                                break;
                            }
                            else if (!isMarked[i - 3] && i >= 3 && i < 9)
                            {
                                isMarked[i - 3] = 2;
                                AfficherImg(O[i - 3], screen);
                                SDL_Flip(screen);
                                break;
                            }
                            else if (!isMarked[i + 4] && (i == 0 || i == 4))
                            {
                                isMarked[i + 4] = 2;
                                AfficherImg(O[i + 4], screen);
                                SDL_Flip(screen);
                                break;
                            }
                            else if (!isMarked[i - 4] && (i == 8 || i == 4))
                            {
                                isMarked[i - 4] = 2;
                                AfficherImg(O[i - 4], screen);
                                SDL_Flip(screen);
                                break;
                            }
                        }
                    }
                    if (i >= 9)
                    {
                        int Rand = rand() % 9;
                        while (isMarked[Rand])
                            Rand = rand() % 9;
                        isMarked[Rand] = 2;
                        AfficherImg(O[Rand], screen);
                        SDL_Flip(screen);
                    }
                }

                for (int j = 0; j < 9; j += 3)
                    if (isMarked[j] && isMarked[j] == isMarked[j + 1] && isMarked[j] == isMarked[j + 2])
                        Winner = isMarked[j];

                for (int j = 0; j < 3; j++)
                    if (isMarked[j] && isMarked[j] == isMarked[j + 3] && isMarked[j] == isMarked[j + 6])
                        Winner = isMarked[j];

                if (!Winner && isMarked[0] && isMarked[0] == isMarked[4] && isMarked[0] == isMarked[8])
                    Winner = isMarked[0];
                else if (!Winner && isMarked[2] && isMarked[2] == isMarked[4] && isMarked[2] == isMarked[6])
                    Winner = isMarked[2];

                if (Winner)
                {
                    if (Winner == 1)
                        AfficherImg(Win, screen);
                    else
                        AfficherImg(Loose, screen);
                    SDL_Flip(screen);
                    SDL_Delay(1500);
                    isRunning = 0;
                }
            }

            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                isRunning = 0;
            break;
        }
    }
}