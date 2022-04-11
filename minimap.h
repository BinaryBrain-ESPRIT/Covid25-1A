#ifndef minimap_H
#define minimap_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "player.h"
#include "ennemy.h"

typedef struct 
{
    SDL_Surface *image,*image1,*playerTag,*zombieTag[5];
    SDL_Rect pos,pos1,playerTagPos,zombieTagPos[5];  
}minimap;

void initminimap(minimap *m,char nameimg[], Player p,Ennemy e[]);
void MAJMinimap(SDL_Rect PosJoueur,Ennemy e[],minimap *m,int redimensionnement);
void afficherminimap(minimap m,SDL_Surface *screen);
void Liberer (minimap * m);
void sauvegarder(int score,char nomjoueur[],char nomfichier[]);
void meilleur(char nomfichier[],int *score,char nomjoueur[]);
void MAJTime(Text *GameTimeTxt, int GameTimeInit);

#endif