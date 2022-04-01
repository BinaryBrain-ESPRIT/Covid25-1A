#ifndef enigme_H
#define enigme_H

#include "Text_Image.h"

typedef struct
{
  Image Backg[3];
  FILE *f;
  Image Timer[11];
  Text Quest;
  Text Rep[3];
  int NumRepC;
  int TimerI;
  int NumE;
} enigme;

void InitEnigme1(enigme *e, char *nomfichier);
void afficherEnigme1(enigme e, SDL_Surface *screen);
void animer1(enigme *e, SDL_Surface *screen);
void sauvegarder1(Player p, Image b, char *nomfichier);
int charger(Player p, background *b, char *nomfichier);

#endif
