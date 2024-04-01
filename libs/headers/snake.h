#ifndef _YG_SNAKE_H_
#define _YG_SNAKE_H_

#include <stdlib.h>

#include "./returns.h"

struct snake_pos_t {
	int                 pos_x;
	int                 pos_y;
	struct snake_pos_t *next;
};

struct snake_t {
	int                 size;
	int                 direction;
	struct snake_pos_t *snake_position_begin;
};

#define EAST  1
#define OUEST 2
#define NORTH 3
#define SOUTH 4

int                 initSnake(void);
int                 destroySnake(void);
struct snake_pos_t *moveSnake(void);

#endif
