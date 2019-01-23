#include "init.h"

void initSDL(void)
{
	int rendererFlags, windowFlags;
	rendererFlags = SDL_RENDERER_ACCELERATED;
	windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	app.window = SDL_CreateWindow("thug life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);


	if (!app.window)
	{
		printf("failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
		exit(1);
	}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL PNG init_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	}
	else
	{
		//Get window surface
		SDL_Surface* gSurface = SDL_GetWindowSurface(app.window);
	}
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

	if (!app.renderer)
	{
		printf("failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		printf("Couldn't initialize SDL Mixer\n");
		exit(1);
	}
	Mix_AllocateChannels(MAX_SND_CHANNELS);
	
	SDL_ShowCursor(0);

	SDL_GetRendererOutputSize(app.renderer, &w, &h);
}

void cleanup(void)
{
	SDL_DestroyRenderer(app.renderer);

	SDL_DestroyWindow(app.window);

	SDL_Quit();
}

void initGame(void)
{
	app.textureTail = &app.textureHead;

	initBackground();

	initStarfield();

	initSounds();

	initFonts();

	initHighscoreTable();

	char muzyka2[50] = "ridersonthestorm.mp3";
	Mix_Music *piosenka1 = NULL;
	piosenka1 = Mix_LoadMUS(muzyka2);

	//printf("muzyka2 check\n");
	Mix_PlayMusic(piosenka1, -1);
	//playSound(SND_THUGLIFE, CH_ANY);
}