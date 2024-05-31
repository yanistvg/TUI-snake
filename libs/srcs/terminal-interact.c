#include "../headers/terminal-interact.h"

struct termios default_terminal;

/**
 * getTermSize permet d'obtenir la taille de l'ecrant du terminal (nombre de ligne
 * et nombre de colonne) affecte a un tableau sous format X Y
 * 
 * @param size tableau de deux elements pour enregistrer la taille
 * 
 * @returns _YG_FAIL_GET_SCREEN_SIZE_ si erreur lors de la recpetion de la taille
 * @returns _YG_SUCESS_               si pas d'erreur
 * 
 * @date 2024-05-30
*/
int getTermSize(int size[2]) {
	struct winsize w;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) < 0) return _YG_FAIL_GET_SCREEN_SIZE_;
	size[X] = w.ws_col;
	size[Y] = w.ws_row;
	return _YG_SUCCESS_;
}

/**
 * stopper le programme lors qu'une erreur est survenue en affichant un petit
 * message d'erreur
 * 
 * @param error message de l'erreur
 * @param errorValue valeur de l'erreur
 * 
 * @return none
 * 
 * @date 2024-05-30
*/
void exitCodeWithError(const char *error, const int errorValue) {
	printf("**ERROR: %s\n", error);
	exit(errorValue);
}

/**
 * enableRawMenuTerminal permet de rendre le terminal dans un mode
 * pour le menu, c'est a dire que le terminal est bloquant mais
 * n'affiche pas les touches, et prend en compte les touches controles.
 * Une fonction de fin est aussi ajoute pour remettre le terminal comme
 * d'origine
 * 
 * @param
 * 
 * @return none
 * 
 * @date 2024-05-30
*/
void enableRawMenuTerminal(void) {
	tcgetattr(STDIN_FILENO, &default_terminal);
	atexit(disableRawMenuTerminal);
	struct termios raw = default_terminal;

	raw.c_lflag &= (tcflag_t)~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

/**
 * disableRawMenuTerminal permet de remettre le terminal comme d'origine
 * 
 * @param
 * 
 * @return none
 * 
 * @date 2024-05-30
*/
void disableRawMenuTerminal(void) {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &default_terminal);
	printf("\033[0;m\e[?25h");
}

/**
 * getMenuChangeBtn permet avec le mode raw active pour le menu de determiner
 * la selection de touche utilisable comme la fleche du haut et du bas pour
 * determiner la touche qui est selectionne
 * 
 * @param selected_btn valeur correspondant au boutton selectionne
 * 
 * @return nouvelle valeur du bouton choisie avec la detection de la validation
 * 
 * @date 2024-05-30
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

/**
 * enableRawPlayTerminal permet d'activer le mode raw sur le terminal pour pouvoir
 * jouer sans que les appel systeme comme read devienne bloquant, et ne pas
 * afficher les touches entrer par l'utilisateur
 * 
 * @param
 * 
 * @return none
 * 
 * @date 2024-05-30
*/
void enableRawPlayTerminal(void) {
	struct termios raw;

	strncpy((char *)&raw, (const char *)&default_terminal, (size_t)sizeof(struct termios));

	raw.c_lflag &= ~(tcflag_t)(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_iflag &= ~(tcflag_t)(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	atexit(disableRawMenuTerminal);
}

/**
 * readPlayingInput permet de determiner la touche presser par un utilisateur
 * lors d'une partie
 * 
 * @param
 * 
 * @returns _YG_NO_TOUCHE_  si pas de touche presse
 * @returns _YG_ESCAPE_KEY_ si touche echape
 * @returns NORTH           si touche top arrow
 * @returns SOUTH           si touche bottom arrow
 * @returns EAST            si touche left arrow
 * @returns OUEST           si touche right arrow
 * 
 * @date 2024-05-30
*/
int readPlayingInput() {
	char c = 0;

	/*
	*** escape key   : 27
	*** right  arrow : 27 91 67
	*** left   arrow : 27 91 68
	*** top    arrow : 27 91 65
	*** bottom arrow : 27 91 66
	*/

	/* Si une touche est presse */
	if (read(STDIN_FILENO, &c, 1) >= 1) {
		if (c == 27) {
			read(STDIN_FILENO, &c, 1);
			if (c == 91) {
				read(STDIN_FILENO, &c, 1);
				if (c == 65) return NORTH;
				if (c == 66) return SOUTH;
				if (c == 67) return EAST;
				if (c == 68) return OUEST;
			}

			if (c <= 0 || c == 27) return _YG_ESCAPE_KEY_;
		}
	}
	return _YG_NO_TOUCHE_;
}
