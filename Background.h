#ifndef Background_H
#define Background_H


#include <SDL/SDL.h>
#include "player.h"

typedef struct
{
    SDL_Rect pos;
    SDL_Surface *img;
    SDL_Rect cam;
} background;


void InitGameBackg(background *Backg, char NameImg[]);
void AfficherBackg(background Backg, SDL_Surface *screen);
void animer_background(background *e);
int collisionPP(Player p, SDL_Surface Masque);
void scrolling(background *Backg, int direction, int pas_Avancement);
void LibererBackg(background backg);

#endif
