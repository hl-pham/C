#include <stdio.h>
#include "type.h"
#include "affichage.c"
#include "manipulation.c"
#include <MLV/MLV_all.h>
#include "affichage.h"
#include "manipulation.h"
#include <time.h>

int main(int argc, char *argv[]){
	srand(time(NULL));
	int cpt=1;
	Position pos;
	Coup test;
	int fin;
	int nb_de_match;
	int a, b;
	int J1 = 0;
	int J2 = 0;
	/*Nombre de parties*/
	do{
		printf("nombre de match pour J1\n");
			scanf("%d", &a);
	}while(a <= 0);
	do{
		printf("nombre de match pour J2\n");
			scanf("%d", &b);
	}while(b <= 0);
	
	MLV_create_window( "tp2", "tp2", 700, 600);
	nb_de_match = moyenne(a, b);
	printf("%d\n",nb_de_match);
	for(int i = 0; i < nb_de_match; i++){
		pos.t = creer_tablette();
		pos.J = JOUEUR_A;
		show_tab(pos.t);
		affiche_position(&pos);
		affiche_Partie(cpt);
		while(1){
			test = lire_coup(&pos);
			manger(&pos.t, test.x, test.y);
			fin = est_jeu_termine(&pos, &pos.J);
			if(fin == 1){
				joueur_gagnant(&pos);
				score(&J1,&J2,pos);
				MLV_actualise_window();
				MLV_wait_seconds( 1);
				MLV_clear_window(MLV_COLOR_BLACK);
				MLV_actualise_window();
				break;
			}
			jouer_coup(&pos, &test);
			affiche_position(&pos);
			MLV_actualise_window();
		}
		cpt++;
		MLV_actualise_window();
	

	}
	MLV_clear_window(MLV_COLOR_BLACK);
	MLV_actualise_window();

	affiche_joueur_gagnant(J1,J2);
	MLV_actualise_window();
	MLV_wait_seconds(10);
	MLV_free_window();

	return 0;

}
