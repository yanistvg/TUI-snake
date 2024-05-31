#include "../headers/draws.h"

char logo[11][54] = {
	"=====================================================\0",
	"==      ===  =======  =====  =====  ====  ==        =\0",
	"=  ====  ==   ======  ====    ====  ===  ===  =======\0",
	"=  ====  ==    =====  ===  ==  ===  ==  ====  =======\0",
	"==  =======  ==  ===  ==  ====  ==  =  =====  =======\0",
	"====  =====  ===  ==  ==  ====  ==     =====      ===\0",
	"======  ===  ====  =  ==        ==  ==  ====  =======\0",
	"=  ====  ==  =====    ==  ====  ==  ===  ===  =======\0",
	"=  ====  ==  ======   ==  ====  ==  ====  ==  =======\0",
	"==      ===  =======  ==  ====  ==  ====  ==        =\0",
	"=====================================================\0"
};

char bouton_play[8][200] = {
	"┌———————————————————————————————————————————————————————┐\0",
	"│         ██████╗ ██╗      █████╗ ██╗   ██╗             │\0",
	"│         ██╔══██╗██║     ██╔══██╗╚██╗ ██╔╝             │\0",
	"│         ██████╔╝██║     ███████║ ╚████╔╝              │\0",
	"│         ██╔═══╝ ██║     ██╔══██║  ╚██╔╝               │\0",
	"│         ██║     ███████╗██║  ██║   ██║                │\0",
	"│         ╚═╝     ╚══════╝╚═╝  ╚═╝   ╚═╝                │\0",
	"└———————————————————————————————————————————————————————┘\0"
};

char bouton_quit[8][200] = {
	"┌———————————————————————————————————————————————————————┐\0",
	"│ ██████╗ ██╗   ██╗██╗████████╗████████╗███████╗██████╗ │\0",
	"│██╔═══██╗██║   ██║██║╚══██╔══╝╚══██╔══╝██╔════╝██╔══██╗│\0",
	"│██║   ██║██║   ██║██║   ██║      ██║   █████╗  ██████╔╝│\0",
	"│██║▄▄ ██║██║   ██║██║   ██║      ██║   ██╔══╝  ██╔══██╗│\0",
	"│╚██████╔╝╚██████╔╝██║   ██║      ██║   ███████╗██║  ██║│\0",
	"│ ╚══▀▀═╝  ╚═════╝ ╚═╝   ╚═╝      ╚═╝   ╚══════╝╚═╝  ╚═╝│\0",
	"└———————————————————————————————————————————————————————┘\0"
};

char game_over[19][90] = {
	"  /$$$$$$   /$$$$$$  /$$      /$$ /$$$$$$$$\0",
	" /$$__  $$ /$$__  $$| $$$    /$$$| $$_____/\0",
	"| $$  \\__/| $$  \\ $$| $$$$  /$$$$| $$      \0",
	"| $$ /$$$$| $$$$$$$$| $$ $$/$$ $$| $$$$$   \0",
	"| $$|_  $$| $$__  $$| $$  $$$| $$| $$__/   \0",
	"| $$  \\ $$| $$  | $$| $$\\  $ | $$| $$      \0",
	"|  $$$$$$/| $$  | $$| $$ \\/  | $$| $$$$$$$$\0",
	" \\______/ |__/  |__/|__/     |__/|________/\0",
	"                                           \0",
	"                                           \0",
	"                                           \0",
	"  /$$$$$$  /$$    /$$ /$$$$$$$$ /$$$$$$$   \0",
	" /$$__  $$| $$   | $$| $$_____/| $$__  $$  \0",
	"| $$  \\ $$| $$   | $$| $$      | $$  \\ $$  \0",
	"| $$  | $$|  $$ / $$/| $$$$$   | $$$$$$$/  \0",
	"| $$  | $$ \\  $$ $$/ | $$__/   | $$__  $$  \0",
	"| $$  | $$  \\  $$$/  | $$      | $$  \\ $$  \0",
	"|  $$$$$$/   \\  $/   | $$$$$$$$| $$  | $$  \0",
	" \\______/     \\_/    |________/|__/  |__/  \0"
};

