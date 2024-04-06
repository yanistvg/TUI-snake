#ifndef _YG_DRAWS_H_
#define _YG_DRAWS_H_

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "./terminal-interact.h"
#include "./returns.h"
#include "./snake.h"

#define TEXT_BLACK  "\033[30m"
#define TEXT_RED    "\033[31m"
#define TEXT_GREEN  "\033[32m"
#define TEXT_YELLOW "\033[33m"
#define TEXT_BLUE   "\033[34m"
#define TEXT_PURPLE "\033[35m"
#define TEXT_CYAN   "\033[36m"
#define TEXT_GREY   "\033[37m"

#define FONT_BLACK  "\033[40m"
#define FONT_RED    "\033[41m"
#define FONT_GREEN  "\033[42m"
#define FONT_YELLOW "\033[43m"
#define FONT_BLUE   "\033[44m"
#define FONT_PURPLE "\033[45m"
#define FONT_CYAN   "\033[46m"
#define FONT_GREY   "\033[47m"

#define DEFAULT_COLOR "\033[0;m"

#define ANIMATION_DELAY 10000

void    drawMainGameScreen(const int size[2]);
void    drawBordureLine(const int size_x);
void    changeScreenPos(const int pos_x, const int pos_y);
void    drawSnakeTitle(const int size_x, const int size_y);
void    clearLogoTitle(const int size_x, const int size_y);
void    drawSnack(const struct snake_t *snake);
int     drawMainMenu(const int size_x, const int new_btn);
void    drawMainLogo(const int size_x);
void    drawPlayBtn(const int size_x, const int selected);
void    drawQuitteBtn(const int size_x, const int selected);
void    deleteSnakeEnd(const int pos_x, const int pos_y);
void    moveSnakeHead(const int pos_x, const int pos_y);

#endif
