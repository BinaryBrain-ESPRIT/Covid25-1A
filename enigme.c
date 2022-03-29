#include "enigme.h"

void initEnigme(enigme *e, char *nomfichier)
{
  // Declaration
  SDL_Color red = {255, 0, 0};
  SDL_Color white = {0, 0, 0};

  // Fichier
  e->f = fopen("enigme.txt", "r");

  // Init Backg
  initImg(&e->Backg, 200, 100, "assets/enigme/Background.jpg");

  // Init Couleurs
  e->Quest.color = red;
  for (int i = 0; i < 3; i++)
    e->Rep[i].color = white;

  // InitTexte
  strcpy(e->Quest.Texte, "");
  strcpy(e->Rep[0].Texte, "");
  strcpy(e->Rep[1].Texte, "");
  strcpy(e->Rep[2].Texte, "");

  // Init Pos
  e->Quest.pos.x = 240;
  e->Quest.pos.x = 130;

  e->Rep[0].pos.x = 400;
  e->Rep[0].pos.y = 200;

  e->Rep[1].pos.x = 550;
  e->Rep[1].pos.y = 200;

  e->Rep[2].pos.x = 700;
  e->Rep[2].pos.y = 200;

  // InitFont
  e->Quest.font = TTF_OpenFont("assets/Font/Bebas-Regular.ttf", 24);
  e->Rep[0].font = TTF_OpenFont("assets/Font/Bebas-Regular.ttf", 24);
  e->Rep[1].font = TTF_OpenFont("assets/Font/Bebas-Regular.ttf", 24);
  e->Rep[2].font = TTF_OpenFont("assets/Font/Bebas-Regular.ttf", 24);

  //RenderText
  e->Quest.surfaceText = TTF_RenderText_Solid(e->Quest.font, e->Quest.Texte, e->Quest.color);
  e->Rep[0].surfaceText = TTF_RenderText_Solid(e->Rep[0].font, e->Rep[0].Texte, e->Rep[0].color);
  e->Rep[1].surfaceText = TTF_RenderText_Solid(e->Rep[1].font, e->Rep[1].Texte, e->Rep[1].color);
  e->Rep[2].surfaceText = TTF_RenderText_Solid(e->Rep[2].font, e->Rep[2].Texte, e->Rep[2].color);
}

void afficherEnigme(enigme e, SDL_Surface *screen)
{
  SDL_BlitSurface(e.Quest.surfaceText,NULL,screen,&e.Quest.pos);
  SDL_BlitSurface(e.Rep[0].surfaceText,NULL,screen,&e.Rep[0].pos);
  SDL_BlitSurface(e.Rep[1].surfaceText,NULL,screen,&e.Rep[1].pos);
  SDL_BlitSurface(e.Rep[2].surfaceText,NULL,screen,&e.Rep[2].pos);
}