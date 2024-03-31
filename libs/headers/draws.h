#ifndef _YG_DRAWS_H_
#define _YG_DRAWS_H_

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "./terminal-interact.h"
#include "./returns.h"

#define TEXT_BLACK  "\033[0;30m"
#define TEXT_RED    "\033[0;31m"
#define TEXT_GREEN  "\033[0;32m"
#define TEXT_YELLOW "\033[0;33m"
#define TEXT_BLUE   "\033[0;34m"
#define TEXT_PURPLE "\033[0;35m"
#define TEXT_CYAN   "\033[0;36m"
#define TEXT_GREY   "\033[0;37m"

#define FONT_BLACK  "\033[0;40m"
#define FONT_RED    "\033[0;41m"
#define FONT_GREEN  "\033[0;42m"
#define FONT_YELLOW "\033[0;43m"
#define FONT_BLUE   "\033[0;44m"
#define FONT_PURPLE "\033[0;45m"
#define FONT_CYAN   "\033[0;46m"
#define FONT_GREY   "\033[0;47m"

#define DEFAULT_COLOR "\033[0;m"

void   drawMainGameScreen(int size[2]);
void   drawBordureLine(int size_x);
void   changeScreenPos(int pos_x, int pos_y);
void   drawSnakeTitle(int size_x, int size_y);
void   clearLogoTitle(int size_x, int size_y);

#endif
