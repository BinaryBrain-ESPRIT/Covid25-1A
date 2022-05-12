#include "player.h"
#include "Background.h"
void initPerso(Player *p, int x, int y, int NumPlayer)
{
    int n;
    char NomImg[100];
    // Player Position on screen
    p->pos.x = x;
    p->pos.y = y;
    // Player Position on Map
    p->posABS.x = 250;
    p->posABS.y = y;
    p->nbreVie = 3;
    p->score = 0;
    // Vitesse
    p->v = 10;
    p->direction = 0;
    // Index I J Matrice
    p->animI = 0;
    p->animJ = 0;
    // Flipped Picture
    p->flipped = 0;

    p->AnimP_Idle = 0;
    p->AnimP_Attack = 0;
    p->AnimP_Run = 0;
    p->AnimP_Die = 0;
    p->attack = 0;
    p->NumPlayer = NumPlayer;
    p->isJumped = 0;
    for (int i = 0; i < 10; i++)
    {
        if (i == 0 || i == 1)
            n = 8;
        else if (i == 2 || i == 3)
            if (NumPlayer != 1)
                n = 6;
            else
                n = 7;
        else if (i == 4 || i == 5)
            n = 8;
        else if (i == 6 || i == 7)
            if (NumPlayer != 1)
                n = 9;
            else
                n = 6;
        else if ((i == 8 || i == 9))
            n = 6;

        for (int j = 0; j < n; j++)
        {
            /**
             * i = Animation Type
             * j = Animation Image
             **/
            sprintf(NomImg, "assets/Animation/Player%d/%d/%d.png", NumPlayer, i, j + 1); // selecting player Images
            p->img[i][j] = IMG_Load(NomImg);                                             // Loading Images
        }
    }
}

void afficherPerso(Player p, SDL_Surface *screen)
{
    printf("%d %d\n", p.animI, p.animJ);
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
    if (p->nbreVie > 0 && !p->attack)
    {
        switch (p->direction)
        {
        case 0:
            p->animJ = 0;
            if (!p->flipped)
                p->animI = 0;
            else
                p->animI = 1;
            break;
        case 1:
            if (p->AnimP_Run > 1)
            {
                p->animI = 2;
                if (p->NumPlayer != 1)
                    n = 5;
                else
                    n = 6;

                if (p->animJ >= n)
                    p->animJ = 0;
                else
                    p->animJ++;
                p->AnimP_Run = 0;
            }
            p->AnimP_Run++;
            break;
        case -1:
            if (p->AnimP_Run > 1)
            {
                p->animI = 3;

                if (p->NumPlayer != 1)
                    n = 5;
                else
                    n = 6;

                if (p->animJ >= n)
                    p->animJ = 0;
                else
                    p->animJ++;

                p->AnimP_Run = 0;
            }
            p->AnimP_Run++;
            break;
        }
    }
}
void saut(Player *p, SDL_Surface *Masque)
{
    int Vitesse = 20;
    int HeightP = p->posInit - 300;
    if (HeightP < 0)
        HeightP = 0;

    if (p->isJumped && p->pos.y > HeightP && !HighHeight(*p, Masque))
    {
        p->pos.y -= Vitesse;
        p->posABS.y -= Vitesse;
    }
    if (p->pos.y <= HeightP || HighHeight(*p, Masque))
    {
        p->isJumped = 0;
    }
    if (!isGround(*p, Masque) && !p->isJumped)
    {
        if (!Interaction(*p, Masque))
        {
            p->pos.y += Vitesse;
            p->posABS.y += Vitesse;
        }
    }
}

void LibererPlayer(Player p)
{
    int n;
    for (int i = 0; i < 10; i++)
    {
        if (i == 0 || i == 1)
            n = 8;
        else if (i == 2 || i == 3)
            if (p.NumPlayer != 1)
                n = 6;
            else
                n = 7;
        else if (i == 4 || i == 5)
            n = 8;
        else if (i == 6 || i == 7)
            if (p.NumPlayer != 1)
                n = 9;
            else
                n = 6;
        else if ((i == 8 || i == 9))
            n = 6;

        for (int j = 0; j < n; j++)
        {
            SDL_FreeSurface(p.img[i][j]);
        }
    }
}