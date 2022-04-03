#include "player.h"

void initPerso(Player *p, int NumPlayer)
{
    int n;
    char NomImg[100];
    p->pos.x = 250;
    p->pos.y = 510;
    p->posABS.x = p->pos.x;
    p->posABS.y = p->pos.y;
    p->nbreVie = 3;
    p->score = 0;
    p->v = 0.5;
    p->direction = 0;
    p->animI = 0;
    p->animJ = 0;
    p->flipped = 0;
    p->AnimP_Idle = 0;
    p->AnimP_Attack = 0;
    p->AnimP_Run = 0;
    p->AnimP_Die = 0;

    for (int i = 0; i < 6; i++)
    {
        if (i == 0 || i == 1)
            n = 7;
        else if (i == 2 || i == 3)
            n = 6;
        else if (i == 4 || i == 5)
            n = 9;

        for (int j = 0; j < n; j++)
        {
            sprintf(NomImg, "assets/Animation/Player1/%d/%d.png", i, j + 1);
            p->img[i][j] = IMG_Load(NomImg);
        }
    }
}

void afficherPerso(Player p, SDL_Surface *screen)
{
    SDL_BlitSurface(p.img[p.animI][p.animJ], NULL, screen, &p.pos);
}

void deplacerPerso(Player *p, int dt)
{

    switch (p->direction)
    {
    case 1:
        p->pos.x += p->v * dt;
        p->posABS.x += p->v * dt;

        break;
    case -1:
        p->pos.x -= p->v * dt;
        p->posABS.x -= p->v * dt;

        break;
    case 2:
        p->pos.y -= p->v * dt;
        p->posABS.y -= p->v * dt;

        break;
    case -2:
        p->pos.y += p->v * dt;
        p->posABS.y += p->v * dt;
        break;
    }
}
void animerPerso(Player *p)
{
    if (p->nbreVie > 0)
    {
        switch (p->direction)
        {
        case 0:
            if (p->AnimP_Idle % 10 == 0)
            {
                if (!p->flipped)
                    p->animI = 0;
                else
                    p->animI = 1;

                if (p->animJ >= 5)
                    p->animJ = 0;
                else
                    p->animJ++;
                p->AnimP_Idle = 0;
            }
            p->AnimP_Idle += 2;
            break;
        case 1:
            if (p->AnimP_Run % 10 == 0)
            {
                p->animI = 2;
                if (p->animJ >= 5)
                    p->animJ = 0;
                else
                    p->animJ++;
                p->AnimP_Run = 0;
            }
            p->AnimP_Run += 4;
            break;
        case -1:
            if (p->AnimP_Run % 10 == 0)
            {
                p->animI = 3;
                if (p->animJ >= 5)
                    p->animJ = 0;
                else
                    p->animJ++;

                p->AnimP_Run = 0;
            }
            p->AnimP_Run += 4;
            break;
        }
    }
}
void saut(Player *p)
{
}

void LibererPlayer(Player p)
{
    int n;
    for (int i = 0; i < 6; i++)
    {
        if (i == 0 || i == 1)
            n = 7;
        else if (i == 2 || i == 3)
            n = 6;
        else if (i == 4 || i == 5)
            n = 9;

        for (int j = 0; j < n; j++)
        {
            SDL_FreeSurface(p.img[i][j]);
        }
    }
}