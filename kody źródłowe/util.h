#include "common.h"

int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
int MAX(int x1, int x2);
int MIN(int x1, int x2);

extern Stage stage;

extern int enemySpawnTimer;
extern int stageResetTimer;
extern void initPlayer(void);