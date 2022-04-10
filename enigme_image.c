#include "enigme_image.h"
#include "Main_Fn.h"
void InitEnigme(Enigme *e, char *nomfichier)
{
    SDL_Color White = {255, 255, 255};
    FILE *f;

    int RandNum = rand() % (5 - 1) + 1;
    f = fopen(nomfichier, "r");

    do
        fscanf(f, "%d %s %s %s %d", &e->NumE, e->Backg[0].NameImg, e->Backg[1].NameImg, e->Backg[2].NameImg, &e->NumRC);
    while (e->NumE != RandNum);

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

    InitBackg(&e->Backg[0], e->Backg[0].NameImg);
    InitBackg(&e->Backg[1], e->Backg[1].NameImg);
    InitBackg(&e->Backg[2], e->Backg[2].NameImg);

    e->Duration = 20;
    fclose(f);
}
void afficherEnigme(Enigme e, SDL_Surface *screen)
{
    AfficherImg(e.Backg[0], screen);

    if (e.NumE >= 2 && e.NumE <= 4)
        Afficher_txt(e.txt, screen);
}
void animer(Enigme *e, SDL_Surface *screen)
{
    int EnigmeTimeS, EnigmeTimeSPred = -1;
    SDL_Color Black = {0, 0, 0};
    SDL_Color Red = {193, 39, 45};

    EnigmeTimeS = (SDL_GetTicks() - e->TimeInit) / 1000;

    if (EnigmeTimeSPred != EnigmeTimeS)
    {
        sprintf(e->Time.Texte, "00:%02d", e->Duration - EnigmeTimeS);
        if (e->Duration - EnigmeTimeS > 5)
            initTxt(&e->Time, 1707, 26, Black, 70, "assets/Font/AznKnucklesTrial-z85pa.otf", e->Time.Texte);
        else
            initTxt(&e->Time, 1707, 26, Red, 70, "assets/Font/AznKnucklesTrial-z85pa.otf", e->Time.Texte);
        afficherEnigme(*e, screen);
        Afficher_txt(e->Time, screen);
        SDL_Flip(screen);
    }
    EnigmeTimeSPred = EnigmeTimeS;
}
void Free_Enigme(Enigme *e)
{
    for (int i = 0; i < 3; i++)
        SDL_FreeSurface(e->Backg[i].img);
    SDL_FreeSurface(e->Time.surfaceText);
}
