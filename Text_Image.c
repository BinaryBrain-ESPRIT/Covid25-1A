#include "Text_Image.h"

// TXT FN
void InitTitle(Text *text, char Title[])
{
    text->pos.x = 600;
    text->pos.y = 70;
    text->font = TTF_OpenFont("assets/Font/Doctor Glitch.otf", 120);
    text->color.r = 255;
    text->color.g = 255;
    text->color.b = 255;
    strcpy(text->Texte, Title);
    text->surfaceText = TTF_RenderText_Solid(text->font, text->Texte, text->color);
}

void iniText(Text *t, int posY, char name[50])
{
    t->pos.x = 50;
    t->pos.y = posY;
    t->font = TTF_OpenFont("assets/Font/AznKnucklesTrial-z85pa.otf", 70);
    t->color.r = 0;
    t->color.g = 0;
    t->color.b = 0;
    strcpy(t->Texte, name);
    t->surfaceText = TTF_RenderText_Solid(t->font, t->Texte, t->color);
}
void initTxt(Text *t, int x, int y, SDL_Color color, int size, char Font[], char Texte[])
{
    t->pos.x = x;
    t->pos.y = y;
    t->font = TTF_OpenFont(Font, size);
    t->color = color;
    strcpy(t->Texte, Texte);
    t->surfaceText = TTF_RenderText_Solid(t->font, t->Texte, t->color);
}

void iniActiveText(Text *t, int posY, char name[50])
{
    t->pos.x = 50;
    t->pos.y = posY;
    t->font = TTF_OpenFont("assets/Font/AznKnucklesTrial-z85pa.otf", 80);
    t->color.r = 174;
    t->color.g = 38;
    t->color.b = 64;
    strcpy(t->Texte, name);
    t->surfaceText = TTF_RenderText_Solid(t->font, t->Texte, t->color);
}

void Afficher_txt(Text text, SDL_Surface *screen)
{
    SDL_BlitSurface(text.surfaceText, NULL, screen, &text.pos);
}

void Liberer_txt(Text text)
{
    SDL_FreeSurface(text.surfaceText);
    TTF_CloseFont(text.font);
    
}

// IMG FN
void InitBackg(Image *Backg, char NomImg[])
{
    Backg->img = IMG_Load(NomImg);
    Backg->pos.x = 0;
    Backg->pos.y = 0;
}

void initImg(Image *Img, int x, int y, char NomImg[])
{
    Img->img = NULL;
    Img->img = IMG_Load(NomImg);
    Img->pos.x = x;
    Img->pos.y = y;
}

void AfficherImg(Image img, SDL_Surface *screen)
{

    SDL_BlitSurface(img.img, NULL, screen, &img.pos);
}

void Liberer_Img(Image Img)
{
    SDL_FreeSurface(Img.img);
}
