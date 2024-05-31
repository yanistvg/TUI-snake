#include "../headers/apple.h"

struct apple_t apple = {0, 0};

/**
 * generateApple permet d'initaliser une pomme qui n'est pas sur le snake
 * 
 * @param max_x valeur maximal en x
 * @param max_y valeur maximal en y
 * 
 * @return none
 * 
 * @date 2024-05-30
*/
void generateApple(const int max_x, const int max_y) {
    do {
        apple.pos_x = 2 + ( rand() % (max_x / 2 - 2) );
        apple.pos_y = 3 + ( rand() % (max_y - 4) );

        if (apple.pos_x % 2 != 0) {
            if (apple.pos_x - 1 > 2) apple.pos_x -= 1;
            else                     apple.pos_x += 1;
        }
    } while (posIsInSnake(apple.pos_x, apple.pos_y));
}

/**
 * detecColition permet de verifier sur une position donne si elle entre
 * en colision avec la pomme
 * 
 * @param pos_x position en x
 * @param pos_y position en y
 * 
 * @return _YG_COLITIONED_  si colition entre la pomme est la position
 * @return _YG_NO_COLISION_ si pas colition entre la pomme est la position
 * 
 * @date 2024-05-30
*/
int detecColitionApple(const int pos_x, const int pos_y) {
    if (pos_x == apple.pos_x && pos_y == apple.pos_y)
        return _YG_COLITIONED_;
    return _YG_NO_COLISION_;
}
