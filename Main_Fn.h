#ifndef Main_Fn_H
#define Main_Fn_H


#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#include "Text_Image.h"

#define Width 1920
#define Height 1080
#define Bpp 32
#define FPS 60
#define FRAME_TARGET_TIME (1000/FPS)
#define Redim 12

typedef struct {
    int isRunning;
    int Volume,posVol;
    int Fullscr;
    int Lang;
    int LevelR,Level;
    int Player;
    int Money;
    double deltaTime;
}Config;


void PlayMusic(char NameMusic[], Mix_Music * music);
void PlayChunkMusic(char NameMusic[], Mix_Chunk *sound);
void Liberer_Mus(Mix_Music * music);
void Liberer_MusCh(Mix_Chunk * sound);


int Setup(Config * Confg);
void SaveSetting(Config *Confg);
void InitImg_fr(Image *tabMO,Image * tabMAO);
void InitImg_en(Image *tabMO,Image * tabMAO);
void InitTxt_en(Text *tabMT,Text * tabMAT);
void InitTxt_fr(Text *tabMT,Text * tabMAT);



#endif 