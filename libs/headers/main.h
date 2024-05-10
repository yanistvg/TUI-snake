#ifndef _YG_MAIN_H_
#define _YG_MAIN_H_

#include <stdio.h>
#include <ctype.h>
#include <time.h>

#include "./returns.h"
#include "./terminal-interact.h"
#include "./draws.h"
#include "./apple.h"

#define _YG_DELAY_PLAY_ 500
#define _YG_COUNTER_MOVE_SNAKE_ 150000/_YG_DELAY_PLAY_

extern struct snake_t snake;
extern struct apple_t apple;

#endif
