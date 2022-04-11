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
    int GameTimeS, GameTimeM, GameTimeSPred;

    GameTimeS = ((SDL_GetTicks() - GameTimeInit) / 1000) % 60;
    GameTimeM = ((SDL_GetTicks() - GameTimeInit) / 1000) / 60;

    if (GameTimeSPred != GameTimeS)
    {
        sprintf(GameTimeTxt->Texte, "%02d:%02d", GameTimeM, GameTimeS);
        initTxt(GameTimeTxt, 1745, 154, Red, 35, "assets/Font/AznKnucklesTrial-z85pa.otf", GameTimeTxt->Texte);
    }

    GameTimeSPred = GameTimeS;
}

void SaveScore(int score, char nomjoueur[], char nomfichier[])
{
}

void LeaderBoard(SDL_Surface *screen, Config *Confg)
{
    Image Backg;
    FILE *f = fopen("Data/Score.txt", "r");
    Score tabS[6];
    SDL_Color Blue = {16, 16, 73};
    SDL_Color Gold = {214, 165, 101};
    SDL_Color Red = {193, 39, 45};
    SDL_Rect tabPos[6];
    SDL_Event event;

    int n = 0;
    int Done = 0;

    tabPos[0].x = 754;
    tabPos[0].y = 271;
    tabPos[1].x = 754;
    tabPos[1].y = 394;
    tabPos[2].x = 754;
    tabPos[2].y = 517;
    tabPos[3].x = 754;
    tabPos[3].y = 640;
    tabPos[4].x = 754;
    tabPos[4].y = 763;
    tabPos[5].x = 754;
    tabPos[5].y = 887;

    InitBackg(&Backg, "assets/LeaderBoard/Background.jpg");
    AfficherImg(Backg, screen);

    while (fscanf(f, "%s %s %d", tabS[n].PlayerName.Texte, tabS[n].Time.Texte, &tabS[n].Score) != EOF)
        n++;

    int permut;
    Score temp;
    do
    {
        permut = 0;
        for (int i = 0; i < n - 1; i++)
        {
            if (tabS[i].Score < tabS[i + 1].Score)
            {
                temp = tabS[i];
                tabS[i] = tabS[i + 1];
                tabS[i + 1] = temp;
                permut = 1;
            }
        }
    } while (permut);

    for (int i = 0; i < n; i++)
        printf("PlayerName: %s Time: %s Score: %d\n", tabS[i].PlayerName.Texte, tabS[i].Time.Texte, tabS[i].Score);

    for (int i = 0; i < n; i++)
    {
        initTxt(&tabS[i].PlayerName, tabPos[i].x, tabPos[i].y, Blue, 29, "assets/Font/Montserrat-Bold.ttf", tabS[i].PlayerName.Texte);
        initTxt(&tabS[i].Time, tabPos[i].x + 277, tabPos[i].y, Gold, 29, "assets/Font/Montserrat-Bold.ttf", tabS[i].Time.Texte);
        sprintf(tabS[i].ScoreTxt.Texte, "%d", tabS[i].Score);
        initTxt(&tabS[i].ScoreTxt, tabPos[i].x + 489, tabPos[i].y, Red, 29, "assets/Font/Montserrat-Bold.ttf", tabS[i].ScoreTxt.Texte);
        Afficher_txt(tabS[i].PlayerName, screen);
        Afficher_txt(tabS[i].Time, screen);
        Afficher_txt(tabS[i].ScoreTxt, screen);
    }
    SDL_Flip(screen);

    while (!Done)
    {
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            Done = 1;
            Confg->isRunning = 0;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                Done = 1;
            break;
        }
    }

    SDL_FreeSurface(Backg.img);
    for (int i = 0; i < n; i++)
    {
        SDL_FreeSurface(tabS[i].PlayerName.surfaceText);
        SDL_FreeSurface(tabS[i].Time.surfaceText);
        SDL_FreeSurface(tabS[i].ScoreTxt.surfaceText);
    }

    fclose(f);
}

void Liberer(minimap *m)
{
    SDL_FreeSurface(m->image);
    SDL_FreeSurface(m->image1);
}