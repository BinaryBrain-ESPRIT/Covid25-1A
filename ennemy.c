#include "ennemy.h"

void initEnnemy(Ennemy *e, int x, int y, int vitesse, int nbreVie)
{

    int direction;
    char NomImg[100];
    int n;
    e->pos.x = x;
    e->pos.y = y;

    do
        direction = rand() % (-1 - 2) - 1;
    while (direction == 0);

    e->direction = direction;
    e->nbreVie = nbreVie;
    e->v = 10;
    e->anim_j = 0;
    e->anim_i = 0;
    e->posInit = x;
    e->attack = 0;
    e->AnimE_Attack = 0;
    e->AnimE_Run = 0;
    e->AnimeE_Idle = 0;
    e->Flipped = 0;
    e->posABS = e->pos;

    for (int i = 0; i < 6; i++)
    {
        if (i == 0 || i == 1)
            n = 15;
        else if (i == 2 || i == 3)
            n = 10;
        else if (i == 4 || i == 5)
            n = 8;
        for (int j = 0; j < n; j++)
        {
            sprintf(NomImg, "assets/Animation/Zombie%d/%d/%d.png", 1, i, j + 1);
            e->img[i][j] = IMG_Load(NomImg);
        }
    }
}
void afficherEnnemy(Ennemy e, SDL_Surface *screen)
{
    SDL_BlitSurface(e.img[e.anim_i][e.anim_j], NULL, screen, &e.pos);
}

void animerEnnemy(Ennemy *e, Config *Confg)
{
    if (e->attack)
    {
        if (e->AnimE_Attack % 10 == 0)
        {
            if (!e->Flipped)
                e->anim_i = 4;
            else
                e->anim_i = 5;

            if (e->anim_j >= 7)
                e->anim_j = 0;
            else
                e->anim_j++;

            e->AnimE_Attack = 0;
        }
        e->AnimE_Attack += 2;
    }
    else
    {
        switch (e->direction)
        {
        case 0:
            if (e->AnimeE_Idle % 10 == 0)
            {
                e->anim_i = 0;
                if (e->anim_j >= 14)
                    e->anim_j = 0;
                else
                    e->anim_j++;
                e->AnimeE_Idle = 0;
            }
            e->AnimeE_Idle += 4;
            break;
        case 1:

            if (e->AnimE_Run % 10 == 0)
            {
                e->anim_i = 2;
                if (e->anim_j >= 9)
                    e->anim_j = 0;
                else
                    e->anim_j++;
                e->AnimE_Run = 0;
            }
            e->AnimE_Run += 4;
            break;
        case -1:
            if (e->AnimE_Run % 10 == 0)
            {
                e->anim_i = 3;
                if (e->anim_j >= 9)
                    e->anim_j = 0;
                else
                    e->anim_j++;

                e->AnimE_Run = 0;
            }
            e->AnimE_Run += 4;
            break;
        }
    }
}
void deplacerEnnemy(Ennemy *e, Config *Confg)
{
    if (e->direction == 1)
    {
        e->pos.x += e->v;
        e->posABS.x += e->v;
        e->Flipped = 0;
    }

    else if (e->direction == -1)
    {
        e->pos.x -= e->v;
        e->posABS.x -= e->v;
        e->Flipped = 1;
    }
}
void deplacerIA(Ennemy *e, SDL_Rect posPerso)
{
    if (posPerso.x > e->pos.x - 500 && posPerso.x < e->pos.x)
    {
        e->direction = -1;
    }
    else if (posPerso.x < e->pos.x + 500 && posPerso.x > (e->pos.x + e->img[e->anim_i][e->anim_j]->w))
    {
        e->direction = 1;
    }
    else if (posPerso.x > e->pos.x && posPerso.x < e->img[e->anim_i][e->anim_j]->w)
    {
        e->direction = 0;
    }
    else
    {
        if (e->pos.x >= e->posInit + 400)
            e->direction = -1;
        else if (e->pos.x <= e->posInit)
            e->direction = 1;
    }
}
int collisionBB(Ennemy e, Player p)
{
    SDL_Rect posE = e.pos;
    SDL_Rect posP = p.pos;
    if ((posP.x > posE.x && posP.x < posE.x + e.img[e.anim_i][e.anim_j]->w) || (posP.x + p.img[p.animI][p.animJ]->w > posE.x && posP.x + p.img[p.animI][p.animJ]->w < posE.x + e.img[e.anim_i][e.anim_j]->w))
    {
        return 1;
    }
    return 0;
}

int collisionEH(Ennemy e, SDL_Surface *Masque)
{
    SDL_Color color;

    int posX = e.posABS.x;
    int posY = e.posABS.y;
    int posX1 = posX + e.img[e.anim_i][e.anim_j]->w;
    int posY1 = posY + e.img[e.anim_i][e.anim_j]->h;

    for (int i = posY; i <= posY1 - 50; i++)
    {
        // Right
        color = GetPixel1(Masque, posX1, i);
        if (color.r == 255 && color.g == 255 && color.b == 1)
        {
            return 1;
        }
        // Left
        color = GetPixel1(Masque, posX, i);
        if (color.r == 255 && color.g == 255 && color.b == 1)
            return -1;
    }

    return 0;
}
int collisionEV(Ennemy e, SDL_Surface *Masque)
{
    SDL_Color color;

    int posX = e.posABS.x;
    int posY = e.posABS.y;
    int posX1 = posX + e.img[e.anim_i][e.anim_j]->w;
    int posY1 = posY + e.img[e.anim_i][e.anim_j]->h;

    for (int i = posX; i <= posX1; i++)
    {
        // TOP
        color = GetPixel1(Masque, i, posY);
        if (color.r == 255 && color.g == 255 && color.b == 1)
            return 2;
        // Bot
        color = GetPixel1(Masque, i, posY1);
        printf("R = %d G = %d B = %d\n", color.r, color.g, color.b);
        if (color.r == 255 && color.g == 255 && color.b == 1)
            return -2;
    }
}

void LibererEnnemy(Ennemy e)
{
    int n;

    for (int i = 0; i < 6; i++)
    {
        if (i == 0 || i == 1)
            n = 15;
        else if (i == 2 || i == 3)
            n = 10;
        else if (i == 4 || i == 5)
            n = 8;
        for (int j = 0; j < n; j++)
        {
            SDL_FreeSurface(e.img[i][j]);
        }
    }
}

SDL_Color GetPixel1(SDL_Surface *pSurface, int x, int y)
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