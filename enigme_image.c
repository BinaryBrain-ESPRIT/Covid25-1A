#include "enigme_image.h"
#include <time.h>

void InitEnigme(Enigme *e, char *nomfichier)
{
    FILE *f;
    srand(time(NULL));
    int l, c;
    int a = 1;
    Card tab[6];
    char NomBackg[100];
    char HideImg[100];

    int indice = 0;
    f = fopen(nomfichier, "r");
    fscanf(f, "%s %s %s %s %s", NomBackg, tab[0].NomIMG, tab[2].NomIMG, tab[4].NomIMG, HideImg);

    for (int i = 0; i < 6; i += 2)
    {
        tab[i].type = a;
        tab[i + 1].type = a;
        a++;
        strcpy(tab[i + 1].NomIMG, tab[i].NomIMG);
    }

    e->tabC[0][0].pos.x = 153;
    e->tabC[0][0].pos.y = 30;
    e->tabC[0][1].pos.x = 809;
    e->tabC[0][1].pos.y = 30;
    e->tabC[0][2].pos.x = 1465;
    e->tabC[0][2].pos.y = 30;
    e->tabC[1][0].pos.x = 153;
    e->tabC[1][0].pos.y = 640;
    e->tabC[1][1].pos.x = 809;
    e->tabC[1][1].pos.y = 640;
    e->tabC[1][2].pos.x = 1465;
    e->tabC[1][2].pos.y = 640;

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            do
                indice = rand() % (5 - 0 + 1);
            while (strlen(tab[indice].NomIMG) <= 0);
            // printf("%zu\n",strlen(tab[indice].NomIMG));
            strcpy(e->tabC[i][j].NomIMG, tab[indice].NomIMG);
            e->tabC[i][j].type = tab[indice].type;
            strcpy(tab[indice].NomIMG, "");
        }
    }

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
        {
            e->tabC[i][j].img = IMG_Load(e->tabC[i][j].NomIMG);
            e->tabC[i][j].hide = IMG_Load(HideImg);
            e->tabC[i][j].done = 0;
            e->tabC[i][j].Turned = 0;
        }

    // Init Backg
    e->Backg[0].img = IMG_Load(NomBackg);
    e->Backg[0].pos.x = 0;
    e->Backg[0].pos.y = 0;

    fclose(f);
}
void afficherEnigme(Enigme e, SDL_Surface *screen)
{
    SDL_BlitSurface(e.Backg[0].img, NULL, screen, &e.Backg[0].pos);

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
        {
            if (!e.tabC[i][j].done)
            {
                SDL_BlitSurface(e.tabC[i][j].hide, NULL, screen, &e.tabC[i][j].pos);
                e.tabC[i][j].Turned = 0;
            }
            else
                SDL_BlitSurface(e.tabC[i][j].img, NULL, screen, &e.tabC[i][j].pos);
        }
}

int Verifier(Enigme e, int l, int c)
{
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            printf("%d\n", e.tabC[i][j].Turned);
    printf("l = %d\nc = %d\n", l, c);
    int a = 0;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // printf("i= %d\nj= %d\nl = %d\n","c = %d\n",i,j,l,c);
            if (e.tabC[i][j].Turned == 1)
            {
                printf("FOund\n");
                if (e.tabC[i][j].type == e.tabC[l][c].type)
                {
                    e.tabC[i][j].done = 1;
                    e.tabC[l][c].done = 1;
                    return 1;
                }
            }
            else
            {
                printf("Not Found\n");
                return 0;
            }
        }
    }
    return -1;
}

void animer(Enigme *e, SDL_Surface *screen)
{
    int x, y;
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        x = event.button.x;
        y = event.button.y;
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (x > e->tabC[i][j].pos.x && x < e->tabC[i][j].pos.x + e->tabC[i][j].img->w && y > e->tabC[i][j].pos.y && y < e->tabC[i][j].pos.y + e->tabC[i][j].img->h)
                {

                    SDL_BlitSurface(e->tabC[i][j].img, NULL, screen, &e->tabC[i][j].pos);

                    e->tabC[i][j].Turned = 1;
                    for (int i = 0; i < 2; i++)
                        for (int j = 0; j < 3; j++)
                            printf("%d\n", e->tabC[i][j].Turned);
                    Verifier(*e, i, j);
                    // afficherEnigme(*e,screen);

                    // printf("%d\n", Verifier(*e, i, j));
                    SDL_Flip(screen);
                }
            }
        }
    }
}
void Free_Enigme(Enigme *e);