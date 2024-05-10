#ifndef _YG_APPLE_H_
#define _YG_APPLE_H_

#include <time.h>
#include <stdlib.h>

#include "./snake.h"

struct apple_t {
    int pos_x;
    int pos_y;
};

void generateApple(const int max_x, const int max_y);

#endif
