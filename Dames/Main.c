#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "MLV.h"
#define X 8 * 50
#define Y 8 * 50

int main(int argc, char *argv[]) {
	
	Position pos = 0;
	Position tmp = pos;
	Case c;
	int x, y;
	int nb_dames = 0;
	int i;

	for (i = 0, c = 0; i < 64; i++, c++) {
		tab_cases_attaquees[i] = pos;
		calculer_cases_attaquees(&tab_cases_attaquees[c], c);
	}

	MLV_create_window("Dames", "", X, Y);
	afficher_position_MLV(pos);

	while (nb_dames < 8) {
		case_selectionnee(&x, &y, &c);
		placer_dans_position(&tmp, c);
		if (est_sans_attaque_mutuelle(tmp) == 1) {
			placer_dans_position(&pos, c);
			afficher_position_MLV(pos);
			nb_dames++;
		}
		else {
			MLV_clear_window(MLV_COLOR_BLACK);
			MLV_draw_text(X / 2 - 50, Y / 2, "placement interdit!", MLV_COLOR_SNOW);
			MLV_actualise_window();
			MLV_wait_milliseconds(750);
			MLV_clear_window(MLV_COLOR_BLACK);
			afficher_position_MLV(pos);			
		}
		tmp = pos;
	}
	MLV_clear_window(MLV_COLOR_BLACK);
	MLV_draw_text(X / 2 - 15, Y / 2 - 25, "gagné!", MLV_COLOR_SNOW);
	MLV_actualise_window();
	MLV_wait_mouse(&x, &y);
	MLV_free_window();

	return 0;
}