/**
 * drawMainGameScreen permet de faire l'affichage en animation de la mise
 * en place de la grille de jeu
 * 
 * @param size table de deux entier qui contient la taille du terminal
 * 
 * @return none
 * 
 * @date 2024-05-30
*/
void drawMainGameScreen(const int size[2]) {
	register int i = 2;

	printf("\e[1;1H\e[2J");
	drawSnakeTitle(size[X], size[Y]);
	drawScore(0);
	changeScreenPos(1, 2);
	
	/* affichage de la bordure superieur de jeu */
	drawBordureLine(size[X]);
	usleep(ANIMATION_DELAY);

	/* affichage des bordure lateraux */
	while(++i < size[Y]-1) {
		changeScreenPos(1, i);
		printf("%s  ", FONT_GREY);
		changeScreenPos(size[X]-1, i);
		printf("  %s", DEFAULT_COLOR);
		usleep(ANIMATION_DELAY);
	}
	/* affichage de la bordure de fin */
	changeScreenPos(1, size[Y]-1);
	drawBordureLine(size[X]);
	clearLogoTitle(size[X], size[Y]);
}

/**
 * drawScore permet d'afficher le score de la partie
 * 
 * @param score score a afficher
 * 
 * @return none
 * 
 * @date 2024-05-31
*/
void drawScore(int score) {
	changeScreenPos(1, 1);
	printf("%sscore : %s%d%s", TEXT_GREEN, TEXT_CYAN, score, DEFAULT_COLOR);
}

/**
 * drawBordureLine permet d'afficher une ligne de bordure pour le snake. cette ligne
 * est presente en haut et en bas de la grille. l'affichage par default se fait en
 * gris pour la ligne
 * 
 * @param size_x taille d'une ligne pour les x
 * 
 * @return none
 * 
 * @date 2024-05-30
*/
void drawBordureLine(const int size_x) {
	char line[size_x+1];

	line[size_x] = 0;
	memset(line, ' ', (size_t)size_x);
	printf("%s%s%s\n", FONT_GREY, line, DEFAULT_COLOR);
}

/**
 * permet de changer la position x et y sur l'ecrant
 * 
 * @param pos_x position x
 * @param pos_y position y
 * 
 * @return none
 * 
 * @date 2024-05-30
*/
void changeScreenPos(const int pos_x, const int pos_y) {
	printf("\e[%d;%dH", pos_y, pos_x);
	fflush(stdout);
}

/**
 * drawSnakeTitle permet d'afficher le logo snake au centre de la fenetre du terminal
 * 
 * @param size_x dimention de la fenetre en x
 * @param size_y dimention de la fenetre en y
 * 
 * @return none
 * 
 * @date 2024-05-30
*/
void drawSnakeTitle(const int size_x, const int size_y) {
	int pos_x = (size_x - 53) / 2;
	int pos_y = (size_y - 11) / 2 + 1;
	register int i = -1;

	printf("%s", TEXT_RED);
	while (++i < 11) {
		changeScreenPos(pos_x, pos_y + i);
		printf("%s", logo[i]);
	}
	printf("%s", DEFAULT_COLOR);
	fflush(stdout);
}

/**
 * clearLogoTitle permet de supprimer l'affichage du logo au meme emplacement
 * que sont ecriture
 * 
 * @param size_x dimention de la fenetre en x
 * @param size_y dimention de la fenetre en y
 * 
 * @return none
 * 
 * @date 2024-05-30
*/
void clearLogoTitle(const int size_x, const int size_y) {
	register int i = -1;
	int pos_x = (size_x - 53) / 2;
	int pos_y = (size_y - 11) / 2 + 1;
	char line[54];
	
	line[53] = 0;
	memset(line, ' ', (size_t)53);

	printf("%s", DEFAULT_COLOR);
	while (++i < 11) {
		changeScreenPos(pos_x, pos_y + i);
		printf("%s", line);
	}
	fflush(stdout);
}

/**
 * drawSnack permet d'afficher le snack sur la grille de jeu
 * 
 * @param snake poiteur sur la structure du snack
 * 
 * @return none
 * 
 * @date 2024-05-30
*/
void drawSnack(const struct snake_t *snake) {
	struct snake_pos_t *snake_pos = snake->snake_position_begin;

	printf("%s", FONT_PURPLE);
	while (snake_pos != NULL) {
		changeScreenPos(2*snake_pos->pos_x-1, snake_pos->pos_y);
		printf("  ");
		snake_pos = snake_pos->next;
	}
	printf("%s", DEFAULT_COLOR);
	fflush(stdout);
}

/**
 * drawMainMenu permet l'affichage du menu principale du jeu avec le logo et deux bouton
 * pour pouvoir jouer
 * 
 * @param size_x dimention de la fenetre en x
 * @param new_btn boutton selectionne (0 -> play, 1 -> quitter)
 * 
 * @return le numero du bouton selectionne (qui a subit un changement d'affichage)
 * 
 * @date 2024-05-30
*/
int drawMainMenu(const int size_x, const int new_btn) {
	/* Affichage du logo si c'est la premier fois */
	drawMainLogo(size_x);
	/* Affichage du bouton play */
	drawPlayBtn(size_x, new_btn == 1);
	/* Affichage du bouton quitter */
	drawQuitteBtn(size_x, new_btn == 2);

	fflush(stdout);

	return new_btn;
}

