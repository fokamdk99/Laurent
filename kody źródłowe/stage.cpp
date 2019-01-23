#include "stage.h"

static void logic(void);
static void draw(void);
static void initPlayer(void);
static void fireBullet(void);
static void doPlayer();
static void doBullets(void);
static void doEnemies(void);
static void drawPlayer(void);
static void drawBullets(void);
static void doFighters(void);
static void spawnEnemies(void);
static void drawFighters(void);
static int bulletHitFighter(Entity *b);
static void placeofSpawn(Entity* enemy);
static void resetStage(void);
static void fireAlienBullet(Entity *e);
//static void initStarfield(void);
//static void doBackground(void);
//static void doStarfield(void);
static void doExplosions(void);
static void doDebris(void);
static void addExplosions(int x, int y, int num);
static void addDebris(Entity *e);
//static void drawBackground(void);
//static void drawStarfield(void);
static void drawDebris(void);
static void drawExplosions(void);
static void thugLife(void);
static void initThug();
static void drawHud(void);
static void teleport(void);
static int highscore;

static Entity *player;
static SDL_Texture *bulletTexture;
static SDL_Texture *enemyTexture;
static SDL_Texture *playerTexture;
static SDL_Texture *alienBulletTexture;
static SDL_Texture *zycie;
static int enemySpawnTimer;
static int stageResetTimer;
static int backgroundX;
static int killedEnemies;
static int isThug;
static float thugResetTimer;
static SDL_Texture *background;
static SDL_Texture *explosionTexture;
static SDL_Texture *glasses;
static Entity *okulary;
static Star stars[MAX_STARS];
static int level = 0;


char thugmusic[50] = "thugLifeMusic.mp3";
Mix_Chunk *thugsample = Mix_LoadWAV("thugLifeMusic.mp3");

void initStage(void)
{
	
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	memset(&stage, 0, sizeof(Stage));
	memset(&stage2, 0, sizeof(Stage));
	stage.fighterTail = &stage.fighterHead;
	stage.bulletTail = &stage.bulletHead;
	stage.explosionTail = &stage.explosionHead;
	stage.debrisTail = &stage.debrisHead;
	
	
	//stage2.fighterTail = &stage2.fighterHead;
	stage2.bulletTail = &stage2.bulletHead;
	
	char obrazek[50] = "playerBullet.png";
	char obrazek2[50] = "enemy.png";
	char obrazek3[50] = "player.png";
	char obrazek4[50] = "background.png";
	char obrazek5[50] = "explosion.png";
	char obrazek6[50] = "thuglife.png";
	char alienbullet[50] = "strzala.png";
	char life[50] = "serduszko.png";
	bulletTexture = loadTexture(obrazek);
	alienBulletTexture = loadTexture(alienbullet);
	if (alienBulletTexture == NULL)
	{
		printf("nie dziala alienBulletTexture!!!!!!!!!!!!!\n");
	}
	enemyTexture = loadTexture(obrazek2);
	playerTexture = loadTexture(obrazek3);
	background = loadTexture(obrazek4);
	explosionTexture = loadTexture(obrazek5);
	printf("glasses check check\n");
	glasses = loadTexture(obrazek6);
	zycie = loadTexture(life);
	enemySpawnTimer = 0;
	killedEnemies = 1;
	//initPlayer();

	char muzyka1[50] = "thugLifeMusic.mp3";
	char muzyka2[50] = "ridersonthestorm.mp3";
	
	highscore = highscores.highscore[0].score;
	resetStage();
	
}

static void teleport(void)
{
	if (player != NULL)
	{
		if (app.keyboard[SDL_SCANCODE_S] && app.keyboard[SDL_SCANCODE_RIGHT])
		{
			player->x += 30;
		}
		if (app.keyboard[SDL_SCANCODE_S] && app.keyboard[SDL_SCANCODE_LEFT])
		{
			player->x -= 30;
		}
		if (app.keyboard[SDL_SCANCODE_S] && app.keyboard[SDL_SCANCODE_UP])
		{
			player->y -= 30;
		}
		if (app.keyboard[SDL_SCANCODE_S] && app.keyboard[SDL_SCANCODE_DOWN])
		{
			player->y += 30;
		}
	}
	
}

