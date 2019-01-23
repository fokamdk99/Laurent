#include "sound.h"

static void loadSounds(void);

static Mix_Chunk *sounds[SND_MAX];
static Mix_Music *music;

void initSounds(void)
{
	memset(sounds, 0, sizeof(Mix_Chunk*) * SND_MAX);

	music = NULL;

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

	loadSounds();
}
void loadMusic(char *filename)
{
	if (music != NULL)
	{
		Mix_HaltMusic();
		Mix_FreeMusic(music);
		music = NULL;
	}

	music = Mix_LoadMUS(filename);
	if(music == NULL)
	{
		printf("nie udalo sie zaladowac piosenki\n");
	}
}

void playMusic(int loop)
{
	Mix_PlayMusic(music, (loop) ? -1 : 0);
}

void playSound(int id, int channel)
{
	Mix_PlayChannel(channel, sounds[id], 0);
}

static void loadSounds(void)
{
	sounds[SND_PLAYER_FIRE] = Mix_LoadWAV("334227__jradcoolness__laser.ogg");
	sounds[SND_ALIEN_FIRE] = Mix_LoadWAV("196914__dpoggioli__laser-gun.ogg");
	sounds[SND_PLAYER_DIE] = Mix_LoadWAV("245372__quaker540__hq-explosion.ogg");
	sounds[SND_ALIEN_DIE] = Mix_LoadWAV("10 Guage Shotgun-SoundBible.com-74120584.ogg");
	sounds[SND_THUGLIFE] = Mix_LoadWAV("thugLifeMusic.mp3");
	sounds[SND_MAIN] = Mix_LoadWAV("ridersonthestorm.mp3");
}
