#include "input.h"

void doKeyUp(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		app.keyboard[event->keysym.scancode] = 0;
	}
	/*
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_UP)
		{
			app.up = 0;
		}

		if (event->keysym.scancode == SDL_SCANCODE_DOWN)
		{
			app.down = 0;
		}

		if (event->keysym.scancode == SDL_SCANCODE_LEFT)
		{
			app.left = 0;
		}

		if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			app.right = 0;
		}

		if (event->keysym.scancode == SDL_SCANCODE_LCTRL)
		{
			app.fire = 0;
		}

		if (event->keysym.scancode == SDL_SCANCODE_LSHIFT)
		{
			app.acc = 0;
		}
	}*/
}

void doKeyDown(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		app.keyboard[event->keysym.scancode] = 1;
	}
	/*
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_UP)
		{
			app.up = 1;
		}

		if (event->keysym.scancode == SDL_SCANCODE_DOWN)
		{
			app.down = 1;
		}

		if (event->keysym.scancode == SDL_SCANCODE_LEFT)
		{
			app.left = 1;
		}

		if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			app.right = 1;
		}

		if(event->keysym.scancode == SDL_SCANCODE_LCTRL)
		{
			app.fire = 1;
		}
		
		if (event->keysym.scancode == SDL_SCANCODE_LSHIFT)
		{
			app.acc = 1;
		}
	}
	*/
}

void doInput(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			FILE* wynik;
			errno_t err;
			err = fopen_s(&wynik, "wynik.txt", "w+");
			for (int i = 0; i < NUM_HIGHSCORES; i++)
			{
				fprintf(wynik, "%d\n", highscores.highscore[i].score);
			}
			fclose(wynik);
			exit(0);
			break;

		case SDL_KEYDOWN:
			doKeyDown(&event.key);
			break;

		case SDL_KEYUP:
			doKeyUp(&event.key);
			break;



		default:
			break;
		}
	}
}
