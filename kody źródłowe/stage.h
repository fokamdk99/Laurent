#include "common.h"
#include "sound.h"
#include "SDL_mixer.h"

extern void blit(SDL_Texture *texture, int x, int y);
extern SDL_Texture *loadTexture(char *filename);

extern void addHighscore(int score);
extern void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y);
extern int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
extern void playSound(int id, int channel);
extern void loadMusic(char *filename);
extern void playMusic(int loop);
extern void drawText(int x, int y, int r, int g, int b, char *format, ...);
extern int MAX(int x1, int x2);
extern int MIN(int x1, int x2);
extern void calcSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);
extern void initStarfield();
extern void doBackground(void);
extern void doStarfield(void);
extern void drawBackground(void);
extern void drawStarfield(void);
extern void drawText(int x, int y, int r, int g, int b, char *format, ...);
extern void initHighscores(void);

extern App app;
extern Stage stage;
extern Stage stage2;
extern Mix_Music *music;
extern Highscores highscores;
extern Mix_Chunk *sounds[SND_MAX];
extern int w;
extern int h;