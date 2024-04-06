#ifndef _YG_TERMINAL_INTERACT_H_
#define _YG_TERMINAL_INTERACT_H_

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <strings.h>

#include "./returns.h"
#include "./snake.h"

#define X 0
#define Y 1

int     getTermSize(int size[2]);
void    exitCodeWithError(const char *error, const int errorValue);
void    enableRawMenuTerminal(void);
void    disableRawMenuTerminal(void);
int     getMenuChangeBtn(int selected_btn);
void    enableRawPlayTerminal(void);
int     readPlayingInput(void);

#endif
