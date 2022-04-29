/**
 * @file enigme.c
 * @author Maher Grati (mohammedmaher.grati@esprit.tn)
 * @brief (enigme text) file
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "enigme.h"

/**
 * @brief init enigme
 * 
 * @param e enigme
 * @param nomfichier fileName
 * @return int return 1 if initialized else if not 
 */
int InitEnigme1(enigme *e, char *nomfichier)
{
  // Declaration
  SDL_Color black = {0, 0, 0};
  char NomBackg[30];
  char NomBackgW[30];
  char NomBackgL[30];
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

  // Calcul Nbre De Ligne
  FILE *f1 = fopen("SelectedEnigme.txt", "r");

  do
  {
    End = fscanf(f1, "%d\n", &NumE1) != EOF;
    n++;
  } while (End != 0);

  fclose(f1);

  // Trouver NumEnigme Aleatoire (Pour Tester qu'il n'est pas encore choisis)
  f1 = fopen("SelectedEnigme.txt", "r");

  do
  {
    NumE = rand() % (4 - 1) + 1;
    // Existence NumE dans SelectedEnigme
    do
    {
      End = fscanf(f1, "%d\n", &NumE1) != EOF;
    } while (NumE != NumE1 && End != 0);

  } while (NumE1 == NumE && n < 3);

  // Dans Le cas Qui a choisis tous Les enigmes Il n'affche pas

  // if (n >= 3 && NumE1 == NumE)
  // return 0;

  fclose(f1);

  // Enregistrer L'enigme selectionne
  f1 = fopen("SelectedEnigme.txt", "a");

  fprintf(f1, "%d\n", NumE);

  fclose(f1);

  // Recuperer L'enigme par Le NumE
  e->f = fopen(nomfichier, "r");
  do
    fscanf(e->f, "%d %s %d %d %s %s %s %s %s %d", &e->NumE, NomBackg, &posX, &posX1, Quest, Quest1, Rep1, Rep2, Rep3, &e->NumRepC);
  while (e->NumE != NumE);

  // Remplacer le Caractere '_' par un espace
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

  strcpy(NomBackgW, "assets/enigmeImage/Win.png");
  strcpy(NomBackgL, "assets/enigmeImage/Loose.png");

  // Init Backg
  InitBackg(&e->Backg[0], NomBackg);
  InitBackg(&e->Backg[1], NomBackgW);
  InitBackg(&e->Backg[2], NomBackgL);

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

  // Render Surface Text
  e->Quest.surfaceText = TTF_RenderText_Solid(e->Quest.font, e->Quest.Texte, e->Quest.color);
  e->Quest1.surfaceText = TTF_RenderText_Solid(e->Quest1.font, e->Quest1.Texte, e->Quest1.color);
  e->Rep[0].surfaceText = TTF_RenderText_Solid(e->Rep[0].font, e->Rep[0].Texte, e->Rep[0].color);
  e->Rep[1].surfaceText = TTF_RenderText_Solid(e->Rep[1].font, e->Rep[1].Texte, e->Rep[1].color);
  e->Rep[2].surfaceText = TTF_RenderText_Solid(e->Rep[2].font, e->Rep[2].Texte, e->Rep[2].color);

  // Couleur Time
  SDL_Color Black = {0, 0, 0};
  SDL_Color Red = {193, 38, 45};

  // Durée
  e->Duration = 10;
  e->TimeOut = 0;

  // Init Timer
  for (int i = 0; i <= e->Duration; i++)
  {
    sprintf(e->Time[i].Texte, "00:%02d", i);
    if (i < 6)
      initTxt(&e->Time[i], 1707, 26, Red, 70, "assets/Font/AznKnucklesTrial-z85pa.otf", e->Time[i].Texte);
    else
      initTxt(&e->Time[i], 1707, 26, Black, 70, "assets/Font/AznKnucklesTrial-z85pa.otf", e->Time[i].Texte);
  }

  fclose(e->f);
  return 1;
}


/**
 * @brief afficher Enigme
 * 
 * @param e enigme
 * @param screen screen display
 */
void afficherEnigme1(enigme e, SDL_Surface *screen)
{
  AfficherImg(e.Backg[0], screen);
  Afficher_txt(e.Quest, screen);
  Afficher_txt(e.Quest1, screen);
  for (int i = 0; i < 3; i++)
    Afficher_txt(e.Rep[i], screen);
}
/**
 * @brief animer
 * 
 * @param e enigme
 * @param screen screen display
 */
void animer1(enigme *e, SDL_Surface *screen)
{
  int EnigmeTimeS, EnigmeTimeSPred = -1;

  EnigmeTimeS = (SDL_GetTicks() - e->TimeInit) / 1000;

  if (e->Duration - EnigmeTimeS < 0)
  {
    e->TimeOut = 1;


    return;
  }

  if (EnigmeTimeSPred != EnigmeTimeS)
  {
    afficherEnigme1(*e, screen);
    Afficher_txt(e->Time[e->Duration - EnigmeTimeS], screen);
    SDL_Flip(screen);
  }
  EnigmeTimeSPred = EnigmeTimeS;
}
/**
 * @brief Free_Enigme
 * 
 * @param e enigme
 */
void Free_Enigme1(enigme *e)
{
  for (int i = 0; i < 3; i++)
    SDL_FreeSurface(e->Backg[i].img);

  for (int i = 0; i <= e->Duration; i++)
    SDL_FreeSurface(e->Time[i].surfaceText);
  Liberer_txt(e->Quest);
  Liberer_txt(e->Quest1);
  for (int i = 0; i < 3; i++)
    Liberer_txt(e->Rep[i]);
  
}