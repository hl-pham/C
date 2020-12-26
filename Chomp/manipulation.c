#include "manipulation.h"
#include "type.h"
#include <stdio.h>

Tablette creer_tablette(){/*creation du plateforme du jeux*/
	int i, j;
	Tablette t;
	for(i = 0; i < N; i++){/*parcours d'une grille*/
		for(j = 0; j < M; j++){
			t.tab[i][j] = TRANDIS;/*chaque case existe encore*/
		}
	}
	return t;
}

void show_tab(Tablette t){/*fonction d'affichage*/
	int i, j;
	for(i = 0; i < N; i++){
		for(j = 0; j < M; j++){
			printf("tab[%d][%d] = %d\n", i, j, t.tab[i][j]);
		}
	}
}

void manger(Tablette *t, int x, int y){/*manger tous les case en bas et a droite de la case(x,y)*/
	int temp_y;
	temp_y = y;
	for(; x < N; x++){
		for(temp_y = y; temp_y < M; temp_y++){
			(*t).tab[x][temp_y] = MANGE;/*la case (x,y) recoit la valeur 0 elle va etre supprimé*/
		}
	}
}

int est_legal(Position *pos, Coup *coup){/*verifier si la case du coup est mangé ou pas*/
	if(pos->t.tab[coup->x][coup->y] == 1){
		return TRANDIS;
	}
	return MANGE;
}

int est_jeu_termine(Position *pos, Joueur *joueur_gagnant){/*affichage du joueur gagnant*/
	if(pos->t.tab[0][0] == MANGE){
		if(pos->J == JOUEUR_A){
			*joueur_gagnant = JOUEUR_B;
			printf("JOUEUR_B\n");
		}
		else{
			*joueur_gagnant = JOUEUR_A;
			printf("JOUEUR_A\n");
		}
		return 1;
	}
	return 0;
}

void jouer_coup(Position *pos, Coup *coup){
	manger(&(*pos).t, (*coup).x, (*coup).y);
	if(pos->J == JOUEUR_A){
		pos->J = JOUEUR_B;
		printf("tour = JOUEUR_B\n");
	}
	else{
		pos->J = JOUEUR_A;
		printf("tour = JOUEUR_A\n");
	}
}

int moyenne(int a, int b){
	return (a + b) / 2;
}

void score(int *a, int *b,Position pos){
	if(joueur_gagnant(&pos) == JOUEUR_B){
		(*a) += 1;}
	else{
		(*b) += 1;}
	
}

