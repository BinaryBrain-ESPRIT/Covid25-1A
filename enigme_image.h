#ifndef Enigme_H_INCLUDED
#define Enigme_H_INCLUDED

#include <SDL/SDL.h>
#include "Text_Image.h"

typedef struct
{
    Image Backg[3];
    Text Time;
    int NumRC;
    int NumE;
    int Duration,TimeInit;
    Text txt;
} Enigme;

void InitEnigme(Enigme *e, char *nomfichier);
void afficherEnigme(Enigme e, SDL_Surface *screen);
void animer(Enigme *e, SDL_Surface *screen);
void Free_Enigme(Enigme *e);

#endif