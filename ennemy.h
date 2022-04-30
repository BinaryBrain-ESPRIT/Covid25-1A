/**
 * @file ennemy.h
 * @author Mohamed Habib Allah Bibani (mohamedhabiballah.bibani@esprit.tn)
 * @brief Header File for Ennemy
 * @version 1.0
 * @date 2022-04-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ennemy_H
#define ennemy_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "player.h"
#include "Main_Fn.h"

/**
 * @struct Ennemy
 * @brief Struct For Ennemy
 */
typedef struct Ennemy
{
    SDL_Rect pos, posABS; /*!<Rectangle For Ennemy Position*/
    SDL_Surface *img[6][20]; /*!<Surface For Ennmy*/
    int Flipped; /*!<Int to check if his flipped or not*/
    double v; /*!<Ennemy Speed*/
    int direction; /*!<Ennemy Direction*/
    int nbreVie; /*!<Ennemy Life*/
    int isKilled; /*!<check if Ennely IsKilled or not*/
    int anim_i, anim_j; /*!<Index For the Matrix*/
    int posInit; /*!<Initial x position For the Ennemy*/
    int attack; /*!<Check If the ennemy attacking or not*/
    int AnimE_Attack, AnimE_Run, AnimeE_Idle; /*!<Variables For the Animation Speed*/
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