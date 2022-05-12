#ifndef enigme_H
#define enigme_H

#include "Text_Image.h"
#include "minimap.h"
/**
 * 
 * @struct enigme
 * @brief Struct for enigme
 * 
 */
typedef struct
{
  Image Backg[3]; /*!<background array  */
  FILE *f; /*!<File  */
  Text Time[20]; /*!<Time array  */
  Text Quest, Quest1; /*!<Quest */
  Text Rep[3];   /*!<Rep array  */
  int NumRepC; /*!<NumRep Array  */
  int NumE;  /*!<Number of Riddle  */
  int Duration, TimeInit, TimeOut;  /*!<Time Variable  */
} enigme;

int InitEnigme1(enigme *e, char *nomfichier);
void afficherEnigme1(enigme e, SDL_Surface *screen);
void animer1(enigme *e, SDL_Surface *screen);
void sauvegarder1(Player p, Image b, char *nomfichier);
int charger(Player p, background *b, char *nomfichier);
void Free_Enigme1(enigme *e);
void LoadGame(Config *Confg, SDL_Rect *PlayerPos, SDL_Rect *PlayerPosABS,Ennemy * e, SDL_Rect *PlayerTagPos, SDL_Rect EnnemyTagPos[],int EnnemyDie[], SDL_Rect *cam);
#endif