static void thugLife(void)
{
	if (isThug != 0)
	{
		if (okulary->x >= player->x - 20)
		{
			okulary->x -= okulary->dx;
		}
		if (okulary->y <= player->y - 30)
		{
			okulary->y += okulary->dy;
		}
		
	}
	
	if(okulary->x <= player->x - 20 && okulary->y >= player->y - 30)
	{
		isThug = 0;
	}
}

static void initThug()
{
	okulary = (Entity*)malloc(sizeof(Entity));
	memset(okulary, 0, sizeof(Entity));
	okulary->dx = 2;
	okulary->dy = 2;
	okulary->texture = glasses;
	SDL_QueryTexture(okulary->texture, NULL, NULL, &okulary->w, &okulary->h);
}

static void initPlayer()
{
	player = (Entity*)malloc(sizeof(Entity));
	memset(player, 0, sizeof(Entity));
	if (player == NULL)
	{
		printf("zjebany memset w initplayer\n");
	}
	stage.fighterTail->next = player;
	stage.fighterTail = player;
	//stage2.fighterTail->next = player;
	//stage2.fighterTail = player;

	player->x = 100;
	player->y = 100;
	player->side = SIDE_PLAYER;
	player->health = 3;
	player->texture = playerTexture;
	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

static void resetStage(void)
{
	Entity *e, *e2;
	Explosion *ex;
	Debris *d;

	while (stage.fighterHead.next)
	{
		e = stage.fighterHead.next;
		//printf("uwalniam fighterhead\n");
		stage.fighterHead.next = e->next;
		free(e);
	}
	
	while (stage.bulletHead.next)
	{
		//printf("uwalniam bullethead\n");
		e = stage.bulletHead.next;
		stage.bulletHead.next = e->next;
		free(e);
	}
	
	while (stage2.bulletHead.next)
	{
		//printf("uwalniam bullethead2\n");
		e2 = stage2.bulletHead.next;
		stage2.bulletHead.next = e2->next;
		free(e2);
	}
	
	while (stage.explosionHead.next)
	{
		if (stage.explosionHead.next == NULL)
		printf("uwalniam explosionhead\n");
		ex = stage.explosionHead.next;
		stage.explosionHead.next = ex->next;
		free(ex);
	}
	
	while (stage.debrisHead.next)
	{
		//printf("uwalniam debrishead\n");
		d = stage.debrisHead.next;
		stage.debrisHead.next = d->next;
		free(d);
	}
	
	memset(&stage, 0, sizeof(Stage));
	stage.fighterTail = &stage.fighterHead;
	stage.bulletTail = &stage.bulletHead;
	stage.explosionTail = &stage.explosionHead;
	stage.debrisTail = &stage.debrisHead;
	stage2.bulletTail = &stage2.bulletHead; //nie jestes tego pewien
	
	initPlayer();
	initStarfield();
	initThug();
	enemySpawnTimer = 0;

	stageResetTimer = FPS * 3;
	thugResetTimer = 0;
	isThug = 0;
	stage.score = 0;
	level = 0;
	
}

static void logic(void)
{
	if (isThug == 1 || thugResetTimer >= 0)
	{

		Mix_PauseMusic();

		doBackground();

		doStarfield();

		thugLife();
		if (thugResetTimer == 0)
		{
			level++;
		}
	}
	else
	{
		Mix_ResumeMusic();

		doBackground();

		doStarfield();

		doPlayer();

		teleport();

		doFighters();

		doBullets();
		
		doEnemies();

		spawnEnemies();

		doExplosions();

		doDebris();

		//printf("resetstagetimer wynosi: %d\n", stageResetTimer);
		if (player == NULL)
		{
			stageResetTimer--;
		}
		if (player == NULL && stageResetTimer <= 0)
		{
			
			addHighscore(stage.score);

			initHighscores();
			
			//resetStage();
		}
	}
}

static void doPlayer()
{
	if (player != NULL)
	{

		player->dx = 0;

		player->dy = 0;

		if (player->reload > 0)
		{
			player->reload--;
		}

		if (app.keyboard[SDL_SCANCODE_UP] && app.keyboard[SDL_SCANCODE_LSHIFT])
		{
			player->dy = ((-2)*PLAYER_SPEED);
		}
		else
			if (app.keyboard[SDL_SCANCODE_UP])
			{
				player->dy = -PLAYER_SPEED;
			}

		if (app.keyboard[SDL_SCANCODE_DOWN] && app.keyboard[SDL_SCANCODE_LSHIFT])
		{
			player->dy = (2 * PLAYER_SPEED);
		}
		else
		{
			if (app.keyboard[SDL_SCANCODE_DOWN])
			{
				player->dy = PLAYER_SPEED;
			}
		}

		if (app.keyboard[SDL_SCANCODE_LEFT] && app.keyboard[SDL_SCANCODE_LSHIFT])
		{
			player->dx = ((-2) * PLAYER_SPEED);
		}
		else
		{
			if (app.keyboard[SDL_SCANCODE_LEFT])
			{
				player->dx = -PLAYER_SPEED;
			}
		}

		if (app.keyboard[SDL_SCANCODE_RIGHT] && app.keyboard[SDL_SCANCODE_LSHIFT])
		{
			player->dx = (2 * PLAYER_SPEED);
		}
		else
		{
			if (app.keyboard[SDL_SCANCODE_RIGHT])
			{
				player->dx = PLAYER_SPEED;
			}
		}


		if (app.keyboard[SDL_SCANCODE_LCTRL] && player->reload == 0)
		{
			fireBullet();

			playSound(SND_PLAYER_FIRE, CH_PLAYER);
		}
		if (player->x < 0)
		{
			player->x = 0;
		}
		if (player->y < 0)
		{
			player->y = 0;
		}
		if (player->x + player->w > SCREEN_WIDTH)
		{
			player->x = SCREEN_WIDTH - player->w;
		}
		if (player->y + player->h > SCREEN_HEIGHT)
		{
			player->y = SCREEN_HEIGHT - player->h;
		}
		/*if (app.keyboard[SDL_SCANCODE_ESCAPE])
		{
			exit(0);
		}*/
	}
}

static void doEnemies(void)
{
	Entity *e;

	for (e = stage.fighterHead.next; e != NULL; e = e->next)
	{
		if (e != player && player != NULL && --e->reload <= 0)
		{
			fireAlienBullet(e);
		}
	}
}

static void fireAlienBullet(Entity *e)
{
	Entity *bullet;

	bullet = (Entity*)malloc(sizeof(Entity));
	memset(bullet, 0, sizeof(Entity));
	stage.bulletTail->next = bullet;
	stage.bulletTail = bullet;

	bullet->x = e->x;
	bullet->y = e->y;
	bullet->health = 1;
	bullet->texture = alienBulletTexture;
	bullet->side = e->side;
	SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

	bullet->x += (e->w / 2) - (bullet->w / 2);
	bullet->y += (e->h / 2) - (bullet->h / 2);

	calcSlope(player->x + (player->w / 2), player->y + (player->h / 2), e->x, e->y, &bullet->dx, &bullet->dy);

	bullet->dx *= ALIEN_BULLET_SPEED;
	bullet->dy *= ALIEN_BULLET_SPEED;

	bullet->side = SIDE_ALIEN;

	e->reload = (rand() % FPS * 4);
}

static void doFighters(void)
{
	Entity *e, *prev;

	prev = &stage.fighterHead;

	
	

		for (e = stage.fighterHead.next; e != NULL; e = e->next)
		{

			if (e != player && e->x < 0)
			{
				e->dx = -e->dx;
			}
			if (e != player && e->y < 0)
			{
				e->dy = -e->dy;
			}
			if (e != player && e->x + e->w > SCREEN_WIDTH)
			{
				e->dx = -e->dx;
			}
			if (e != player && e->y + e->h > SCREEN_HEIGHT)
			{
				e->dy = -e->dy;
			}
			if (player != NULL && player->health > 0 && e->side != player->side && collision(player->x, player->y, player->w, player->h, e->x, e->y, e->w, e->h))
			{
				player->health --;
				e->health = 0;
				//printf("player health = %d", player->health);
				playSound(SND_PLAYER_DIE, CH_PLAYER);
				if (player->health > 0)
				{
					addExplosions(e->x, e->y, 32);
					addDebris(e);
				}
				else
				{
					addExplosions(player->x, player->y, 32);
					addDebris(player);
				}
				
			}

			e->x += e->dx;
			e->y += e->dy;

			if (e == player && e->health <= 0)
			{
				highscore = MAX(stage.score, highscore);
				//printf("player zabity\n");
				stage.fighterHead.next = player->next;
				player = NULL;
			}
			else if (e->health == 0)
			{
				stage.score++;
				highscore = MAX(stage.score, highscore);
				killedEnemies++;
				if (e == stage.fighterTail)
				{
					stage.fighterTail = prev;
				}
				prev->next = e->next;
				free(e);
				e = prev;
			}

			prev = e;
			
		}

}
static void placeofSpawn(Entity* enemy)
{
	int i = rand() % 3;
	switch (i)
	{
	case 0:
		enemy->x = SCREEN_WIDTH-2*(enemy->w);
		enemy->y = SCREEN_HEIGHT / 2;
		break;
	case 1:
		enemy->x = SCREEN_WIDTH - 200;
		enemy->y = 0;
		break;
	case 2:
		enemy->x = SCREEN_WIDTH - 200;
		enemy->y = SCREEN_HEIGHT - 2*(enemy->h);
		break;
	default:
		printf("nie dziala placeofSpawn\n");
	}
}

static void spawnEnemies(void)
{
	Entity *enemy;

	if (--enemySpawnTimer <= 0)
	{
		enemy = (Entity*)malloc(sizeof(Entity));
		memset(enemy, 0, sizeof(Entity));
		stage.fighterTail->next = enemy;
		stage.fighterTail = enemy;

		//enemy->x = SCREEN_WIDTH;
		//enemy->y = rand() % SCREEN_HEIGHT;
		
		enemy->texture = enemyTexture;
		enemy->side = SIDE_ALIEN;
		enemy->health = 1;
		SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);

		placeofSpawn(enemy);
		
		enemy->dx = -(2 + (rand() % 4) + rand() % 9);//calcSlope(player->x, player->y, enemy->x, enemy->y, player->dx, player->dy);//
		enemy->dy = (5 - (rand() % 7));//calcSlope(player->x, player->y, enemy->x, enemy->y, player->dx, player->dy);//
		
		enemySpawnTimer = 30 + (rand() % 60);
	}
}

