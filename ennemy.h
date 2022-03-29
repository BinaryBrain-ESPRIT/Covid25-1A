#ifndef ennemy_H
#define ennemy_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "player.h"

#include "Main_Fn.h"
typedef struct
{
    SDL_Rect pos;
    SDL_Surface *img[5][10];
    int numAnim;
    double v; // Vitesse
    int direction;
    int nbreVie;
    int anim_i, anim_j;
    int posInit;
    int attack;
    int AnimE_Attack, AnimE_Run, AnimeE_Idle;
} Ennemy;

void initEnnemy(Ennemy *e, int x, int y, int vitesse, int direction, int nbreVie);
void afficherEnnemy(Ennemy e, SDL_Surface *screen);
void animerEnnemy(Ennemy *e, Config *Confg);
void deplacerEnnemy(Ennemy *e, Config *Confg);
void deplacerIA(Ennemy *e, SDL_Rect posPerso);
int collisionBB(Ennemy e, Player p);

#endif