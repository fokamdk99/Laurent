#include "common.h"

extern void doInput(void);
extern void prepareScene(void);
extern void presentScene(void);
extern void initSDL(void);
extern void cleanup(void);
extern void initStage();
extern void initGame(void);
extern void initPlayer();
extern void initSounds(void);
extern void loadMusic(char *filename);
extern void playMusic(int loop);
extern void playSound(int id, int channel);
extern void initFonts(void);
extern void initHighscores(void);
extern void initBackground(void);
extern void initStarfield(void);
extern void initHighscoreTable(void);
extern void initTitle(void);
/*
extern SDL_Texture* loadTexture(char* filename);
extern void blit(SDL_Texture* texture, int x, int y);;
extern SDL_Surface* loadSurface(char* filename);
extern void doKeyDown(SDL_KeyboardEvent *event);
extern void doKeyDown(SDL_KeyboardEvent *event);

typedef struct
{
	SDL_Renderer *renderer;
	SDL_Window *window;
} App;
*/

App app;
Entity player;
Entity bullet;
Stage stage;
Stage stage2;
Highscores highscores;