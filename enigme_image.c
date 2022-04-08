#include "enigme_image.h"
void InitEnigme(Enigme *e, char *nomfichier)
{
    FILE *f;
    char ImgTimer[10];
    char NomBackg[100];
    char NomBackgW[100];
    char NomBackgL[100];
    char NomTimer[100];
    int Res;
    // int RandNum = rand() % (3 - 1) + 1;
    f = fopen(nomfichier, "r");

    fscanf(f, "%d %s %s %s %d", &e->NumE, NomBackg, NomBackgW, NomBackgL, &e->NumRC);

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
