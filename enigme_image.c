/**
 * @file enigme_image.c
 * @author Benzarti Wiem (wiem.benzarti@esprit.tn)
 * @brief Image Riddle File
 * @version 0.1
 * @date 2022-04-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "enigme_image.h"

/**
 * @brief initialisation riddle
 *
 * @param e Enigme
 * @param nomfichier file name
 */
void InitEnigme(Enigme *e, char *nomfichier)
{
    SDL_Color White = {255, 255, 255};
    SDL_Color Black = {0, 0, 0};
    SDL_Color Red = {193, 38, 45};

    FILE *f;
    // Random 1->4
    int RandNum = rand() % (5 - 1) + 1;
    f = fopen(nomfichier, "r");

    // Fichier (NumeroEnigme Background NumeroReponseCorrecte)
    do
        fscanf(f, "%d %s %d", &e->NumE, e->Backg[0].NameImg, &e->NumRC);
    while (e->NumE != RandNum);

    strcpy(e->Backg[1].NameImg, "assets/enigmeImage/Win.png");
    strcpy(e->Backg[2].NameImg, "assets/enigmeImage/Loose.png");

    // Init Enigme 2.3.4
    if (e->NumE >= 2 && e->NumE <= 4)
    {
        e->txt.color = White;
        e->txt.font = TTF_OpenFont("assets/Font/Cooper Black Regular.ttf", 135);
        switch (e->NumE)
        {
        case 2:
            strcpy(e->txt.Texte, "\"Dogga\"");
            break;
        case 3:
            strcpy(e->txt.Texte, "\"Kairouan\"");
            break;
        case 4:
            strcpy(e->txt.Texte, "\"El Jam\"");
            break;
        }
        e->txt.surfaceText = TTF_RenderText_Solid(e->txt.font, e->txt.Texte, e->txt.color);

        e->txt.pos.x = Width / 2 - (e->txt.surfaceText->w / 2);
        e->txt.pos.y = 182;
    }

    // InitBackg
    for (int i = 0; i < 3; i++)
        InitBackg(&e->Backg[i], e->Backg[i].NameImg);

    e->TimeOut = 0;
    e->Duration = 10;

    // Init Time
    for (int i = 0; i <= e->Duration; i++)
    {
        sprintf(e->Time[i].Texte, "00:%02d", i);
        if (i < 6)
            initTxt(&e->Time[i], 1707, 26, Red, 70, "assets/Font/AznKnucklesTrial-z85pa.otf", e->Time[i].Texte);
        else
            initTxt(&e->Time[i], 1707, 26, Black, 70, "assets/Font/AznKnucklesTrial-z85pa.otf", e->Time[i].Texte);
    }

    fclose(f);
}

/**
 * @brief Display riddle
 *
 * @param e Enigme
 * @param screen screen display
 */
void afficherEnigme(Enigme e, SDL_Surface *screen)
{
    AfficherImg(e.Backg[0], screen);

    if (e.NumE >= 2 && e.NumE <= 4)
        Afficher_txt(e.txt, screen);
}
void animer(Enigme *e, SDL_Surface *screen)
{
    int EnigmeTimeS, EnigmeTimeSPred = -1;

    // TimeSeconds
    EnigmeTimeS = (SDL_GetTicks() - e->TimeInit) / 1000;

    // Check if Not TimeOut
    if (e->Duration - EnigmeTimeS < 0)
    {
        e->TimeOut = 1;
        return;
    }

    // Check That a Sec Passed
    if (EnigmeTimeSPred != EnigmeTimeS)
    {
        afficherEnigme(*e, screen);
        Afficher_txt(e->Time[e->Duration - EnigmeTimeS], screen);
        SDL_Flip(screen);
    }
    EnigmeTimeSPred = EnigmeTimeS;
}

/**
 * @brief free riddle
 *
 * @param e Enigme
 */
void Free_Enigme(Enigme *e)
{
    for (int i = 0; i < 3; i++)
        SDL_FreeSurface(e->Backg[i].img);
    for (int i = 0; i <= e->Duration; i++)
        SDL_FreeSurface(e->Time[i].surfaceText);
}

/**
 * @brief switch player
 *
 * @param Confg Configuration
 */
void SwitchPlayer(Config *Confg, int j)
{
    if (j == 7)
    {
        if (Confg->LevelR == 2)
            if (Confg->Player == 1)
                Confg->Player = 2;
            else
                Confg->Player = 1;
        else if (Confg->LevelR == 3)
            if (Confg->Player == 1)
                Confg->Player = 3;
            else if (Confg->Player == 2)
                Confg->Player = 1;
            else
                Confg->Player = 2;
    }
    else if (j == 8)
    {
        if (Confg->LevelR == 3)
            if (Confg->Player == 3)
                Confg->Player = 1;
            else if (Confg->Player == 2)
                Confg->Player = 3;
            else
                Confg->Player = 2;
    }
}
