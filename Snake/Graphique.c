#include <assert.h>
#include <MLV/MLV_all.h>

#include "Graphique.h"

void afficher_quadrillage(Monde *mon){
	int i, j;
	assert(mon != NULL);
	for(i = 0; i < N; i++){
		for(j = 0; j < M; j++){
			if((i%2 == 0 && j%2 == 0) || (i%2 == 1 && j%2 == 1))
				MLV_draw_filled_rectangle(15 + j*TAILLE_CARRE, 70 +  i*TAILLE_CARRE, TAILLE_CARRE, TAILLE_CARRE, MLV_COLOR_CHARTREUSE1);
			else
				MLV_draw_filled_rectangle(15 + j*TAILLE_CARRE, 70 +  i*TAILLE_CARRE, TAILLE_CARRE, TAILLE_CARRE, MLV_COLOR_CHARTREUSE3);
		}
	}
}

void afficher_pomme(Pomme *pom){
	assert(pom != NULL);
	MLV_draw_filled_circle(15 + pom->x * TAILLE_CARRE + TAILLE_CARRE/2, 
		70 + pom->y * TAILLE_CARRE + TAILLE_CARRE/2, TAILLE_CARRE/3, MLV_COLOR_RED);
}

void afficher_serpent(Serpent *ser){
	int i;
	assert(ser != NULL);
	MLV_draw_filled_circle(15 + ser->tab[0].x * TAILLE_CARRE + TAILLE_CARRE/2, 
		70 + ser->tab[0].y * TAILLE_CARRE + TAILLE_CARRE/2, TAILLE_CARRE/3, MLV_COLOR_BLACK);
	for(i = 1; i < ser->taille; i++)
		MLV_draw_filled_rectangle(15 + ser->tab[i].x * TAILLE_CARRE + 5, 
			70 + ser->tab[i].y * TAILLE_CARRE + 5, TAILLE_CARRE - 10, TAILLE_CARRE -10, MLV_COLOR_BLUE);
}

void afficher_monde(Monde *mon){
	int i;
	char phrase[40] = "Nombre de pommes mangées : ", pomme[4];
	assert(mon != NULL);
	sprintf(pomme, "%d", mon->nb_pommes_mangees);
	strcat(phrase, pomme);
	afficher_quadrillage(mon);
	for(i = 0; i < NB_POMMES; i++)
		afficher_pomme(&(mon->pommes[i]));
	afficher_serpent(&(mon->s));
	MLV_draw_text(LARGEUR/2 - 100, 30, phrase, MLV_COLOR_RED);
	MLV_actualise_window();
}