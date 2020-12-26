#include "affichage.h"
#include "manipulation.h"
#include "type.h"
#include <MLV/MLV_all.h>
#include <stdio.h>

void afficher(Position *pos){
	int i, j;
	int temp_x, temp_y;

	temp_x = LARGEUR / N;
	temp_y = HAUTEUR / M;

	MLV_draw_filled_rectangle(0, 0, LARGEUR, HAUTEUR, MLV_COLOR_DARKORANGE4);

	for(i = 0; i < M; i++){
		for(j = 0; j < N; j++){
			if(pos->t.tab[j][i] == 1){
				MLV_draw_rectangle(j * temp_x, i * temp_y, temp_x, temp_y, MLV_COLOR_BLACK);
			}
			else{
				MLV_draw_filled_rectangle(j * temp_x, i * temp_y, temp_x, temp_y, MLV_COLOR_BLACK);
			}
			MLV_actualise_window();
		}
	}
	MLV_actualise_window();
}

void affiche_position(Position *pos){
	afficher(pos);
	if(pos->J == JOUEUR_A){
		MLV_draw_adapted_text_box(500, 520, "JOUEUR_A", 20, MLV_COLOR_RED,MLV_COLOR_BLACK , MLV_COLOR_RED, MLV_TEXT_CENTER);
	}
	else{
		MLV_draw_adapted_text_box(500, 520, "JOUEUR_B", 20, MLV_COLOR_RED,MLV_COLOR_BLACK , MLV_COLOR_RED, MLV_TEXT_CENTER);
	}
	MLV_actualise_window();
	MLV_wait_seconds(1);
	afficher(pos);
}

Coup lire_coup(Position *pos){
	int x, y;
	int temp;
	Coup res;
	MLV_wait_mouse(&x, &y);
	res.y = y / (HAUTEUR / M);
	res.x = x / (LARGEUR / N);
	temp = est_legal(pos, &res);
	while(temp == MANGE){
		printf("déjà mangé\n");
		MLV_wait_mouse(&x, &y);
		res.y = y / (HAUTEUR / M);
		res.x = x / (LARGEUR / N);
		temp = est_legal(pos, &res);
	}
	return res;
}

Joueur joueur_gagnant(Position *pos){
	int fin=est_jeu_termine(pos,&(pos->J));
	if(fin ==1){
		if(pos->J == JOUEUR_A){
			MLV_draw_adapted_text_box(500, 520, "JOUEUR_A a gagné", 20, MLV_COLOR_RED,MLV_COLOR_BLACK , MLV_COLOR_RED, MLV_TEXT_CENTER);
			return JOUEUR_B;
		}
		else{
			MLV_draw_adapted_text_box(500, 520, "JOUEUR_B a gagné", 20, MLV_COLOR_RED,MLV_COLOR_BLACK , MLV_COLOR_RED, MLV_TEXT_CENTER);
			return JOUEUR_A;
			}
	}
	return 0 ;
MLV_actualise_window();
}


void affiche_phrase(int n, char chaine[],int Y){
	int x, y;
	char chaine2[10];
	sprintf(chaine2, "%d", n);
	strcat(chaine, chaine2);
	MLV_get_size_of_text(chaine, &x, &y);
	MLV_draw_text((800 - x)/2, Y, chaine, MLV_COLOR_WHITE);
	MLV_actualise_window();
}

void affiche_Partie(int n){
	char c[20] = "Partie n°";
	affiche_phrase(n, c,570);
}



void affiche_joueur_gagnant(int a ,int b){
	char J1[20] = "Joueur A :";
	char J2[20] = "Joueur B :";
	affiche_phrase(a,J1,11);
	affiche_phrase(b,J2,50);
	if(a>b){
		MLV_draw_adapted_text_box(500, 520, "JOUEUR_A a gagné", 20, MLV_COLOR_RED,MLV_COLOR_BLACK , MLV_COLOR_RED, MLV_TEXT_CENTER);	
	}
	else if(a<b){
		MLV_draw_adapted_text_box(500, 520, "JOUEUR_B a gagné", 20, MLV_COLOR_RED,MLV_COLOR_BLACK , MLV_COLOR_RED, MLV_TEXT_CENTER);
	}	
	else{
		MLV_draw_adapted_text_box(500, 520, "Match est nul", 20, MLV_COLOR_RED,MLV_COLOR_BLACK , MLV_COLOR_RED, MLV_TEXT_CENTER);
	}
	MLV_actualise_window();
}
