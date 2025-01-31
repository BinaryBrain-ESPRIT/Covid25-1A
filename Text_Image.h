#ifndef Text_Image_H
#define Text_Image_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "Background.h"

typedef struct
{
    SDL_Rect pos;
    SDL_Color color;
    SDL_Surface *surfaceText;
    TTF_Font *font;
    char Texte[100];
} Text;

typedef struct
{
    SDL_Rect pos;
    SDL_Surface *img;
    char NameImg[100];
} Image;


// Txt FN
void InitTitle(Text *text, char Title[]);
void iniText(Text *t, int posY, char name[]);
void initTxt(Text *t, int x, int y, SDL_Color color, int size, char Font[], char Texte[]);
void iniActiveText(Text *t, int posY, char name[]);
void Afficher_txt(Text text, SDL_Surface *screen);
void Liberer_txt(Text text);

// IMG FN
void InitBackg(Image *Backg, char NomImg[]);
void initImg(Image *Img, int x, int y, char NomImg[]);
void AfficherImg(Image Img, SDL_Surface *screen);
void Liberer_Img(Image Img);

#endif