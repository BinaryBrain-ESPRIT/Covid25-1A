#include "player.h"

void initPerso(Player *p, int NumPlayer)
{
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
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            sprintf(NomImg, "assets/Animation/Player%d/%d/%d.png", NumPlayer + 1, i, j + 1);
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
        if (p->posABS.x < 9390 && !(p->posABS.y > 530 && p->posABS.y < 1310))
        {
            p->pos.x += p->v * dt;
            p->posABS.x += p->v * dt;
        }
        break;
    case -1:
        if (p->posABS.x > 0 && !(p->posABS.y > 530 && p->posABS.y < 1310))
        {
            p->pos.x -= p->v * dt;
            p->posABS.x -= p->v * dt;
        }
        break;
    case 2:
        if (p->posABS.x > 6800 && p->posABS.x < 6850 && p->posABS.y > 510)
        {
            p->pos.y -= p->v * dt;
            p->posABS.y -= p->v * dt;
        }
        break;
    case -2:
        p->pos.y += p->v * dt;
        p->posABS.y += p->v * dt;
        break;
    }
}
void animerPerso(Player *p)
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
void saut(Player *p)
{
}