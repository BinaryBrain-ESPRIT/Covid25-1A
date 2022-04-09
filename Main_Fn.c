#include "Main_Fn.h"

int Setup(Config *Confg)
{
    FILE *f = fopen("Data/Config.txt", "r");
    char Nom[50];
    int Value;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("ERROR : %s\n", SDL_GetError());
        return 0;
    }
    if (TTF_Init() != 0)
    {
        printf("ERROR : %s\n", SDL_GetError());
        return 0;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
        printf("%s\n", Mix_GetError());
        return 0;
    }
    SDL_WM_SetCaption("Covid 25", "");

    while (fscanf(f, "%s : %d", Nom, &Value) != EOF)
    {
        if (strcmp(Nom, "Money") == 0)
            Confg->Money = Value;
        else if (strcmp(Nom, "Player") == 0)
            Confg->Player = Value;
        else if (strcmp(Nom, "LevelReached") == 0)
            Confg->LevelR = Value;
        else if (strcmp(Nom, "Language") == 0)
            Confg->Lang = Value;
        else if (strcmp(Nom, "FullScreen") == 0)
            Confg->Fullscr = Value;
        else if (strcmp(Nom, "Volume") == 0)
            Confg->Volume = Value;
        else if (strcmp(Nom, "PosVol") == 0)
            Confg->posVol = Value;
    }
    fclose(f);
    return 1;
}

void SaveSetting(Config *Confg)
{
    FILE *f = fopen("Data/Config.txt", "w");

    fprintf(f, "Money : %d\n", Confg->Money);
    fprintf(f, "Player : %d\n", Confg->Player);
    fprintf(f, "LevelReached : %d\n", Confg->LevelR);
    fprintf(f, "Language : %d\n", Confg->Lang);
    fprintf(f, "FullScreen : %d\n", Confg->Fullscr);
    fprintf(f, "Volume : %d\n", Confg->Volume);
    fprintf(f, "PosVol : %d\n", Confg->posVol);

    fclose(f);
}

void InitTxt_en(Text *tabMT, Text *tabMAT)
{
    InitTitle(&tabMT[0], "Covid-25");
    iniText(&tabMT[1], 430, "New Game");
    iniText(&tabMT[2], 560, "Settings");
    iniText(&tabMT[3], 690, "Credits");
    iniText(&tabMT[4], 820, "Quit");

    InitTitle(&tabMAT[0], "Covid-25");
    iniActiveText(&tabMAT[1], 430, "New Game");
    iniActiveText(&tabMAT[2], 560, "Settings");
    iniActiveText(&tabMAT[3], 690, "Credits");
    iniActiveText(&tabMAT[4], 820, "Quit");
}

void InitImg_fr(Image *tabMO, Image *tabMAO)
{
    initImg(&tabMO[3], Width / 2 - 245, 450, "assets/MenuOpt/language_fr.png");
    initImg(&tabMO[4], Width / 2 - 245, 700, "assets/MenuOpt/fullscreen_fr.png");
    initImg(&tabMO[5], Width / 2 - 147, 945, "assets/MenuOpt/return_fr.png");

    initImg(&tabMAO[0], Width / 2 - 245, 450, "assets/MenuOpt/language_selected_fr.png");
    initImg(&tabMAO[1], Width / 2 - 245, 700, "assets/MenuOpt/fullscreen_selected_fr.png");
    initImg(&tabMAO[2], Width / 2 - 147, 945, "assets/MenuOpt/return_selected_fr.png");
}

void InitImg_en(Image *tabMO, Image *tabMAO)
{
    initImg(&tabMO[3], Width / 2 - 245, 450, "assets/MenuOpt/language.png");
    initImg(&tabMO[4], Width / 2 - 245, 700, "assets/MenuOpt/fullscreen.png");
    initImg(&tabMO[5], Width / 2 - 147, 945, "assets/MenuOpt/return.png");

    initImg(&tabMAO[0], Width / 2 - 245, 450, "assets/MenuOpt/language_selected.png");
    initImg(&tabMAO[1], Width / 2 - 245, 700, "assets/MenuOpt/fullscreen_selected.png");
    initImg(&tabMAO[2], Width / 2 - 147, 945, "assets/MenuOpt/return_selected.png");
}

void InitTxt_fr(Text *tabMT, Text *tabMAT)
{
    iniText(&tabMT[1], 430, "Nouveau Jeu");
    iniText(&tabMT[2], 560, "Parametre");
    iniText(&tabMT[3], 690, "Credits");
    iniText(&tabMT[4], 820, "Quitter");

    iniActiveText(&tabMAT[1], 430, "Nouveau Jeu");
    iniActiveText(&tabMAT[2], 560, "Parametre");
    iniActiveText(&tabMAT[3], 690, "Credits");
    iniActiveText(&tabMAT[4], 820, "Quitter");
}

void PlayMusic(char NameMusic[], Mix_Music *music)
{
    music = Mix_LoadMUS(NameMusic);
    Mix_PlayMusic(music, -1);
}

void PlayChunkMusic(char NameMusic[], Mix_Chunk *sound)
{
    sound = Mix_LoadWAV(NameMusic);
    Mix_PlayChannel(-1, sound, 0);
}

void Liberer_MusCh(Mix_Chunk *sound)
{
    Mix_FreeChunk(sound);
}

void Liberer_Mus(Mix_Music *music)
{
    Mix_FreeMusic(music);
}

