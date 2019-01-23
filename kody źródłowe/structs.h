typedef struct 
{
	void(*logic)(void);
	void(*draw)(void);
} Delegate;

struct Texture {
	char name[MAX_NAME_LENGTH];
	SDL_Texture *texture;
	Texture *next;
};

typedef struct
{
	SDL_Renderer *renderer;
	SDL_Window *window;
	Delegate delegate;
	int keyboard[MAX_KEYBOARD_KEYS];
	Texture textureHead, *textureTail;
	/*int up;
	int down;
	int right;
	int left;
	int fire;
	int acc;*/
} App;

struct Entity
{
	float x;
	float y;
	float dx;
	float dy;
	int w;
	int h;
	int health;
	int reload;
	int ifhit;
	SDL_Texture* texture;
	SDL_Surface* surface;
	Entity *next;
	int side;
};

struct Explosion
{
	float x;
	float y;
	float dx;
	float dy;
	int r, g, b, a;
	Explosion *next;
};

struct Debris
{
	float x;
	float y;
	float dx;
	float dy;
	SDL_Rect rect;
	SDL_Texture *texture;
	int life;
	Debris *next;
};


typedef struct
{
	Entity fighterHead, *fighterTail;
	Entity bulletHead, *bulletTail;
	Explosion explosionHead;
	Explosion *explosionTail;
	Debris debrisHead;
	Debris *debrisTail;
	int score;
} Stage;


typedef struct {
	int x;
	int y;
	int speed;
} Star;

typedef struct {
	int recent;
	int score;
} Highscore;

typedef struct {
	Highscore highscore[NUM_HIGHSCORES];
} Highscores;

