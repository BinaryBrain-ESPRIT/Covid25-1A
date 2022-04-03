#ifndef PLAYER_H
#define PLAYER_H


#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

typedef struct
{

  int nbreVie;
  SDL_Rect pos,posABS;
  SDL_Surface * img[6][10];
  double v; 
  int score;
  int direction;
  int animI,animJ;
  int flipped;
  int AnimP_Idle, AnimP_Run, AnimP_Attack,AnimP_Die;

} Player;



void initPerso(Player *p, int NumPlayer);
void afficherPerso(Player p, SDL_Surface *screen);
void deplacerPerso(Player *p, int dt);
void animerPerso(Player *p);
void saut(Player *p);
void LibererPlayer(Player p);
#endif