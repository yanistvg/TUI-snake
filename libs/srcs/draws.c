#include "../headers/draws.h"

char logo[11][54] = {
	"=====================================================",
	"==      ===  =======  =====  =====  ====  ==        =",
	"=  ====  ==   ======  ====    ====  ===  ===  =======",
	"=  ====  ==    =====  ===  ==  ===  ==  ====  =======",
	"==  =======  ==  ===  ==  ====  ==  =  =====  =======",
	"====  =====  ===  ==  ==  ====  ==     =====      ===",
	"======  ===  ====  =  ==        ==  ==  ====  =======",
	"=  ====  ==  =====    ==  ====  ==  ===  ===  =======",
	"=  ====  ==  ======   ==  ====  ==  ====  ==  =======",
	"==      ===  =======  ==  ====  ==  ====  ==        =",
	"====================================================="
};

/*
*** drawMainGameScreen permet de faire l'affichage en animation de la mise
*** en place de la grille de jeu
***
*** input :
***   int [2] -> taille de la fenetre du terminal
***
*** output: none
*/
void drawMainGameScreen(int size[2]) {
	register int i = 2;

	printf("\e[1;1H\e[2J");
	drawSnakeTitle(size[X], size[Y]);
	changeScreenPos(1, 1);
	printf("%sscore : %s0%s\n", TEXT_GREEN, TEXT_CYAN, DEFAULT_COLOR);
	
	/* affichage de la bordure superieur de jeu */
	drawBordureLine(size[X]);
	usleep(50000);

	/* affichage des bordure lateraux */
	while(++i < size[Y]-1) {
		changeScreenPos(1, i);
		printf("%s ", FONT_GREY);
		changeScreenPos(size[X], i);
		printf(" %s", DEFAULT_COLOR);
		usleep(50000);
	}
	/* affichage de la bordure de fin */
	changeScreenPos(1, size[Y]-1);
	drawBordureLine(size[X]);
	clearLogoTitle(size[X], size[Y]);
}

/*
*** drawBordureLine permet d'afficher une ligne de bordure pour le snake. cette ligne
*** est presente en haut et en bas de la grille. l'affichage par default se fait en
*** gris pour la ligne
***
*** input :
***    int -> taille d'une ligne pour les x
***
*** output: none
*/
void drawBordureLine(int size_x) {
	char line[size_x+1];

	line[size_x] = 0;
	memset(line, ' ', (size_t)size_x);
	printf("%s%s%s\n", FONT_GREY, line, DEFAULT_COLOR);
}

/*
*** permet de changer la position x et y sur l'ecrant
***
*** input :
***   int -> position x
***   int -> position y
***
*** output: none
*/
void changeScreenPos(int pos_x, int pos_y) {
	printf("\e[%d;%dH", pos_y, pos_x);
	fflush(stdout);
}

/*
*** drawSnakeTitle permet d'afficher le logo snake au centre de la fenetre du terminal
***
*** input :
***    int -> dimention de la fenetre en x
***    int -> dimention de la fenetre en y
***
*** output: none
*/
void drawSnakeTitle(int size_x, int size_y) {
	int pos_x = (size_x - 53) / 2;
	int pos_y = (size_y - 11) / 2 + 1;
	register int i = -1;

	printf("%s", TEXT_RED);
	while (++i < 11) {
		changeScreenPos(pos_x, pos_y + i);
		printf("%s", logo[i]);
	}
	printf("%s", DEFAULT_COLOR);
}

/*
*** clearLogoTitle permet de supprimer l'affichage du logo au meme emplacement
*** que sont ecriture
***
*** input :
***    int -> dimention de la fenetre en x
***    int -> dimention de la fenetre en y
***
*** output: none
*/
void clearLogoTitle(int size_x, int size_y) {
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
	changeScreenPos(size_x, size_y-1);
}
