#ifndef ennemy_H
#define ennemy_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "player.h"
#include "Main_Fn.h"

typedef struct
{
    SDL_Rect pos, posABS;
    SDL_Surface *img[6][20];
    int Flipped;
    double v; // Vitesse
    int direction;
    int nbreVie, isKilled;
    int anim_i, anim_j;
    int posInit;
    int attack;
    int AnimE_Attack, AnimE_Run, AnimeE_Idle;
} Ennemy;

void initEnnemy(Ennemy *e, int x, int y, int vitesse, int nbreVie);
void afficherEnnemy(Ennemy e, SDL_Surface *screen);
void animerEnnemy(Ennemy *e, Config *Confg);
void deplacerEnnemy(Ennemy *e, Config *Confg);
void deplacerIA(Ennemy *e, Player p);
int collisionBB(Ennemy e, Player p);
void LibererEnnemy(Ennemy e);
int collisionEH(Ennemy e, SDL_Surface *Masque);
int collisionEV(Ennemy e, SDL_Surface *Masque);
SDL_Color GetPixel1(SDL_Surface *pSurface, int x, int y);
int BehindEnnemy(Player p, Ennemy e);

#endif