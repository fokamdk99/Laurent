#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define PLAYER_SPEED 4
#define PLAYER_BULLET_SPEED 16
#define ALIEN_BULLET_SPEED 8
#define MAX_KEYBOARD_KEYS 350

#define SIDE_PLAYER 0
#define SIDE_ALIEN 1

#define FPS 60

#define MAX_STARS   500

#define MAX_SND_CHANNELS 8

#define PIOSENKI 100

#define MAX_LINE_LENGTH 1024

#define NUM_HIGHSCORES 8

#define STRNCPY(dest, src, n) strncpy(dest, src, n); dest[n - 1] = '\0'

#define MAX_NAME_LENGTH 64

#define GLYPH_HEIGHT 28
#define GLYPH_WIDTH  18

enum
{
	CH_ANY = -1,
	CH_PLAYER,
	CH_ALIEN_FIRE,
	CH_THUG
};

enum
{
	SND_PLAYER_FIRE,
	SND_ALIEN_FIRE,
	SND_PLAYER_DIE,
	SND_ALIEN_DIE,
	SND_MAX,
	SND_THUGLIFE,
	SND_MAIN
};

