#include "minimap.h"
#include "Main_Fn.h"
void initminimap(minimap *m, char nameimg[],Player p)
{
    m->image = IMG_Load(nameimg);
    m->pos.x = Width/2 - (m->image->w / 2);
    m->pos.y = 50;
    m->playerTag = IMG_Load("assets/Levels/Backg/minimaptagPlayer1.png");
    m->playerTagPos.x = ((p.pos.x * Redim) / 100) + m->pos.x;
    m->playerTagPos.y = ((p.pos.y * Redim) / 100) + m->pos.y;
}

void afficherminimap(minimap m, SDL_Surface *screen)
{
    SDL_BlitSurface(m.image,NULL,screen,&m.pos);
    SDL_BlitSurface(m.playerTag,NULL,screen,&m.playerTagPos);
}
