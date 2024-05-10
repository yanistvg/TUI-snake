#include "./libs/headers/main.h"
// TODO: afficher la taille de l'ecrant en haut a droite avec sprintf pour remplacer itoa
int main(void) {
	int                 size[2] = {0, 0}; // screen size
	int                 playing = 1;
	int                 selected_btn = 1;
	struct snake_pos_t *snake_previous_end = NULL;
	int                 counter_snake_mouving;

	if (getTermSize(size) == _YG_FAIL_GET_SCREEN_SIZE_)
		exitCodeWithError("Fail to get screen size", _YG_FAIL_GET_SCREEN_SIZE_);

	srand((unsigned int)time((time_t *)NULL));

	printf("\e[1;1H\e[2J"); // clear la fenetre
	printf("\e[?25l");
	/* Interaction avec la page d'accueil */
	enableRawMenuTerminal();
	do {
		// afficher la page d'accueil
		drawMainMenu(size[X], selected_btn);
		selected_btn = getMenuChangeBtn(selected_btn);
		if ((selected_btn & 0x04) == 0x04) playing = 0;
	} while(playing);

	/* quitter le programme si le bouton quitter est selectionne */
	if ((selected_btn & 0x03) == 0x02) {
		changeScreenPos(size[X], size[Y]-1);
		return _YG_SUCCESS_;
	}

	/*
	*** DEBUT DE LA PARTIE :
	***  a cette etapes la selection du  boutton play
	***  a etais effectue nous pouvons donc commencer
	***  la premiere partie
	*/

	enableRawPlayTerminal(); // change le mode raw du terminal
	/* permet d'initialiser la structure du snack */
	initSnake();
	generateApple(size[X], size[Y]);
	drawMainGameScreen(size); // affichage du plateau de jeu avec une animation
	drawApple(apple.pos_x, apple.pos_y);
	drawSnack(&snake); // afficher le snack

	playing = 1;
	counter_snake_mouving = 0;
	while (playing) {
		/* pour controller l'horloge, le delay permet d'avoir un controlle */
		/* sur le delay du deplacement du snake toute les 100 ms et garder */
		/* toute les 0.5 ms recuperer les touches entrer par l'utilisateur */
		usleep(_YG_DELAY_PLAY_);

		/*
		*** zone de deplacement du snake lors que le compter de temps
		*** atteint les 150 ms
		*/
		if (counter_snake_mouving >= _YG_COUNTER_MOVE_SNAKE_) {
			
			if (checkLivingSnack(size)) {
				playing = -1;
				break;
			}

			// deplacement du snake en memoire
			snake_previous_end = moveSnake();

			// changement de l'affichage du snake
			deleteSnakeEnd(snake_previous_end->pos_x, snake_previous_end->pos_y);
			moveSnakeHead(snake.snake_position_begin->pos_x, snake.snake_position_begin->pos_y);

			free(snake_previous_end);
			
			counter_snake_mouving = 0;
		}

		/*
		*** interception des actions de l'utilisateur, comme les fleches
		*** directive, echape pour stopper la partie
		*/
		selected_btn = readPlayingInput();
		if (selected_btn != _YG_NO_TOUCHE_ && selected_btn != _YG_ESCAPE_KEY_) {
			changeSnakeDirection(selected_btn);
		}
		if (selected_btn == _YG_ESCAPE_KEY_) playing = 0;

		counter_snake_mouving++;
	}

	/*
	*** Afficher la page de fin de la partie
	*/
	if (playing == -1) {
		drawGameOverScree(size[X], size[Y]);
	}

	/*
	*** FIN D'EXECUTION :
	***  lors de la fin de partie, il faut supprimer la structure
	***  du snake, desactive le mode raw du terminal
	*/
	disableRawMenuTerminal();
	changeScreenPos(size[X], size[Y]-1);
	destroySnake();

	return _YG_SUCCESS_;
}
