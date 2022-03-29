#ifndef Enigme_H_INCLUDED
#define Enigme_H_INCLUDED

#include <SDL/SDL.h>
#include "Text_Image.h"
typedef struct{
    SDL_Surface* img;
    SDL_Surface * hide;
    SDL_Rect pos;
    int Turned;
    int type;
    char NomIMG[100];
    int done;
}Card;
typedef struct 
{
    Image Backg[3];
    Card tabC[3][3];
}Enigme;


void InitEnigme(Enigme * e, char *nomfichier);
void afficherEnigme(Enigme e, SDL_Surface * screen);
void animer (Enigme *e,SDL_Surface * screen);
void Free_Enigme(Enigme *e);
int Verifier(Enigme e, int l, int c);



#endif