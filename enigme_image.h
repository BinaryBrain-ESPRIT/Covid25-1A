#ifndef Enigme_H_INCLUDED
#define Enigme_H_INCLUDED

#include <SDL/SDL.h>
#include "Text_Image.h"
#include "Main_Fn.h"


/**
 * @struct Enigme
 * @brief Struct for Enigme
 */
typedef struct Enigme
{
    Image Backg[3]; /*!<background array  */
    Text Time[20];/*!<time array*/
    int NumRC;/*!<Correct answer's number*/
    int NumE;/*!<riddle's number*/
    int Duration,TimeInit,TimeOut;/*!<time variables*/
    Text txt;/*!<text*/
} Enigme;

void InitEnigme(Enigme *e, char *nomfichier);
void afficherEnigme(Enigme e, SDL_Surface *screen);
void animer(Enigme *e, SDL_Surface *screen);

void Free_Enigme(Enigme *e);
void SwitchPlayer(Config * Confg);
#endif