static void fireBullet(void)
{
	Entity *bullet1;
	Entity *bullet2;

	bullet1 = (Entity*)malloc(sizeof(Entity));
	bullet2 = (Entity*)malloc(sizeof(Entity));
	memset(bullet1, 0, sizeof(Entity));
	memset(bullet2, 0, sizeof(Entity));
	stage.bulletTail->next = bullet1;
	stage.bulletTail = bullet1;
	stage2.bulletTail->next = bullet2;
	stage2.bulletTail = bullet2;

	bullet1->x = player->x;
	bullet2->x = player->x;
	bullet1->y = player->y;
	bullet2->y = player->y;
	bullet1->dx = PLAYER_BULLET_SPEED;
	bullet2->dx = PLAYER_BULLET_SPEED;
	bullet1->health = 1;
	bullet2->health = 1;
	bullet1->texture = bulletTexture;
	bullet2->texture = bulletTexture;
	SDL_QueryTexture(bullet1->texture, NULL, NULL, &bullet1->w, &bullet1->h);
	SDL_QueryTexture(bullet2->texture, NULL, NULL, &bullet2->w, &bullet2->h);
	bullet1->side = SIDE_PLAYER;
	bullet2->side = SIDE_PLAYER;

	bullet1->y += (bullet1->h / 2); //+= (player->h / 2)
	bullet2->y += (player->h / 2) + (bullet2->h / 2);
	player->reload = 8;
}

