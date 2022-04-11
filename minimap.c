#include "minimap.h"
#include "Main_Fn.h"

void initminimap(minimap *m, char nameimg[], Player p, Ennemy e[])
{
    m->image = IMG_Load(nameimg);
    m->image1 = IMG_Load("assets/MiniMap/MinimapFrame.png");
    m->pos1.x = 0;
    m->pos1.y = 0;
    m->pos.x = 382;
    m->pos.y = 45;
    m->playerTag = IMG_Load("assets/MiniMap/PlayerTag.png");
    m->playerTagPos.x = ((p.pos.x * Redim) / 100) + m->pos.x;
    m->playerTagPos.y = ((p.pos.y * Redim) / 100) + m->pos.y;
    for (int i = 0; i < 5; i++)
    {
        m->zombieTag[i] = IMG_Load("assets/MiniMap/ZombieTag.png");
        m->zombieTagPos[i].x = ((e[i].pos.x * Redim) / 100) + m->pos.x;
        m->zombieTagPos[i].y = ((e[i].pos.y * Redim) / 100) + m->pos.y;
    }
}
void afficherminimap(minimap m, SDL_Surface *screen)
{
    SDL_BlitSurface(m.image1, NULL, screen, &m.pos1);
    SDL_BlitSurface(m.image, NULL, screen, &m.pos);

    SDL_BlitSurface(m.playerTag, NULL, screen, &m.playerTagPos);
    for (int i = 0; i < 5; i++)
    {
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

void MAJTime(Text *GameTimeTxt, int GameTimeInit)
{
    SDL_Color Red = {193, 39, 45};
    int GameTimeS, GameTimeM,GameTimeSPred;

    GameTimeS = ((SDL_GetTicks() - GameTimeInit) / 1000) % 60;
    GameTimeM = ((SDL_GetTicks() - GameTimeInit) / 1000) / 60;

    if (GameTimeSPred != GameTimeS)
    {
        sprintf(GameTimeTxt->Texte, "%02d:%02d", GameTimeM, GameTimeS);
        initTxt(GameTimeTxt, 1745, 154, Red, 35, "assets/Font/AznKnucklesTrial-z85pa.otf", GameTimeTxt->Texte);
    }

    GameTimeSPred = GameTimeS;
}

void Liberer(minimap *m)
{
    SDL_FreeSurface(m->image);
    SDL_FreeSurface(m->image1);
}