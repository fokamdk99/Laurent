#include "common.h"
#include "SDL_mixer.h"

void initSounds(void);
void loadMusic(char *filename);
void playMusic(int loop);
void playSound(int id, int channel);	