static void doBullets(void)
{
	Entity *b, *prev, *b2, *prev2;

	prev = &stage.bulletHead;
	prev2 = &stage2.bulletHead;

		for (b = stage.bulletHead.next; b != NULL; b = b->next)
		{
			b->x += b->dx;
			b->y += b->dy;

			if (bulletHitFighter(b))
			{


				if (killedEnemies % 25 == 0)
				{
					isThug = 1;
					okulary->x = player->x + 180;
					okulary->y = player->y - 200;
					thugResetTimer = 3 * FPS;
					Mix_PauseMusic();
					playSound(SND_THUGLIFE, CH_ANY);
				}
				addExplosions(b->x, b->y, 32);

				addDebris(b);

				if (b == stage.bulletTail)
				{
					stage.bulletTail = prev;
				}

				prev->next = b->next;
				free(b);
				b = prev;
			}

			if (bulletHitFighter(b) || b->x > SCREEN_WIDTH)
			{
				if (b == stage.bulletTail)
				{
					stage.bulletTail = prev;
				}

				prev->next = b->next;
				free(b);
				b = prev;
			}


			prev = b;

		}

		for (b2 = stage2.bulletHead.next; b2 != NULL; b2 = b2->next)
		{
			b2->x += b2->dx;
			b2->y += b2->dy;
			if (bulletHitFighter(b2))
			{

				if (killedEnemies % 25 == 0)
				{
					isThug = 1;
					okulary->x = player->x + 180;
					okulary->y = player->y - 200;
					thugResetTimer = 3 * FPS;
					Mix_PauseMusic();
					playSound(SND_THUGLIFE, CH_ANY);
				}
				addExplosions(b2->x, b2->y, 32);

				addDebris(b2);

				if (b2 == stage2.bulletTail)
				{
					stage2.bulletTail = prev2;
				}

				prev2->next = b2->next;
				free(b2);
				b2 = prev2;
			}

			if (bulletHitFighter(b2) || b2->x > SCREEN_WIDTH)
			{


				if (b2 == stage2.bulletTail)
				{
					stage2.bulletTail = prev2;
				}

				prev2->next = b2->next;
				free(b2);
				b2 = prev2;
			}

			prev2 = b2;
		}
}

