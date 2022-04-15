#ifndef enigme_H
#define enigme_H

#include "Text_Image.h"

typedef struct
{
  Image Backg[3];
  FILE *f;
  Text Time[20];
  Text Quest, Quest1;
  Text Rep[3];
  int NumRepC;
  int NumE;
  int Duration, TimeInit, TimeOut;
} enigme;

int InitEnigme1(enigme *e, char *nomfichier);
void afficherEnigme1(enigme e, SDL_Surface *screen);
void animer1(enigme *e, SDL_Surface *screen);
void sauvegarder1(Player p, Image b, char *nomfichier);
int charger(Player p, background *b, char *nomfichier);
void Free_Enigme1(enigme *e);
#endif
