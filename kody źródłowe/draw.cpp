#include "draw.h"

static SDL_Texture *getTexture(char *name);
static void addTextureToCache(char *name, SDL_Texture *sdlTexture);

void prepareScene(void)
{
	SDL_SetRenderDrawColor(app.renderer, 160, 128, 96, 255);
	SDL_RenderClear(app.renderer);
}

void presentScene(void)
{
	SDL_RenderPresent(app.renderer);
}


static SDL_Texture *getTexture(char *name)
{
	Texture *t;

	for (t = app.textureHead.next; t != NULL; t = t->next)
	{
		if (strcmp(t->name, name) == 0)
		{
			return t->texture;
		}
	}

	return NULL;
}

static void addTextureToCache(char *name, SDL_Texture *sdlTexture)
{
	Texture *texture;

	texture = (Texture*)malloc(sizeof(Texture));
	memset(texture, 0, sizeof(Texture));
	app.textureTail->next = texture;
	app.textureTail = texture;

	strncpy_s(texture->name, name, MAX_NAME_LENGTH);
	texture->texture = sdlTexture;
}

SDL_Texture* loadTexture(char* filename)
{
	SDL_Texture* texture;

	texture = getTexture(filename);

	if (texture == NULL)
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
		texture = IMG_LoadTexture(app.renderer, filename);
		addTextureToCache(filename, texture);
	}

	/*
	if (texture == NULL)
	{
		printf("didn't manage to load texture\n");
	}
	*/
	return texture;


}


SDL_Surface* loadSurface(char* filename)
{
	SDL_Surface* loadedSurface = IMG_Load(filename);
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", filename, IMG_GetError());
	}
	/*else
	{
		//Convert surface to screen format
		SDL_Surface* optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, NULL);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", filename, SDL_GetError());
		}
		
		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}*/
	return loadedSurface;
}
void blit(SDL_Texture* texture, int x, int y)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	dest.w = src->w;
	dest.h = src->h;

	SDL_RenderCopy(app.renderer, texture, src, &dest);
}