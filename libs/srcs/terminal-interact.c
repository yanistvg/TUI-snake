#include "../headers/terminal-interact.h"

struct termios default_terminal;

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
void exitCodeWithError(const char *error, const int errorValue) {
	printf("**ERROR: %s\n", error);
	exit(errorValue);
}

/*
*** enableRawMenuTerminal permet de rendre le terminal dans un mode
*** pour le menu, c'est a dire que le terminal est bloquant mais
*** n'affiche pas les touches, et prend en compte les touches controles.
*** Une fonction de fin est aussi ajoute pour remettre le terminal comme
*** d'origine
***
*** input : none
***
*** output: none
*/
void enableRawMenuTerminal() {
	tcgetattr(STDIN_FILENO, &default_terminal);
	atexit(disableRawMenuTerminal);
	struct termios raw = default_terminal;

	raw.c_lflag &= (tcflag_t)~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

/*
*** disableRawMenuTerminal permet de remettre le terminal comme d'origine
***
*** input : none
***
*** output: none
*/
void disableRawMenuTerminal() {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &default_terminal);
	printf("\033[0;m\e[?25h");
}

/*
*** getMenuChangeBtn permet avec le mode raw active pour le menu de determiner
*** la selection de touche utilisable comme la fleche du haut et du bas pour
*** determiner la touche qui est selectionne
***
*** input :
***    int -> valeur correspondant au boutton selectionne
***
*** output:
***    int -> nouvelle valeur du bouton choisie avec la detection de la validation
*/
int getMenuChangeBtn(int selected_btn) {
	char c;
	int wait = 1;

	do {
		read(STDIN_FILENO, &c, 1);
		if (c == 27) {
			read(STDIN_FILENO, &c, 1);
			if (c == 91) {
				read(STDIN_FILENO, &c, 1);
				if (c == 65) {
					selected_btn--;
					wait = 0;
				}
				if (c == 66) {
					selected_btn++;
					wait = 0;
				}
			}
		}
		if (c == 10) {
			selected_btn |= 0x04;
			return selected_btn;
		}
	} while(wait);

	if (selected_btn < 1) selected_btn = 2;
	if (selected_btn > 2) selected_btn = 1;

	return selected_btn;
}
