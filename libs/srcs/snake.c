#include "../headers/snake.h"

struct snake_t snake;

/*
*** initSnake permt d'initialiser le structure du snack pour pouvoir
*** l'utiliser
***
*** input : none
***
*** output: none
*/
int initSnake(void) {
	snake.size                 = 2;
	snake.direction            = EAST;
	snake.snake_position_begin = NULL;

	snake.snake_position_begin = (struct snake_pos_t*)malloc(sizeof(struct snake_pos_t));

	if (snake.snake_position_begin == NULL) return _YG_ALLOC_ERROR_;
	
	snake.snake_position_begin->next  = (struct snake_pos_t*)malloc(sizeof(struct snake_pos_t));
	if (snake.snake_position_begin->next == NULL) {
		free(snake.snake_position_begin);
		return _YG_ALLOC_ERROR_;
	}

	snake.snake_position_begin->pos_x = 4;
	snake.snake_position_begin->pos_y = 4;
	
	snake.snake_position_begin->next->next  = NULL;
	snake.snake_position_begin->next->pos_x = 3;
	snake.snake_position_begin->next->pos_y = 4;

	return _YG_SUCCESS_;
}

/*
*** destroySnake permet de supprimer le snack completement
***
*** input : none
***
*** output: none
*/
int destroySnake(void) {
	struct snake_pos_t *prev_pos = snake.snake_position_begin;

	while (snake.snake_position_begin != NULL) {
		snake.snake_position_begin = snake.snake_position_begin->next;
		free(prev_pos);
		prev_pos = snake.snake_position_begin;
	}
	snake.size      = 0;
	snake.direction = 0;

	return _YG_SUCCESS_;
}

/*
*** moveSnake permet de deplacer le snake sur la grille en fonction
*** de son orientation
***
*** input : none
***
*** output:
***    struct snake_pos_t * -> poiteur sur l'ancienne fin du snake
*/
struct snake_pos_t *moveSnake(void) {
	struct snake_pos_t *new_head = NULL;
	struct snake_pos_t *end_snake = snake.snake_position_begin;
	struct snake_pos_t *return_end = NULL;

	new_head = (struct snake_pos_t *)malloc(sizeof(struct snake_pos_t));
	new_head->pos_x = snake.snake_position_begin->pos_x;
	new_head->pos_y = snake.snake_position_begin->pos_y;
	new_head->next = snake.snake_position_begin;

	if (snake.direction == EAST ) new_head->pos_x++;
	if (snake.direction == OUEST) new_head->pos_x--;
	if (snake.direction == NORTH) new_head->pos_y--;
	if (snake.direction == SOUTH) new_head->pos_y++;

	snake.snake_position_begin = new_head;

	while (end_snake->next != NULL) {
		if (end_snake->next->next == NULL) {
			return_end = end_snake->next;
			end_snake->next = NULL;
		} else {
			end_snake = end_snake->next;
		}
	}

	return return_end;
}

/*
*** changeSnakeDirection permet de changer la direction du snake
*** pour la prochaine iteration de son deplacement
***
*** input :
***    int -> valeur de sa nouvelle direction valeur : [1; 4]
***
*** output: none
*/
void changeSnakeDirection(int newDirection) {
	if (newDirection < 1 || newDirection > 4) return;

	/* verification des changement non faisable */
	if (newDirection == NORTH && snake.direction == SOUTH) return;
	if (newDirection == SOUTH && snake.direction == NORTH) return;
	if (newDirection == EAST  && snake.direction == OUEST) return;
	if (newDirection == OUEST && snake.direction == EAST ) return;

	/* changement de direction du snake */
	snake.direction = newDirection;
}