static void draw(void)
{
	if (isThug == 1 || --thugResetTimer > 0)
	{
		drawBackground();

		drawStarfield();

		drawPlayer();

		blit(glasses, okulary->x, okulary->y);

		char poziom[50] = "CONGRATULATIONS! YOU ACCOMPLISHED LEVEL %d";

		if (player->y >= h/2)
		{
			drawText(w / 2 - GLYPH_WIDTH * strlen(poziom) / 2, h/2 - 200, 255, 255, 255, poziom, level+1);
		}
		else
		{
			drawText(w / 2 - GLYPH_WIDTH * strlen(poziom) / 2, h/2+200, 255, 255, 255, poziom, level+1);
		}
	}
	else
	{
		drawBackground();

		drawStarfield();

		drawBullets();

		drawFighters();

		drawDebris();

		drawExplosions();

		drawHud();
	}
}

static void drawPlayer(void)
{
		blit(player->texture, player->x, player->y);	
}

static void drawBullets(void)
{
	Entity *b;

	for (b = stage.bulletHead.next; b != NULL; b = b->next)
	{
		blit(b->texture, b->x, b->y);
	}
	for (b = stage2.bulletHead.next; b != NULL; b = b->next)
	{
		blit(b->texture, b->x, b->y);
	}
}

static void drawFighters(void)
{
	Entity *e;

	for (e = stage.fighterHead.next; e != NULL; e = e->next)
	{
		blit(e->texture, e->x, e->y);
	}
}
static int ile = 0;
static int bulletHitFighter(Entity *b)
{
	Entity *e;

	for (e = stage.fighterHead.next; e != NULL; e = e->next)
	{
		
			if (e->side != b->side && e == player && e->health > 0 && b->health!= 0 && collision(b->x, b->y, b->w, b->h, e->x, e->y, e->w, e->h))
			{
				e->health--;
				b->health = 0;
				//printf("wywolanie nr %d\n", ile++);
				playSound(SND_PLAYER_DIE, CH_PLAYER);
				//addExplosions(b->x, b->y, 32);
				//addDebris(b);
				return 1;
			}
			
			if (e->side != b->side && e != player && collision(b->x, b->y, b->w, b->h, e->x, e->y, e->w, e->h))
			{
				
					e->health = 0;
					b->health = 0;
				

				if (e == player)
				{
					if (e->health == 0)
					{
						playSound(SND_PLAYER_DIE, CH_PLAYER);
					}
				}
				else
				{
					playSound(SND_ALIEN_DIE, CH_ANY);
				}

				return 1;
			}
			
	}

	return 0;
}


