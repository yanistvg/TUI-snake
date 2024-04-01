#include "./libs/headers/main.h"

int main(int argc, char **argv) {
	int size[2] = {0, 0}; // screen size
	int playing = 1;
	int selected_btn = 1;
	struct snake_pos_t *snake_previous_end = NULL;

	if (getTermSize(size) == _YG_FAIL_GET_SCREEN_SIZE_)
		exitCodeWithError("Fail to get screen size", _YG_FAIL_GET_SCREEN_SIZE_);

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
	disableRawMenuTerminal();

	/*
	*** DEBUT DE LA PARTIE :
	***  a cette etapes la selection du boutton play
	***  a etais effectue nous pouvons donc commencer
	***  la premiere partie
	*/

	/* permet d'initialiser la structure du snack */
	initSnake();
	drawMainGameScreen(size); // affichage du plateau de jeu avec une animation
	drawSnack(&snake); // afficher le snack

	playing = 1;
	while (playing < 50) {
		usleep(60000);
		snake_previous_end = moveSnake();
		deleteSnakeEnd(snake_previous_end->pos_x, snake_previous_end->pos_y);
		free(snake_previous_end);
		drawSnack(&snake);
		playing++;
	}


	/* avant de stoper le programme, placer le curseur a la fin */
	disableRawMenuTerminal();
	changeScreenPos(size[X], size[Y]-1);
	destroySnake();

	return _YG_SUCCESS_;
}
