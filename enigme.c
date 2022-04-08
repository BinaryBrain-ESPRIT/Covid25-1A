#include "enigme.h"
int InitEnigme1(enigme *e, char *nomfichier)
{
  // Declaration
  SDL_Color black = {0, 0, 0};
  char NomBackg[30];
  char NomTimer[35];
  char Quest[100];
  char Quest1[100];
  char Rep1[100];
  char Rep2[100];
  char Rep3[100];
  int posX, posX1;
  int NumE;
  int NumE1;
  enigme e1;
  int End;
  int n = 0;
  FILE *f1 = fopen("SelectedEnigme.txt", "r");
  do
  {
    End = fscanf(f1, "%d\n", &NumE1) != EOF;
    n++;
  } while (End != 0);
  fclose(f1);
  f1 = fopen("SelectedEnigme.txt", "r");
  do
  {
    NumE = rand() % (4 - 1) + 1;
    do
    {
      End = fscanf(f1, "%d\n", &NumE1) != EOF;
    } while (NumE != NumE1 && End != 0);

  } while (NumE1 == NumE && n < 3);


  if (n >= 3 && NumE1 == NumE)
    return 0;

  fclose(f1);

  f1 = fopen("SelectedEnigme.txt", "a");

  fprintf(f1, "%d\n", NumE);
  /*
    do
    {
      NumE = rand() % (4 - 1) + 1;
      while (fread(&e1, sizeof(enigme), 1, f1) != EOF && NumE != e1.NumE)
        ;
    } while (e1.NumE == NumE);
  */
  // Fichier
  e->f = fopen(nomfichier, "r");
  do
    fscanf(e->f, "%d %s %d %d %s %s %s %s %s %d", &e->NumE, NomBackg, &posX, &posX1, Quest, Quest1, Rep1, Rep2, Rep3, &e->NumRepC);
  while (e->NumE != NumE);
  for (int i = 0; i < strlen(Quest); i++)
  {
    if (Quest[i] == '_')
      Quest[i] = ' ';
  }
  for (int i = 0; i < strlen(Quest1); i++)
  {
    if (Quest1[i] == '_')
      Quest1[i] = ' ';
  }

  // Init Backg
  InitBackg(&e->Backg[0], NomBackg);

  // Init Couleurs
  e->Quest.color = black;
  e->Quest1.color = black;
  for (int i = 0; i < 3; i++)
    e->Rep[i].color = black;

  // InitTexte
  strcpy(e->Quest.Texte, Quest);
  strcpy(e->Quest1.Texte, Quest1);
  strcpy(e->Rep[0].Texte, Rep1);
  strcpy(e->Rep[1].Texte, Rep2);
  strcpy(e->Rep[2].Texte, Rep3);

  // Init Pos
  e->Quest.pos.x = posX;
  e->Quest.pos.y = 133;

  e->Quest1.pos.x = posX1;
  e->Quest1.pos.y = 248;

  e->Rep[0].pos.x = 261;
  e->Rep[0].pos.y = 409;

  e->Rep[1].pos.x = 1340;
  e->Rep[1].pos.y = 409;

  e->Rep[2].pos.x = 775;
  e->Rep[2].pos.y = 661;

  // InitFont
  e->Quest.font = TTF_OpenFont("assets/Font/ChopinScript.ttf", 100);
  e->Quest1.font = TTF_OpenFont("assets/Font/ChopinScript.ttf", 100);
  e->Rep[0].font = TTF_OpenFont("assets/Font/ChopinScript.ttf", 120);
  e->Rep[1].font = TTF_OpenFont("assets/Font/ChopinScript.ttf", 120);
  e->Rep[2].font = TTF_OpenFont("assets/Font/ChopinScript.ttf", 120);

  // RenderText
  e->Quest.surfaceText = TTF_RenderText_Solid(e->Quest.font, e->Quest.Texte, e->Quest.color);
  e->Quest1.surfaceText = TTF_RenderText_Solid(e->Quest1.font, e->Quest1.Texte, e->Quest1.color);
  e->Rep[0].surfaceText = TTF_RenderText_Solid(e->Rep[0].font, e->Rep[0].Texte, e->Rep[0].color);
  e->Rep[1].surfaceText = TTF_RenderText_Solid(e->Rep[1].font, e->Rep[1].Texte, e->Rep[1].color);
  e->Rep[2].surfaceText = TTF_RenderText_Solid(e->Rep[2].font, e->Rep[2].Texte, e->Rep[2].color);
  for (int i = 0; i < 11; i++)
  {
    sprintf(NomTimer, "assets/enigmeText/Timer/%d.jpg", i);
    initImg(&e->Timer[i], 1673, 32, NomTimer);
  }
  e->TimerI = 0;
  fclose(e->f);
  fclose(f1);
  return 1;
}

void afficherEnigme1(enigme e, SDL_Surface *screen)
{
  SDL_BlitSurface(e.Backg[0].img, NULL, screen, &e.Backg[0].pos);
  SDL_BlitSurface(e.Quest.surfaceText, NULL, screen, &e.Quest.pos);
  SDL_BlitSurface(e.Quest1.surfaceText, NULL, screen, &e.Quest1.pos);
  SDL_BlitSurface(e.Rep[0].surfaceText, NULL, screen, &e.Rep[0].pos);
  SDL_BlitSurface(e.Rep[1].surfaceText, NULL, screen, &e.Rep[1].pos);
  SDL_BlitSurface(e.Rep[2].surfaceText, NULL, screen, &e.Rep[2].pos);
}
void animer1(enigme *e, SDL_Surface *screen)
{
  AfficherImg(e->Timer[10 - e->TimerI], screen);
  e->TimerI++;
}
