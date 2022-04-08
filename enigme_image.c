#include "enigme_image.h"
#include "Main_Fn.h"
void InitEnigme(Enigme *e, char *nomfichier)
{
    SDL_Color White = {255, 255, 255};
    FILE *f;
    char ImgTimer[10];
    char NomBackg[100];
    char NomBackgW[100];
    char NomBackgL[100];
    char NomTimer[100];

    int RandNum = rand() % (5 - 1) + 1;
    f = fopen(nomfichier, "r");

    do
        fscanf(f, "%d %s %s %s %d", &e->NumE, NomBackg, NomBackgW, NomBackgL, &e->NumRC);
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

    InitBackg(&e->Backg[0], NomBackg);
    InitBackg(&e->Backg[1], NomBackgW);
    InitBackg(&e->Backg[2], NomBackgL);

    for (int i = 1; i < 11; i++)
    {
        strcpy(NomTimer, "assets/enigmeImage/Timer/");
        sprintf(ImgTimer, "%d.jpg", i);
        strcat(NomTimer, ImgTimer);
        initImg(&e->Timer[i - 1], 1637, 40, NomTimer);
    }
    e->TimerI = 0;

    fclose(f);
}
void afficherEnigme(Enigme e, SDL_Surface *screen)
{
    AfficherImg(e.Backg[0], screen);

    if (e.NumE >= 2 && e.NumE <= 4)
        Afficher_txt(e.txt,screen);
}
void animer(Enigme *e, SDL_Surface *screen)
{
    AfficherImg(e->Timer[10 - e->TimerI - 1], screen);
    e->TimerI++;
}
void Free_Enigme(Enigme *e)
{
    for (int i = 0; i < 3; i++)
        SDL_FreeSurface(e->Backg[i].img);
    for (int i = 0; i < 10; i++)
        SDL_FreeSurface(e->Timer[i].img);
}
