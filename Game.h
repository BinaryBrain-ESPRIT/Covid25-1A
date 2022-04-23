#ifndef Game_H
#define Game_H

#include <SDL/SDL.h>
#include "player.h"
#include "Text_Image.h"
#include "Main_Fn.h"
#include "Mouse.h"
#include "ennemy.h"



void AffichageMainMenu(SDL_Surface *screen, Text tabT[], Text tabAT[], Image tabI[][3], int j, int l, int p);
void AffichageMenuOpt(SDL_Surface *screen, Image tabMO[], Image tabMAO[], int j);
void AffichageCredits(SDL_Surface *screen, Config *Confg);
void ChoosePlayerName(Player *p, Config *Confg, SDL_Surface *screen);
void SelectLevel(SDL_Surface *screen, Config *Confg);
void Game(SDL_Surface *screen, Config *Confg);
void MultiPlayerGame(SDL_Surface *screen, Config *Confg);
int MenuInGame(SDL_Surface *screen, Config *Confg, int *Opened, int *isRunning);
void MenuOpt(SDL_Surface *screen, Config *Confg);
int AfficherEnigmeImage(SDL_Surface *screen, Config *Confg, int GameTimeInit, SDL_Surface *Masque, Player p);
int AfficherEnigmeTexte(SDL_Surface *screen, Config *Confg, int GameTimeInit, SDL_Surface *Masque);
int WinGame(Config *Confg, SDL_Surface *screen);
int LooseGame(Config *Confg, SDL_Surface *screen);
int SaveGame(Config *Confg, SDL_Surface *screen);
#endif