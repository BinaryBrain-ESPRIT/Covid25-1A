#include "ennemy.h"

void initEnnemy(Ennemy *e, int x, int y, int vitesse, int direction, int nbreVie)
{
    e->pos.x = x;
    e->pos.y = y;
    e->direction = direction;
    e->nbreVie = nbreVie;
    e->v = 0.2;
    e->anim_j = 0;
    e->anim_i = 0;
    e->posInit = x;
    e->attack = 0;
    e->AnimE_Attack = 0;
    e->AnimE_Run = 0;
    e->AnimeE_Idle = 0;
    // Run
    e->img[0][0] = IMG_Load("assets/Animation/Zombie1//idle/1.png");
    e->img[0][1] = IMG_Load("assets/Animation/Zombie1/idle/2.png");
    e->img[0][2] = IMG_Load("assets/Animation/Zombie1/idle/3.png");
    e->img[0][3] = IMG_Load("assets/Animation/Zombie1/idle/4.png");
    e->img[0][4] = IMG_Load("assets/Animation/Zombie1/idle/5.png");
    e->img[0][5] = IMG_Load("assets/Animation/Zombie1/idle/6.png");
    e->img[0][6] = IMG_Load("assets/Animation/Zombie1/idle/7.png");
    e->img[0][7] = IMG_Load("assets/Animation/Zombie1/idle/8.png");
    e->img[0][8] = IMG_Load("assets/Animation/Zombie1/idle/9.png");
    e->img[0][9] = IMG_Load("assets/Animation/Zombie1/idle/10.png");
    e->img[0][10] = IMG_Load("assets/Animation/Zombie1/idle/11.png");
    e->img[0][11] = IMG_Load("assets/Animation/Zombie1/idle/12.png");
    e->img[0][12] = IMG_Load("assets/Animation/Zombie1/idle/13.png");
    e->img[0][13] = IMG_Load("assets/Animation/Zombie1/idle/14.png");
    e->img[0][14] = IMG_Load("assets/Animation/Zombie1/idle/15.png");
    /*
    e->img[1][0] = IMG_Load("assets/Animation/Zombie1//idle flipped/1.png");
    e->img[1][1] = IMG_Load("assets/Animation/Zombie1/idle flipped/2.png");
    e->img[1][2] = IMG_Load("assets/Animation/Zombie1/idle flipped/3.png");
    e->img[1][3] = IMG_Load("assets/Animation/Zombie1/idle flipped/4.png");
    e->img[1][4] = IMG_Load("assets/Animation/Zombie1/idle flipped/5.png");
    e->img[1][5] = IMG_Load("assets/Animation/Zombie1/idle flipped/6.png");
    e->img[1][6] = IMG_Load("assets/Animation/Zombie1/idle flipped/7.png");
    e->img[1][7] = IMG_Load("assets/Animation/Zombie1/idle flipped/8.png");
    e->img[1][8] = IMG_Load("assets/Animation/Zombie1/idle flipped/9.png");
    e->img[1][9] = IMG_Load("assets/Animation/Zombie1/idle flipped/10.png");
    e->img[1][10] = IMG_Load("assets/Animation/Zombie1/idle flipped/11.png");
    e->img[1][11] = IMG_Load("assets/Animation/Zombie1/idle flipped/12.png");
    e->img[1][12] = IMG_Load("assets/Animation/Zombie1/idle flipped/13.png");
    e->img[1][13] = IMG_Load("assets/Animation/Zombie1/idle flipped/14.png");
    e->img[1][14] = IMG_Load("assets/Animation/Zombie1/idle flipped/15.png");
    */
    e->img[2][0] = IMG_Load("assets/Animation/Zombie1/run/1.png");
    e->img[2][1] = IMG_Load("assets/Animation/Zombie1/run/2.png");
    e->img[2][2] = IMG_Load("assets/Animation/Zombie1/run/3.png");
    e->img[2][3] = IMG_Load("assets/Animation/Zombie1/run/4.png");
    e->img[2][4] = IMG_Load("assets/Animation/Zombie1/run/5.png");
    e->img[2][5] = IMG_Load("assets/Animation/Zombie1/run/6.png");
    e->img[2][6] = IMG_Load("assets/Animation/Zombie1/run/7.png");
    e->img[2][7] = IMG_Load("assets/Animation/Zombie1/run/8.png");
    e->img[2][8] = IMG_Load("assets/Animation/Zombie1/run/9.png");
    e->img[2][9] = IMG_Load("assets/Animation/Zombie1/run/10.png");

    e->img[3][0] = IMG_Load("assets/Animation/Zombie1/run flipped/1.png");
    e->img[3][1] = IMG_Load("assets/Animation/Zombie1/run flipped/2.png");
    e->img[3][2] = IMG_Load("assets/Animation/Zombie1/run flipped/3.png");
    e->img[3][3] = IMG_Load("assets/Animation/Zombie1/run flipped/4.png");
    e->img[3][4] = IMG_Load("assets/Animation/Zombie1/run flipped/5.png");
    e->img[3][5] = IMG_Load("assets/Animation/Zombie1/run flipped/6.png");
    e->img[3][6] = IMG_Load("assets/Animation/Zombie1/run flipped/7.png");
    e->img[3][7] = IMG_Load("assets/Animation/Zombie1/run flipped/8.png");
    e->img[3][8] = IMG_Load("assets/Animation/Zombie1/run flipped/9.png");
    e->img[3][9] = IMG_Load("assets/Animation/Zombie1/run flipped/10.png");

    e->img[4][0] = IMG_Load("assets/Animation/Zombie1/attack/1.png");
    e->img[4][1] = IMG_Load("assets/Animation/Zombie1/attack/2.png");
    e->img[4][2] = IMG_Load("assets/Animation/Zombie1/attack/3.png");
    e->img[4][3] = IMG_Load("assets/Animation/Zombie1/attack/4.png");
    e->img[4][4] = IMG_Load("assets/Animation/Zombie1/attack/5.png");
    e->img[4][5] = IMG_Load("assets/Animation/Zombie1/attack/6.png");
    e->img[4][6] = IMG_Load("assets/Animation/Zombie1/attack/7.png");
    e->img[4][7] = IMG_Load("assets/Animation/Zombie1/attack/8.png");
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
            e->anim_i = 4;
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
                if (e->anim_j >= 6)
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
                if (e->anim_j >= 5)
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
                if (e->anim_j >= 5)
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
        e->pos.x += e->v * 20;
    else if (e->direction == -1)
        e->pos.x -= e->v * 20;
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

    if ((posP.x > posE.x && posP.x < posE.x + e.img[e.anim_i][e.anim_j]->w) || (posP.x + p.img[p.animI][p.animJ]->w > posE.x && posP.x + p.img[p.animI][p.animJ]->w < posE.x + e.img[e.anim_i][e.anim_j]->w) )
    {
        return 1;
    }
    return 0;
}