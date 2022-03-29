#ifndef enigme_H
#define enigme_H


#include "Text_Image.h"


typedef struct{
  SDL_Surface * back;
  FILE * f;
}enigme;
typedef struct
{
  Image Backg;
  FILE * f;
  Text Quest;
  Text Rep[3];
  int NumRepC;

} enigme;
void InitEnigme(enigme *e, char *nomfichier);
void afficherEnigme(enigme e, SDL_Surface *screen);
void animer(enigme *e);
void sauvegarder(Player p, Image b, char *nomfichier[]);
int charger(Player p, background *b, char *nomfichier[]);

#endif
