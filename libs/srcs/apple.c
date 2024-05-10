#include "../headers/apple.h"

struct apple_t apple = {0, 0};

/*
*** generateApple permet d'initaliser une pomme qui n'est pas sur le snake
***
*** input :
***   int -> valeur maximal en x
***   int -> valeur maximal en y
***
*** output: none
*/
void generateApple(const int max_x, const int max_y) {
    do {
        apple.pos_x = 2 + ( rand() % (max_x - 2) );
        apple.pos_y = 3 + ( rand() % (max_y - 4) );

        if (apple.pos_x % 2 != 0) {
            if (apple.pos_x - 1 > 2) apple.pos_x -= 1;
            else                     apple.pos_x += 1;
        }
    } while (posIsInSnake(apple.pos_x, apple.pos_y));
}
