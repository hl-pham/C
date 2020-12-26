#include <stdio.h>
#include "Case.h"
#define MIN(a, b) ((a) <= (b) ? (a): (b))

int est_case_occupee(Position pos, Case c) {
	if ((pos & (1uLL << c)) == 0) {
		return 0;
	}
	return 1;
}

int placer_dans_position(Position *pos, Case c) {
	if (est_case_occupee(*pos, c) == 1) {
		return 0;
	}
	else {
		*pos = *pos | (1uLL << c);
		return 1;
	}
}

int afficher_position(Position pos) {
	int i;

	for (i = 63; i >= 0; i--) {
		if (i % 8 == 7) {
			printf("\n");
		}
		if (((pos >> i) & 1) == 1) {
			printf("+ ");
		}
		else {
			printf(". ");
		}
	}
	printf("\n\n");
	return 1;
}

int calculer_cases_attaquees(Position *pos, Case c) {
	int i;
	int j;

	/* HORIZONTALE */
	for (i = 8 * (c / 8); i < 8 * (c / 8 + 1); i++) {
		*pos = *pos | (1uLL << i);
	}

	/* VERTICALE */
	for (i = c % 8, j = 0; j < 8; i += 8, j++) {
		*pos = *pos | (1uLL << i);
	}

	/* DIAGONALES: NORD-EST / NORD-OUEST / SUD-OUEST / SUD-EST*/

	for (i = c, j = 0; j <= MIN((c % 8), (8 - c / 8)); i += 7, j++) {
		if (i > 63) {
			break;
		}
		else {
			*pos = *pos | (1uLL << i);
		}
	}

	for (i = c, j = 0; j < MIN((8 - c % 8), (8 - c / 8)); i += 9, j++) {
		if (i > 63) {
			break;
		}
		else {
			*pos = *pos | (1uLL << i);
		}
	}

	for (i = c, j = 0; j <= MIN((7 - c % 8), (c / 8)); i -= 7, j++) {
		if (i > 63) {
			break;
		}
		else {
			*pos = *pos | (1uLL << i);
		}
	}

	for (i = c, j = 0; j <= MIN((c % 8), (c / 8)); i -= 9, j++) {
		if (i > 63) {
			break;
		}
		else {
			*pos = *pos | (1uLL << i);
		}
	}
	return 1;
}

int est_sans_attaque_mutuelle(Position pos) {
	Position attaques = 0;
	Case c;
	int i;

	for (i = 0, c = 0; i < 64; i++, c++) {
		if ((pos & (1uLL << i)) != 0) {
			if ((attaques & (1uLL << i)) == 0) {
				calculer_cases_attaquees(&attaques, c);
			}
			else {
				return 0;
			}
		}
	}
	return 1;
}