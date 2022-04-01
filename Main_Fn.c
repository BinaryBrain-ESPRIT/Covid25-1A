#include "Main_Fn.h"

int Setup(Config *Confg)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("ERROR : %s", SDL_GetError());
        return 0;
    }
    if (TTF_Init() != 0)
    {
        printf("ERROR : %s", SDL_GetError());
        return 0;
    }
    if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 1536) == -1)
    {
        printf("%s", Mix_GetError());
        return 0;
    }

    Confg->Lang = 1;
    Confg->Volume = 1;
    Confg->Fullscr = 1;
    Confg->LevelR = 0;
    Confg->Player = 0;

    return 1;
}

void InitTxt_en(Text *tabMT,Text * tabMAT)
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

void InitImg_fr(Image *tabMO,Image * tabMAO)
{
    initImg(&tabMO[3], Width / 2 - 245, 450, "assets/MenuOpt/language_fr.png");
    initImg(&tabMO[4], Width / 2 - 245, 700, "assets/MenuOpt/fullscreen_fr.png");
    initImg(&tabMO[5], Width / 2 - 147, 945, "assets/MenuOpt/return_fr.png");

    initImg(&tabMAO[0], Width / 2 - 245, 450, "assets/MenuOpt/language_selected_fr.png");
    initImg(&tabMAO[1], Width / 2 - 245, 700, "assets/MenuOpt/fullscreen_selected_fr.png");
    initImg(&tabMAO[2], Width / 2 - 147, 945, "assets/MenuOpt/return_selected_fr.png");
}

void InitImg_en(Image *tabMO,Image * tabMAO)
{
    initImg(&tabMO[3], Width / 2 - 245, 450, "assets/MenuOpt/language.png");
    initImg(&tabMO[4], Width / 2 - 245, 700, "assets/MenuOpt/fullscreen.png");
    initImg(&tabMO[5], Width / 2 - 147, 945, "assets/MenuOpt/return.png");

    initImg(&tabMAO[0], Width / 2 - 245, 450, "assets/MenuOpt/language_selected.png");
    initImg(&tabMAO[1], Width / 2 - 245, 700, "assets/MenuOpt/fullscreen_selected.png");
    initImg(&tabMAO[2], Width / 2 - 147, 945, "assets/MenuOpt/return_selected.png");
}

void InitTxt_fr(Text *tabMT,Text * tabMAT)
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
