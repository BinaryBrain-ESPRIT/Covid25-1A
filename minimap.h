#ifndef minimap_H
#define minimap_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "player.h"
#include "ennemy.h"

typedef struct
{
    SDL_Surface *image, *image1, *playerTag, *zombieTag[5];
    SDL_Rect pos, pos1, playerTagPos, zombieTagPos[5];
} minimap;
typedef struct Score
{
    Text PlayerName, Time, ScoreTxt;
    int Score;
} Score;

void initminimap(minimap *m, char nameimg[], Player p, Ennemy e[]);
void MAJMinimap(SDL_Rect PosJoueur, Ennemy e[], minimap *m, int redimensionnement);
void afficherminimap(minimap m, SDL_Surface *screen);
void Liberer(minimap *m);
void SaveScore(int score, char nomjoueur[], char nomfichier[]);
void LeaderBoard(SDL_Surface *screen, Config *Confg);
void MAJTime(Text *GameTimeTxt, int GameTimeInit);

#endif