/**
 * drawMainLogo permet d'afficher le logo pour pour la page d'accueil
 * 
 * @param size_x dimention de la fenetre en x
 * 
 * @return none
 * 
 * @date 2024-05-30
*/
void drawMainLogo(const int size_x) {
	register int i = -1;
	int pos_x = (size_x - 53) / 2;
	int pos_y = 3;

	printf("%s", TEXT_RED); // set la couleur du logo
	while (++i < 11) {
		changeScreenPos(pos_x, pos_y+i);
		printf("%s", logo[i]);
	}
	printf("%s", DEFAULT_COLOR);
}

/**
 * drawPlayBtn permet d'afficher le boutton play pour la page d'accueil
 * 
 * @param size_x dimention de la fenetre en x
 * @param selected determine si le bouton est selectionne
 * 
 * @return none
 * 
 * @date 2024-05-30
*/
void drawPlayBtn(const int size_x, const int selected) {
	register int i = -1;
	int pos_x = (size_x - 57) / 2;
	int pos_y = 19;

	if (selected) printf("\033[30;47m");
	else printf("%s", DEFAULT_COLOR);
	while (++i < 8) {
		changeScreenPos(pos_x, pos_y+i);
		printf("%s", bouton_play[i]);
	}
	printf("%s", DEFAULT_COLOR);
}

/**
 * drawQuitteBtn permet d'afficher le boutton quitter pour la page d'accueil
 * 
 * @param size_x dimention de la fenetre en x
 * @param selected determine si le bouton est selectionne
 * 
 * @return none
 * 
 * @date 2024-05-30
*/
void drawQuitteBtn(const int size_x, const int selected) {
	register int i = -1;
	int pos_x = (size_x - 57) / 2;
	int pos_y = 28;

	if (selected) printf("\033[30;47m");
	else printf("%s", DEFAULT_COLOR);
	while (++i < 8) {
		changeScreenPos(pos_x, pos_y+i);
		printf("%s", bouton_quit[i]);
	}
	printf("%s", DEFAULT_COLOR);
}

/**
 * deleteSnakeEnd permet de supprimer une case sur l'affichage par une
 * position x et y, utilise pour supprimer la derniere case du snake
 * 
 * @param pos_x position x de la case
 * @param pos_y position y de la case
 * 
 * @return none
 * 
 * @date 2024-05-30
*/
void deleteSnakeEnd(const int pos_x, const int pos_y) {
	changeScreenPos(2*pos_x-1, pos_y);
	printf("%s  ", DEFAULT_COLOR);
	fflush(stdout);
}

/**
 * deleteSnakeEnd permet d'ajouter une case sur l'affichage par une
 * position x et y, utilise pour modifier la tete du snake
 * 
 * @param pos_x position x de la case
 * @param pos_y position y de la case
 * 
 * @return none
 * 
 * @date 2024-05-30
*/
void moveSnakeHead(const int pos_x, const int pos_y) {
	changeScreenPos(2*pos_x-1, pos_y);
	printf("%s  %s", FONT_PURPLE, DEFAULT_COLOR);
	fflush(stdout);
}

/**
 * drawGameOverScree permet d'afficher le message game over
 * lorsque la partie est fini en perdant comme un looser
 * 
 * @param size_x dimention de la fentre pour les x
 * @param size_y dimention de la fentre pour les y
 * 
 * @return none
 * 
 * @date 2024-05-30
*/
void drawGameOverScree(const int size_x, const int size_y) {
	int pos_y = size_y / 2 - 9;
	int pos_x = size_x / 2 - 22;
	register int i = 0;

	changeScreenPos(pos_x, pos_y);

	i = 0;
	while (++i <= 19) {
		printf("%s%s%s", TEXT_RED, game_over[i - 1], DEFAULT_COLOR);
		changeScreenPos(pos_x, pos_y + i);
	}
	fflush(stdout);
}

/**
 * drawApple permet d'afficher la pomme dans la grille de jeu
 * 
 * @param pos_x position en x de la pomme
 * @param pos_y position en y de la pomme
 * 
 * @return none
 * 
 * @date 2024-05-30
*/
void drawApple(const int pos_x, const int pos_y) {
	changeScreenPos(2*pos_x-1, pos_y);
	printf("%s %s", FONT_RED, DEFAULT_COLOR);
}
