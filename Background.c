#include "Background.h"
#include "Main_Fn.h"

void InitGameBackg(background *Backg, int x, int y, int W, int H,int Lvl)
{

    for (int i = 0; i < 5; i++)
    {
        sprintf(Backg->BackgImage[i].NameImg, "assets/Levels/Level%d/Level%d[%d].jpg",Lvl,Lvl, i);
        Backg->BackgImage[i].img = IMG_Load(Backg->BackgImage[i].NameImg);        
        Backg->BackgImage[i].pos.x = x;
        Backg->BackgImage[i].pos.y = y;
        Backg->BackgImage[i].pos.w = W;
        Backg->BackgImage[i].pos.h = H;
    }

    Backg->cam.x = 0;
    Backg->cam.y = 0;
    Backg->cam.w = W;
    Backg->cam.h = H;
    Backg->Anim = 0;
    Backg->AnimI = 0;
}

void AfficherBackg(background Backg, SDL_Surface *screen)
{
    SDL_BlitSurface(Backg.BackgImage[Backg.AnimI].img, &Backg.cam, screen, &Backg.BackgImage[Backg.AnimI].pos);
}

void animer_background(background *Backg, SDL_Surface *screen)
{
    if (Backg->Anim > 2)
    {
        if (Backg->AnimI > 3)
            Backg->AnimI = 0;
        else
            Backg->AnimI++;
        Backg->Anim = 0;
    }
    else
        Backg->Anim++;
}

SDL_Color GetPixel(SDL_Surface *pSurface, int x, int y)
{
    SDL_Color color;
    Uint32 col = 0;

    // Determine Pos
    char *pPosition = (char *)pSurface->pixels;
    pPosition += (pSurface->pitch * y);
    pPosition += (pSurface->format->BytesPerPixel * x);
    memcpy(&col, pPosition, pSurface->format->BytesPerPixel);

    // convertir color
    SDL_GetRGB(col, pSurface->format, &color.r, &color.g, &color.b);

    return color;
}

// Jaune Droite Gauche
int collisionPH(Player p, SDL_Surface *Masque)
{
    SDL_Color color;

    int posX = p.posABS.x;
    int posY = p.posABS.y;
    int posX1 = posX + p.img[p.animI][p.animJ]->w;
    int posY1 = posY + p.img[p.animI][p.animJ]->h;

    for (int i = posY; i <= posY1 - 50; i++)
    {
        // Right
        color = GetPixel(Masque, posX1, i);
        if (color.r == 255 && color.g == 255 && color.b == 1)
            return 1;

        // Left
        color = GetPixel(Masque, posX, i);
        if (color.r == 255 && color.g == 255 && color.b == 1)
            return -1;
    }

    return 0;
}

// Jaune
int HighHeight(Player p, SDL_Surface *Masque)
{
    SDL_Color color;
    int posX = p.posABS.x;
    int posY = p.posABS.y;
    int posX1 = posX + p.img[p.animI][p.animJ]->w;
    int posY1 = posY + p.img[p.animI][p.animJ]->h;

    for (int i = posX; i <= posX1; i++)
    {
        // TOP Yellow
        color = GetPixel(Masque, i, posY);
        if (color.r == 255 && color.g == 255 && color.b == 1)
            return 1;
    }
    return 0;
}

// Rouge
int isTrapped(Player p, SDL_Surface *Masque)
{
    SDL_Color color;
    int posX = p.posABS.x;
    int posY = p.posABS.y;
    int posX1 = posX + p.img[p.animI][p.animJ]->w;
    int posY1 = posY + p.img[p.animI][p.animJ]->h;

    for (int i = posX; i <= posX1; i++)
    {
        color = GetPixel(Masque, i, posY1);
        if (color.r == 254 && color.g == 0 && color.b == 0)
            return 1;
    }
    return 0;
}

// Jaune
int isGround(Player p, SDL_Surface *Masque)
{
    SDL_Color color;
    int posX = p.posABS.x;
    int posY = p.posABS.y;
    int posX1 = posX + p.img[p.animI][p.animJ]->w;
    int posY1 = posY + p.img[p.animI][p.animJ]->h;

    for (int i = posX; i <= posX1; i++)
    {
        // Bot Yellow
        color = GetPixel(Masque, i, posY1);
        if (color.r == 255 && color.g == 255 && (color.b == 1 || color.b == 0))
            return 1;
    }
    return 0;
}

// Bleu
int EnigmeDetected(Player p, SDL_Surface *Masque)
{
    SDL_Color color;
    int posX = p.posABS.x;
    int posY = p.posABS.y;
    int posX1 = posX + p.img[p.animI][p.animJ]->w;
    int posY1 = posY + p.img[p.animI][p.animJ]->h;

    for (int i = posY; i <= posY1 - 10; i++)
    {
        // Right Green
        color = GetPixel(Masque, posX1, i);
        if (color.r == 0 && color.g == 0 && color.b == 254)
            return 1;
        // Left Green
        /*color = GetPixel(Masque, posX, i);
        if (color.r == 0 && color.g == 0 && color.b == 254)
            return 1;*/
    }
    return 0;
}

// Vert
int Interaction(Player p, SDL_Surface *Masque)
{
    SDL_Color color;
    int posX = p.posABS.x;
    int posY = p.posABS.y;
    int posX1 = posX + p.img[p.animI][p.animJ]->w;
    int posY1 = posY + p.img[p.animI][p.animJ]->h;

    for (int i = posY; i <= posY1 - 10; i++)
    {
        // Right Green
        color = GetPixel(Masque, posX, i);
        if (color.r == 0 && color.g == 255 && color.b == 1)
            return 3;
        // Left Green
        color = GetPixel(Masque, posX1, i);
        if (color.r == 0 && color.g == 255 && color.b == 1)
            return 4;
    }

    for (int i = posX; i <= posX1; i++)
    {
        // Top Green
        color = GetPixel(Masque, i, posY);
        if (color.r == 0 && color.g == 255 && color.b == 1)
            return 1;
        // Bot Green
        color = GetPixel(Masque, i, posY1);
        if (color.r == 0 && color.g == 255 && color.b == 1)
            return 2;
    }

    return 0;
}

void scrolling(background *Backg, int direction, int pas_Avancement)
{
    switch (direction)
    {
    case 1:
        Backg->cam.x += pas_Avancement;
        break;
    case -1:
        Backg->cam.x -= pas_Avancement;
        break;
    case 2:
        Backg->cam.y -= pas_Avancement;
        break;
    case -2:
        Backg->cam.y += pas_Avancement;
        break;
    }
}

void LibererBackg(background backg)
{
    for (int i = 0; i < 5; i++)
        SDL_FreeSurface(backg.BackgImage[i].img);
}