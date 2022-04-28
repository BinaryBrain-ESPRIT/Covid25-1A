#ifndef Background_H
#define Background_H

#include <SDL/SDL.h>
#include "player.h"

typedef struct Image1
{
    SDL_Rect pos;
    SDL_Surface *img;
    char NameImg[50];
}Image1;

typedef struct
{
    Image1 BackgImage[5];
    SDL_Rect cam;
    int Anim,AnimI;
} background;

void InitGameBackg(background *Backg, int x, int y, int W, int H);
void AfficherBackg(background Backg, SDL_Surface *screen);
void animer_background(background *Backg, SDL_Surface *screen);
int collisionPH(Player p, SDL_Surface *Masque);
int isTrapped(Player p, SDL_Surface *Masque);
int isGround(Player p, SDL_Surface *Masque);
int HighHeight(Player p, SDL_Surface *Masque);
int Interaction(Player p, SDL_Surface *Masque);
int EnigmeDetected(Player p, SDL_Surface *Masque);
void scrolling(background *Backg, int direction, int pas_Avancement);
void LibererBackg(background backg);

#endif
