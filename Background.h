#ifndef Background_H
#define Background_H

#include <SDL/SDL.h>
#include "player.h"

typedef struct
{
    SDL_Rect pos;
    SDL_Surface *img;
    char NameImg[100];
} Image1;
typedef struct
{
    SDL_Rect pos;
    SDL_Surface *img;
    SDL_Rect cam;
    Image1 AnimBackg[10];
    int Anim;
} background;

void InitGameBackg(background *Backg, int x, int y, int W, int H, char NameImg[]);
void AfficherBackg(background Backg, SDL_Surface *screen);
int animer_background(background *Backg, SDL_Surface *screen, int Anim);
int collisionPH(Player p, SDL_Surface *Masque);
int isTrapped(Player p, SDL_Surface *Masque);
int isGround(Player p, SDL_Surface *Masque);
int HighHeight(Player p, SDL_Surface *Masque);
int Interaction(Player p, SDL_Surface *Masque);
int EnigmeDetected(Player p, SDL_Surface *Masque);
void scrolling(background *Backg, int direction, int pas_Avancement);
void LibererBackg(background backg);

#endif
