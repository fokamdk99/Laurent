#include "common.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "sound.h"

int w, h;
extern App app;
void initSDL(void);
void cleanup(void);
void initGame(void);

extern void initBackground(void);
extern void initFonts(void);
extern void initHighscoreTable(void);
extern void initSounds(void);
extern void initStarfield(void);
extern void loadMusic(char *filename);
extern void playMusic(int loop);

