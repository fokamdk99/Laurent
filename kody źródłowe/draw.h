#include "common.h"

void prepareScene(void);
void presentScene(void);
void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y);

SDL_Texture* loadTexture(char* filename);
void blit(SDL_Texture* texture, int x, int y);
SDL_Texture* loadTexture(char* filename);
SDL_Surface* loadSurface(char* filename);
extern App app;
extern Entity player;