#include "Background.h"
#include "Main_Fn.h"

void InitGameBackg(background *Backg, char NameImg[])
{
    Backg->img = IMG_Load(NameImg);
    Backg->pos.x = 0;
    Backg->pos.y = 0;
    Backg->cam.x = 0;
    Backg->cam.y = 0;
    Backg->cam.w = Width;
    Backg->cam.h = Height;
}

void AfficherBackg(background Backg, SDL_Surface *screen)
{
    SDL_BlitSurface(Backg.img, &Backg.cam, screen, &Backg.pos);
}

void animer_background(background *e)
{
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
        {
            return 1;
        }
        // Left
        color = GetPixel(Masque, posX, i);
        if (color.r == 255 && color.g == 255 && color.b == 1)
            return -1;
    }

    return 0;
}

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
        if (color.r == 255 && color.g == 255 && color.b == 1)
            return 1;
    }
    return 0;
}

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
        color = GetPixel(Masque, posX, i);
        printf("R: %d G: %d B: %d\n",color.r,color.g,color.b);
        if (color.r == 0 && color.g == 0 && color.b == 254)
            return 1;
        // Left Green
        /*color = GetPixel(Masque, posX1, i);
        if (color.r == 0 && color.g == 0 && color.b == 254)
            return 1;*/
    }
    return 0;
}
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

void scrolling(background *Backg, background *Masque, int direction, int pas_Avancement)
{
    switch (direction)
    {
    case 1:
        Backg->cam.x += pas_Avancement;
        // Masque->cam.x += pas_Avancement;
        break;
    case -1:
        Backg->cam.x -= pas_Avancement;
        // Masque->cam.x -= pas_Avancement;
        break;
    case 2:
        Backg->cam.y -= pas_Avancement;
        // Masque->cam.y -= pas_Avancement;
        break;
    case -2:
        Backg->cam.y += pas_Avancement;
        // Masque->cam.y += pas_Avancement;
        break;
    }
}

void LibererBackg(background backg)
{
    SDL_FreeSurface(backg.img);
}