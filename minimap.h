#ifndef minimap_H
#define minimap_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "player.h"
typedef struct 
{
    SDL_Surface *image,*playerTag;
    SDL_Rect pos,playerTagPos;  
}minimap;

void initminimap(minimap *m,char nameimg[], Player p);
void MAJMinimap(SDL_Rect PosJoueur,minimap *m,SDL_Rect camera, int redimensionnelent);
void afficherminimap(minimap m,SDL_Surface *screen);
void Liberer (minimap * m);
void sauvegarder(int score,char nomjoueur[],char nomfichier[]);
void meilleur(char nomfichier[],int *score,char nomjoueur[]);

#endif