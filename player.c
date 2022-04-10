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
    p->v = 10;
    p->direction = 0;
    p->animI = 0;
    p->animJ = 0;
    p->flipped = 0;
    p->AnimP_Idle = 0;
    p->AnimP_Attack = 0;
    p->AnimP_Run = 0;
    p->AnimP_Die = 0;
    p->NumPlayer = NumPlayer;
    p->isGround = 1;

    for (int i = 0; i < 8; i++)
    {

        if (i == 0 || i == 1)
            if (NumPlayer != 3)
                n = 7;
            else
                n = 1;
        else if (i == 2 || i == 3)
            if (NumPlayer != 3)
                n = 6;
            else
                n = 7;
        else if (i == 4 || i == 5)
            n = 8;
        else if (i == 6 || i == 7)
            if (NumPlayer != 3)
                n = 9;
            else
                n = 5;

        for (int j = 0; j < n; j++)
        {
            sprintf(NomImg, "assets/Animation/Player%d/%d/%d.png", NumPlayer, i, j + 1);
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
        p->pos.x += p->v;
        p->posABS.x += p->v;

        break;
    case -1:
        p->pos.x -= p->v;
        p->posABS.x -= p->v;

        break;
    case 2:
        p->pos.y -= p->v;
        p->posABS.y -= p->v;

        break;
    case -2:
        p->pos.y += p->v;
        p->posABS.y += p->v;
        break;
    }
}
void animerPerso(Player *p)
{
    int n = 0;
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

                if (p->NumPlayer != 3)
                    n = 5;
                else
                    n = 0;

                if (p->animJ >= n)
                    p->animJ = 0;
                else
                    p->animJ++;
                p->AnimP_Idle = 0;
            }
            p->AnimP_Idle += 2;

            break;
        case 1:
            if (p->AnimP_Run > 2)
            {
                p->animI = 2;
                if (p->NumPlayer != 3)
                    n = 5;
                else
                    n = 6;

                if (p->animJ >= n)
                    p->animJ = 0;
                else
                    p->animJ++;
                p->AnimP_Run = 0;
            }
            p->AnimP_Run ++ ;
            break;
        case -1:
            if (p->AnimP_Run > 2)
            {
                p->animI = 3;

                if (p->NumPlayer != 3)
                    n = 5;
                else
                    n = 6;

                if (p->animJ >= n)
                    p->animJ = 0;
                else
                    p->animJ++;

                p->AnimP_Run = 0;
            }
            p->AnimP_Run ++;
            break;
        }
    }
}
void saut(Player *p, int Collision)
{
    int Vitesse = 20;
    int HeightP = 0;
    //printf("Collision  = %d\n", Collision);
    if (!p->isGround && p->pos.y > HeightP)
    {
        p->pos.y -= Vitesse;
        p->posABS.y -= Vitesse;
        // SDL_Delay(10);
    }
    if (p->pos.y <= HeightP)
    {
        p->isGround = 1;
    }
    if (p->isGround && (Collision != -2))
    {
        p->pos.y += Vitesse;
        p->posABS.y += Vitesse;
    }
    /*if (p->isGround && p->pos.y > 510)
        p->pos.y = 510;*/
    // SDL_Delay(10);
}

void LibererPlayer(Player p)
{
    int n;
    for (int i = 0; i < 8; i++)
    {

        if (i == 0 || i == 1)
            if (p.NumPlayer != 3)
                n = 7;
            else
                n = 1;
        else if (i == 2 || i == 3)
            if (p.NumPlayer != 3)
                n = 6;
            else
                n = 7;
        else if (i == 4 || i == 5)
            n = 8;
        else if (i == 6 || i == 7)
            if (p.NumPlayer != 3)
                n = 9;
            else
                n = 5;
        for (int j = 0; j < n; j++)
        {
            SDL_FreeSurface(p.img[i][j]);
        }
    }
}