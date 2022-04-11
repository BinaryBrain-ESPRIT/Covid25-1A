#ifndef Menu_H
#define Menu_H

#include <SDL/SDL.h>
#include "player.h"
#include "Text_Image.h"
#include "Main_Fn.h"
#include "Mouse.h"
#include "ennemy.h"

void AffichageMainMenu(SDL_Surface *screen, Text tabT[], Text tabAT[], Image tabI[][3], int j, int l, int p);
void AffichageMenuOpt(SDL_Surface *screen, Image tabMO[], Image tabMAO[], int j);
void AffichageCredits(SDL_Surface *screen, Config *Confg);
void ChoosePlayerName(Player *p, Config *Confg,SDL_Surface * screen);
void SelectLevel(SDL_Surface *screen, Config *Confg);
void MenuNG(SDL_Surface *screen, Config *Confg);
void MenuInGame(SDL_Surface *screen, Config *Confg, int *Opened, int *isRunning);
void MenuOpt(SDL_Surface *screen, Config *Confg);
#endif