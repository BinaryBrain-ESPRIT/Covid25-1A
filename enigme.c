#include "enigme.h"

void InitEnigme1(enigme *e, char *nomfichier)
{
  // Declaration
  SDL_Color black = {0, 0, 0};
  char NomBackg[100];
  char NomTimer[100];
  char ImgTimer[100];
  // Fichier
  e->f = fopen(nomfichier, "r");

  fscanf(e->f, "%d %s %d", &e->NumE, NomBackg, &e->NumRepC);

  // Init Backg
  InitBackg(&e->Backg[0], NomBackg);

  // Init Couleurs
  e->Quest.color = black;
  for (int i = 0; i < 3; i++)
    e->Rep[i].color = black;

  // InitTexte
  strcpy(e->Quest.Texte, "Question ?"); 
  strcpy(e->Rep[0].Texte, "1- Rep");
  strcpy(e->Rep[1].Texte, "2- Rep");
  strcpy(e->Rep[2].Texte, "3- Rep");

  // Init Pos
  e->Quest.pos.x = 549;
  e->Quest.pos.y = 95;

  e->Rep[0].pos.x = 261;
  e->Rep[0].pos.y = 409;

  e->Rep[1].pos.x = 1340;
  e->Rep[1].pos.y = 409;

  e->Rep[2].pos.x = 775;
  e->Rep[2].pos.y = 661;

  // InitFont
  e->Quest.font = TTF_OpenFont("assets/Font/ChopinScript.ttf", 225);
  e->Rep[0].font = TTF_OpenFont("assets/Font/ChopinScript.ttf", 120);
  e->Rep[1].font = TTF_OpenFont("assets/Font/ChopinScript.ttf", 120);
  e->Rep[2].font = TTF_OpenFont("assets/Font/ChopinScript.ttf", 120);

  // RenderText
  e->Quest.surfaceText = TTF_RenderText_Solid(e->Quest.font, e->Quest.Texte, e->Quest.color);
  e->Rep[0].surfaceText = TTF_RenderText_Solid(e->Rep[0].font, e->Rep[0].Texte, e->Rep[0].color);
  e->Rep[1].surfaceText = TTF_RenderText_Solid(e->Rep[1].font, e->Rep[1].Texte, e->Rep[1].color);
  e->Rep[2].surfaceText = TTF_RenderText_Solid(e->Rep[2].font, e->Rep[2].Texte, e->Rep[2].color);

  for (int i = 0; i < 11; i++)
  {
    strcpy(NomTimer, "assets/enigmeText/Timer/");
    sprintf(ImgTimer, "%d.jpg", i);
    strcat(NomTimer, ImgTimer);
    initImg(&e->Timer[i], 1673, 32, NomTimer);
  }
  e->TimerI = 0;
}

void afficherEnigme1(enigme e, SDL_Surface *screen)
{
  SDL_BlitSurface(e.Backg[0].img, NULL, screen, &e.Backg[0].pos);
  SDL_BlitSurface(e.Quest.surfaceText, NULL, screen, &e.Quest.pos);
  SDL_BlitSurface(e.Rep[0].surfaceText, NULL, screen, &e.Rep[0].pos);
  SDL_BlitSurface(e.Rep[1].surfaceText, NULL, screen, &e.Rep[1].pos);
  SDL_BlitSurface(e.Rep[2].surfaceText, NULL, screen, &e.Rep[2].pos);
}
void animer1(enigme *e, SDL_Surface *screen)
{
  AfficherImg(e->Timer[10 - e->TimerI], screen);
  e->TimerI++;
}