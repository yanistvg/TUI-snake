#ifndef _YG_TERMINAL_INTERACT_H_
#define _YG_TERMINAL_INTERACT_H_

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "./returns.h"

#define X 0
#define Y 1

int     getTermSize(int size[2]);
void    exitCodeWithError(char *error, int errorValue);

#endif