static void doExplosions(void)
{
	Explosion *e, *prev;

	prev = &stage.explosionHead;

	for (e = stage.explosionHead.next; e != NULL; e = e->next)
	{
		e->x += e->dx;
		e->y += e->dy;

		if (--e->a <= 0)
		{
			if (e == stage.explosionTail)
			{
				stage.explosionTail = prev;
			}

			prev->next = e->next;
			free(e);
			e = prev;
		}

		prev = e;
	}
}

static void doDebris(void)
{
	Debris *d, *prev;

	prev = &stage.debrisHead;

	for (d = stage.debrisHead.next; d != NULL; d = d->next)
	{
		d->x += d->dx;
		d->y += d->dy;

		d->dy += 0.5;

		if (--d->life <= 0)
		{
			if (d == stage.debrisTail)
			{
				stage.debrisTail = prev;
			}

			prev->next = d->next;
			free(d);
			d = prev;
		}

		prev = d;
	}
}

static void addExplosions(int x, int y, int num)
{
	Explosion *e;
	int i;

	for (i = 0; i < num; i++)
	{
		e = (Explosion*)malloc(sizeof(Explosion));
		memset(e, 0, sizeof(Explosion));
		stage.explosionTail->next = e;
		stage.explosionTail = e;

		e->x = x + (rand() % 32) - (rand() % 32);
		e->y = y + (rand() % 32) - (rand() % 32);
		e->dx = (rand() % 10) - (rand() % 10);
		e->dy = (rand() % 10) - (rand() % 10);

		e->dx /= 10;
		e->dy /= 10;

		switch (rand() % 4)
		{
		case 0:
			e->r = 255;
			break;

		case 1:
			e->r = 255;
			e->g = 128;
			break;

		case 2:
			e->r = 255;
			e->g = 255;
			break;

		default:
			e->r = 255;
			e->g = 255;
			e->b = 255;
			break;
		}

		e->a = rand() % FPS * 3;
	}
}

static void addDebris(Entity *e)
{
	Debris *d;
	int x, y, w, h;

	w = e->w / 2;
	h = e->h / 2;

	for (y = 0; y <= h; y += h)
	{
		for (x = 0; x <= w; x += w)
		{
			d = (Debris*)malloc(sizeof(Debris));
			memset(d, 0, sizeof(Debris));
			stage.debrisTail->next = d;
			stage.debrisTail = d;

			d->x = e->x + e->w / 2;
			d->y = e->y + e->h / 2;
			d->dx = (rand() % 5) - (rand() % 5);
			d->dy = -(5 + (rand() % 12));
			d->life = FPS * 2;
			d->texture = e->texture;

			d->rect.x = x;
			d->rect.y = y;
			d->rect.w = w;
			d->rect.h = h;
		}
	}
}


static void drawDebris(void)
{
	Debris *d;

	for (d = stage.debrisHead.next; d != NULL; d = d->next)
	{
		blitRect(d->texture, &d->rect, d->x, d->y);
	}
}

static void drawExplosions(void)
{
	Explosion *e;

	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_ADD);
	SDL_SetTextureBlendMode(explosionTexture, SDL_BLENDMODE_ADD);

	for (e = stage.explosionHead.next; e != NULL; e = e->next)
	{
		SDL_SetTextureColorMod(explosionTexture, e->r, e->g, e->b);
		SDL_SetTextureAlphaMod(explosionTexture, e->a);

		blit(explosionTexture, e->x, e->y);
	}

	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);
}

static void drawHud(void)
{
	char score[50] = "SCORE: %03d";
	char najwyzszy[50] = "HIGH SCORE: %03d";
	drawText(10, 10, 255, 255, 255, score, stage.score);

	if (stage.score > 0 && stage.score == highscore)
	{
		drawText(960, 10, 0, 255, 0, najwyzszy, highscore);
	}
	else
	{
		drawText(960, 10, 255, 255, 255, najwyzszy, highscore);
	}
	if (player != NULL)
	{
		for (int i = 0; i < player->health; i++)
		{
			blit(zycie, 400 + 120 * i, 10);
		}
	}
	
}