/**
 * @file minimap.h
 * @author oussamaawledsalem
 * @brief 
 * @version 0.1
 * @date 2022-04-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef minimap_H
#define minimap_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "player.h"
#include "ennemy.h"

/**
 * @struct struct minimap
 * @brief struct for minimap
 * 
 */
typedef struct
{
    SDL_Surface *image, *image1, *playerTag, *zombieTag[5];
    SDL_Rect pos, pos1, playerTagPos, zombieTagPos[5];
    int EnnemyDie[5];
} minimap;
/**
 * @struct struct score
 * @brief struct for score
 * 
 */
typedef struct Score
{
    Text PlayerName, Time, ScoreTxt;
    int Score;
} Score;
/**
 * @struct struct card
 * @brief struct for card
 * 
 */
typedef struct card
{
    Image Image;
    Image RImage;
    int Turned;
    int Done;
    int CardNumber;
} card;

void initminimap(minimap *m, char nameimg[], Player p, Ennemy e[]);
void MAJMinimap(SDL_Rect PosJoueur, Ennemy e[], minimap *m, int redimensionnement);
void afficherminimap(minimap m, SDL_Surface *screen);
void Liberer(minimap *m);
void SaveScore(char PlayerName[], int Score, char Time[]);
void LeaderBoard(SDL_Surface *screen, Config *Confg);
void MAJTime(Text *GameTimeTxt, int GameTimeInit);
void MiniGameCard(SDL_Surface *screen, Config *Confg);

#endif