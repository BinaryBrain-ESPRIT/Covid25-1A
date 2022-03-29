#include "player.h"

void initPerso(Player *p, int NumPlayer)
{
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
    if (NumPlayer == 0)
    {
        p->img[0][0] = IMG_Load("assets/Animation/Player1/idle/1.png");
        p->img[0][1] = IMG_Load("assets/Animation/Player1/idle/2.png");
        p->img[0][2] = IMG_Load("assets/Animation/Player1/idle/3.png");
        p->img[0][3] = IMG_Load("assets/Animation/Player1/idle/4.png");
        p->img[0][4] = IMG_Load("assets/Animation/Player1/idle/5.png");
        p->img[0][5] = IMG_Load("assets/Animation/Player1/idle/6.png");
        p->img[0][6] = IMG_Load("assets/Animation/Player1/idle/7.png");

        p->img[1][0] = IMG_Load("assets/Animation/Player1/idle flipped/1.png");
        p->img[1][1] = IMG_Load("assets/Animation/Player1/idle flipped/2.png");
        p->img[1][2] = IMG_Load("assets/Animation/Player1/idle flipped/3.png");
        p->img[1][3] = IMG_Load("assets/Animation/Player1/idle flipped/4.png");
        p->img[1][4] = IMG_Load("assets/Animation/Player1/idle flipped/5.png");
        p->img[1][5] = IMG_Load("assets/Animation/Player1/idle flipped/6.png");
        p->img[1][6] = IMG_Load("assets/Animation/Player1/idle flipped/7.png");

        p->img[2][0] = IMG_Load("assets/Animation/Player1/run/1.png");
        p->img[2][1] = IMG_Load("assets/Animation/Player1/run/2.png");
        p->img[2][2] = IMG_Load("assets/Animation/Player1/run/3.png");
        p->img[2][3] = IMG_Load("assets/Animation/Player1/run/4.png");
        p->img[2][4] = IMG_Load("assets/Animation/Player1/run/5.png");
        p->img[2][5] = IMG_Load("assets/Animation/Player1/run/6.png");

        p->img[3][0] = IMG_Load("assets/Animation/Player1/run flipped/1.png");
        p->img[3][1] = IMG_Load("assets/Animation/Player1/run flipped/2.png");
        p->img[3][2] = IMG_Load("assets/Animation/Player1/run flipped/3.png");
        p->img[3][3] = IMG_Load("assets/Animation/Player1/run flipped/4.png");
        p->img[3][4] = IMG_Load("assets/Animation/Player1/run flipped/5.png");
        p->img[3][5] = IMG_Load("assets/Animation/Player1/run flipped/6.png");
    }
    else if (NumPlayer == 1)
    {
        p->img[0][0] = IMG_Load("assets/Animation/Player2/idle/1.png");
        p->img[0][1] = IMG_Load("assets/Animation/Player2/idle/2.png");
        p->img[0][2] = IMG_Load("assets/Animation/Player2/idle/3.png");
        p->img[0][3] = IMG_Load("assets/Animation/Player2/idle/4.png");
        p->img[0][4] = IMG_Load("assets/Animation/Player2/idle/5.png");
        p->img[0][5] = IMG_Load("assets/Animation/Player2/idle/6.png");
        p->img[0][6] = IMG_Load("assets/Animation/Player2/idle/7.png");

        p->img[1][0] = IMG_Load("assets/Animation/Player2/idle flipped/1.png");
        p->img[1][1] = IMG_Load("assets/Animation/Player2/idle flipped/2.png");
        p->img[1][2] = IMG_Load("assets/Animation/Player2/idle flipped/3.png");
        p->img[1][3] = IMG_Load("assets/Animation/Player2/idle flipped/4.png");
        p->img[1][4] = IMG_Load("assets/Animation/Player2/idle flipped/5.png");
        p->img[1][5] = IMG_Load("assets/Animation/Player2/idle flipped/6.png");
        p->img[1][6] = IMG_Load("assets/Animation/Player2/idle flipped/7.png");

        p->img[2][0] = IMG_Load("assets/Animation/Player2/run/1.png");
        p->img[2][1] = IMG_Load("assets/Animation/Player2/run/2.png");
        p->img[2][2] = IMG_Load("assets/Animation/Player2/run/3.png");
        p->img[2][3] = IMG_Load("assets/Animation/Player2/run/4.png");
        p->img[2][4] = IMG_Load("assets/Animation/Player2/run/5.png");
        p->img[2][5] = IMG_Load("assets/Animation/Player2/run/6.png");

        p->img[3][0] = IMG_Load("assets/Animation/Player2/run flipped/1.png");
        p->img[3][1] = IMG_Load("assets/Animation/Player2/run flipped/2.png");
        p->img[3][2] = IMG_Load("assets/Animation/Player2/run flipped/3.png");
        p->img[3][3] = IMG_Load("assets/Animation/Player2/run flipped/4.png");
        p->img[3][4] = IMG_Load("assets/Animation/Player2/run flipped/5.png");
        p->img[3][5] = IMG_Load("assets/Animation/Player2/run flipped/6.png");
    }
    else if (NumPlayer == 2)
    {
        p->img[0][0] = IMG_Load("assets/Animation/Player3/idle/1.png");
        p->img[0][1] = IMG_Load("assets/Animation/Player3/idle/2.png");
        p->img[0][2] = IMG_Load("assets/Animation/Player3/idle/3.png");
        p->img[0][3] = IMG_Load("assets/Animation/Player3/idle/4.png");
        p->img[0][4] = IMG_Load("assets/Animation/Player3/idle/5.png");
        p->img[0][5] = IMG_Load("assets/Animation/Player3/idle/6.png");
        p->img[0][6] = IMG_Load("assets/Animation/Player3/idle/7.png");

        p->img[1][0] = IMG_Load("assets/Animation/Player3/idle flipped/1.png");
        p->img[1][1] = IMG_Load("assets/Animation/Player3/idle flipped/2.png");
        p->img[1][2] = IMG_Load("assets/Animation/Player3/idle flipped/3.png");
        p->img[1][3] = IMG_Load("assets/Animation/Player3/idle flipped/4.png");
        p->img[1][4] = IMG_Load("assets/Animation/Player3/idle flipped/5.png");
        p->img[1][5] = IMG_Load("assets/Animation/Player3/idle flipped/6.png");
        p->img[1][6] = IMG_Load("assets/Animation/Player3/idle flipped/7.png");

        p->img[2][0] = IMG_Load("assets/Animation/Player3/run/1.png");
        p->img[2][1] = IMG_Load("assets/Animation/Player3/run/2.png");
        p->img[2][2] = IMG_Load("assets/Animation/Player3/run/3.png");
        p->img[2][3] = IMG_Load("assets/Animation/Player3/run/4.png");
        p->img[2][4] = IMG_Load("assets/Animation/Player3/run/5.png");
        p->img[2][5] = IMG_Load("assets/Animation/Player3/run/6.png");

        p->img[3][0] = IMG_Load("assets/Animation/Player3/run flipped/1.png");
        p->img[3][1] = IMG_Load("assets/Animation/Player3/run flipped/2.png");
        p->img[3][2] = IMG_Load("assets/Animation/Player3/run flipped/3.png");
        p->img[3][3] = IMG_Load("assets/Animation/Player3/run flipped/4.png");
        p->img[3][4] = IMG_Load("assets/Animation/Player3/run flipped/5.png");
        p->img[3][5] = IMG_Load("assets/Animation/Player3/run flipped/6.png");
    }
}
void afficherPerso(Player p, SDL_Surface *screen)
{
    SDL_BlitSurface(p.img[p.animI][p.animJ], NULL, screen, &p.pos);
}
void deplacerPerso(Player *p, int dt)
{

    if (p->direction == 1)
    {
        p->pos.x += p->v * dt;
        p->posABS.x += p->v * dt;
    }
    else if (p->direction == -1 && p->pos.x >0)
    {
        p->pos.x -= p->v * dt;
        p->posABS.x -= p->v * dt;
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

            if (p->animJ >= 6)
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