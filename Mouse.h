#ifndef Mouse_H
#define Mouse_H

#include "Text_Image.h"
#include "Main_Fn.h"
#include "Game.h"

void Motion_MM(Text tabMT[], Text tabMAT[], Image tabM[][3], SDL_Event event, SDL_Surface *screen, int *i, Config *Confg);
void Motion_MG(Image *tabMG, SDL_Surface *screen, SDL_Event event, int *i);
void Motion_MO(SDL_Surface *screen, Config *Confg, SDL_Event event, Image *tabMO, Image *tabMAO, int *i);
int MotionSL(Image LevelBut[], int j, SDL_Event event, int LevelSelected);
#endif