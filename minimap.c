#include "minimap.h"
#include "Main_Fn.h"

void initminimap(minimap *m, char nameimg[], Player p, Ennemy e[])
{
    m->image = IMG_Load(nameimg);
    m->pos.x = Width / 2 - (m->image->w / 2);
    m->pos.y = 50;
    m->playerTag = IMG_Load("assets/Levels/Backg/minimaptagPlayer1.png");
    m->playerTagPos.x = ((p.pos.x * Redim) / 100) + m->pos.x;
    m->playerTagPos.y = ((p.pos.y * Redim) / 100) + m->pos.y;
    for (int i = 0; i < 5; i++)
    {

        m->zombieTag[i] = IMG_Load("assets/Levels/Backg/minimaptagPlayer1.png");
        m->zombieTagPos[i].x = ((e[i].pos.x * Redim) / 100) + m->pos.x;
        m->zombieTagPos[i].y = ((e[i].pos.y * Redim) / 100) + m->pos.y;

        //printf("x = %d\ny = %d\n", m->zombieTagPos[i].x, m->zombieTagPos[i].y);
    }
}
void afficherminimap(minimap m, SDL_Surface *screen)
{
    SDL_BlitSurface(m.image, NULL, screen, &m.pos);
    SDL_BlitSurface(m.playerTag, NULL, screen, &m.playerTagPos);
    for (int i = 0; i < 5; i++)
    {
        printf("x = %d\ny = %d\n", m.zombieTagPos[i].x, m.zombieTagPos[i].y);
        SDL_BlitSurface(m.zombieTag[i], NULL, screen, &m.zombieTagPos[i]);
    }
}
void MAJMinimap(SDL_Rect PosJoueur, Ennemy e[], minimap *m, int redimensionnement)
{
    m->playerTagPos.x = m->pos.x + ((PosJoueur.x * redimensionnement) / 100);
    m->playerTagPos.y = m->pos.y + ((PosJoueur.y * redimensionnement) / 100);
    for (int i = 0; i < 5; i++)
    {
        m->zombieTagPos[i].x = m->pos.x + ((e[i].posABS.x * redimensionnement) / 100);
        m->zombieTagPos[i].y = m->pos.y + ((e[i].posABS.y * redimensionnement) / 100);
    }
}