#include "title.h"

static void logic(void);
static void draw(void);
static void drawLogo(void);

static SDL_Texture *sdl2Texture;
static SDL_Texture *shooterTexture;
static int reveal = 0;
static int timeout;

void initTitle(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);

	char tytul[50] = "title1.png";
	sdl2Texture = loadTexture(tytul);
	//shooterTexture = loadTexture("gfx/shooter.png");

	timeout = FPS * 5;
}

static void logic(void)
{
	doBackground();

	doStarfield();

	if (reveal < SCREEN_HEIGHT)
	{
		reveal++;
	}
	
	if (app.keyboard[SDL_SCANCODE_LSHIFT])
	{
		initHighscores();
	}

	if (app.keyboard[SDL_SCANCODE_LCTRL])
	{
		initStage();
	}
	if (app.keyboard[SDL_SCANCODE_ESCAPE])
	{
		FILE* wynik;
		errno_t err;
		err = fopen_s(&wynik, "wynik.txt", "w+");
		for (int i = 0; i < NUM_HIGHSCORES; i++)
		{
			fprintf(wynik, "%d\n", highscores.highscore[i].score);
		}
		fclose(wynik);
		exit(0);
	}
}

static void draw(void)
{
	drawBackground();

	drawStarfield();

	drawLogo();

	char press1[50] = "PRESS LEFT CTRL TO PLAY";
	char press2[50] = "PRESS LEFT SHIFT TO REVEAL HIGHSCORETABLE";
	char press3[100] = "MANUAL: USE ARROWS TO MOVE; PRESS LEFT CTRL TO SHOOT";
	char press4[100] = "PRESS LEFT SHIFT TO MOVE FASTER";
	char press5[100] = "PRESS S AND ONE OF THE ARROWS TO TELEPORT";
	char press6[50] = "TO LEAVE THE GAME PRESS ESCAPE";

	if (--timeout % 40 < 35)
	{
		if (timeout == 0)
		{
			timeout = 5 * FPS;
		}
		drawText(SCREEN_WIDTH / 2 - GLYPH_WIDTH*strlen(press1)/2, 350, 255, 255, 255,  press1); //TEXT_CENTER,
		drawText(SCREEN_WIDTH / 2 - GLYPH_WIDTH * strlen(press2) / 2, 410, 255, 255, 255, press2);
		drawText(SCREEN_WIDTH / 2 - GLYPH_WIDTH * strlen(press3) / 2, 470, 255, 255, 255, press3);
		drawText(SCREEN_WIDTH / 2 - GLYPH_WIDTH * strlen(press4) / 2, 530, 255, 255, 255, press4);
		drawText(SCREEN_WIDTH / 2 - GLYPH_WIDTH * strlen(press5) / 2, 590, 255, 255, 255, press5);
		drawText(SCREEN_WIDTH / 2 - GLYPH_WIDTH * strlen(press6) / 2, 650, 255, 255, 255, press6);
	}
}

static void drawLogo(void)
{
	SDL_Rect r;

	r.x = 0;
	r.y = 0;

	SDL_QueryTexture(sdl2Texture, NULL, NULL, &r.w, &r.h);

	r.h = MIN(reveal, r.h);

	blitRect(sdl2Texture, &r, (SCREEN_WIDTH / 2) - (r.w / 2), 100);

	/*SDL_QueryTexture(shooterTexture, NULL, NULL, &r.w, &r.h);

	r.h = MIN(reveal, r.h);

	blitRect(shooterTexture, &r, (SCREEN_WIDTH / 2) - (r.w / 2), 250);*/
}