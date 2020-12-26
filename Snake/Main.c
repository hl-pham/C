#include <MLV/MLV_all.h>
#include <stdlib.h>
#include <time.h>


#include "Graphique.h"


int main(){
	Monde mon;
	MLV_Keyboard_button touche;
	MLV_Button_state etat;
	char phrase[12] = "Score : ", pomme[4];
	srand(time(NULL));
	MLV_create_window("Snake", "", LARGEUR, HAUTEUR);
	mon = init_monde(NB_POMMES);
	afficher_monde(&mon);
	MLV_wait_keyboard(NULL, NULL, NULL);
	while(1){
		MLV_get_event(&touche, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &etat);
		if (etat == MLV_PRESSED){
			if(touche == MLV_KEYBOARD_UP){
				if(mon.s.dir != SUD)
					mon.s.dir = NORD;
			}
			else if(touche == MLV_KEYBOARD_DOWN){
				if(mon.s.dir != NORD)
					mon.s.dir = SUD;
			}
			else if(touche == MLV_KEYBOARD_LEFT){
				if(mon.s.dir != EST)
					mon.s.dir = OUEST;
			}
			else if(touche == MLV_KEYBOARD_RIGHT){
				if(mon.s.dir != OUEST)
					mon.s.dir = EST;
			}
		}
		if(mort_serpent(&mon))
			break;
		else if(! deplacer_serpent(&mon)){
			if(manger_pomme_serpent(&mon))
				ajouter_pomme_monde(&mon);
		}
		MLV_clear_window(MLV_COLOR_BLACK);
		afficher_monde(&mon);
		MLV_wait_milliseconds(200);
	}
	MLV_clear_window(MLV_COLOR_BLACK);
	sprintf(pomme, "%d", mon.nb_pommes_mangees);
	strcat(phrase, pomme);
	MLV_draw_text(LARGEUR/2 - 50, HAUTEUR/2 - 50, "GAME OVER...", MLV_COLOR_RED);
	MLV_draw_text(LARGEUR/2 - 30, HAUTEUR/2 + 50, phrase, MLV_COLOR_GOLD);
	MLV_actualise_window();
	MLV_wait_seconds(5);
	MLV_free_window();
	return 0;
}