#include "../headers/terminal-interact.h"

/*
*** getTermSize permet d'obtenir la taille de l'ecrant du terminal (nombre de ligne
*** et nombre de colonne) affecte a un tableau sous format X Y
***
*** input :
***   int [2] -> tableau de deux elements pour enregistrer la taille
***
*** output:
***   _YG_FAIL_GET_SCREEN_SIZE_ -> si erreur lors de la recpetion de la taille
***   _YG_SUCESS_               -> si pas d'erreur
*/
int getTermSize(int size[2]) {
	struct winsize w;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) < 0) return _YG_FAIL_GET_SCREEN_SIZE_;
	size[X] = w.ws_col;
	size[Y] = w.ws_row;
	return _YG_SUCCESS_;
}

/*
*** stopper le programme lors qu'une erreur est survenue en affichant un petit
*** message d'erreur
***
*** input :
***    - char * -> message de l'erreur
***    - int    -> valeur de l'erreur
***
*** output: none
*/
void exitCodeWithError(char *error, int errorValue) {
	printf("**ERROR: %s\n", error);
	exit(errorValue);
}
