#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 8
#define M 16
#define MANGE 0
#define TRANDIS 1
#define HAUTEUR 480
#define LARGEUR 640

typedef struct tablette{
	int tab[N][M];
} Tablette;

typedef enum joueur{
	JOUEUR_A,
	JOUEUR_B
} Joueur;

typedef struct position {
	Tablette t;
	Joueur J;
} Position;

typedef struct coup {
	int x;
	int y;
} Coup;

Tablette creer_tablette(){
	int i, j;
	Tablette t;
	for(i = 0; i < N; i++){
		for(j = 0; j < M; j++){
			t.tab[i][j] = TRANDIS;
		}
	}
	return t;
}

void show_tab(Tablette t){/*afficher a tablette à partir de la structure du tablette*/
	int i, j;
	for(i = 0; i < N; i++){
		for(j = 0; j < M; j++){
			printf("tab[%d][%d] = %d\n", i, j, t.tab[i][j]);
		}
	}
}

/*supprimer les cases à droite et en bas du case(x,y)*/
void manger(Tablette *t, int x, int y){
	int temp_y;
	temp_y = y;
	for(; x < N; x++){
		for(temp_y = y; temp_y < M; temp_y++){
			(*t).tab[x][temp_y] = MANGE;
		}
	}
}

/*fonction qui prend la position et le coup et renvoie si le case est mangé ou pas*/
int est_legal(Position *pos, Coup *coup){
	if(pos->t.tab[coup->x][coup->y] == 1){
		return TRANDIS;
	}
	return MANGE;
}

/*elle renvoie  si le jeu est terminer avec l'affichage du joueur et  sinon*/
int est_jeu_termine(Position *pos, Joueur *joueur_gagnant){
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
	if(pos->J == JOUEUR_A){
		pos->J = JOUEUR_B;
		printf("tour = JOUEUR_B\n");
	}
	else{
		pos->J = JOUEUR_A;
		printf("tour = JOUEUR_A\n");
	}
}

void afficher(Position *pos){
	int i, j;
	int temp_x, temp_y;

	temp_x = LARGEUR / N;
	temp_y = HAUTEUR / M;

	MLV_draw_filled_rectangle(0, 0, LARGEUR, HAUTEUR, MLV_COLOR_CHOCOLATE);
	MLV_draw_filled_circle(10, 10, 5, MLV_COLOR_BLUE);

	for(i = 0; i < M; i++){
		for(j = 0; j < N; j++){
			if(pos->t.tab[j][i] == 1){
				MLV_draw_rectangle(j * temp_x, i * temp_y, temp_x, temp_y, MLV_COLOR_WHITE);
			}
			else{
				MLV_draw_filled_rectangle(j * temp_x, i * temp_y, temp_x, temp_y, MLV_COLOR_WHITE);
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
	Coup res;
	MLV_wait_mouse(&x, &y);
	/*printf("test x=%d y=%d\n", x, y);
	printf("L = %d H = %d\n", (LARGEUR / N), (HAUTEUR / M));*/
	res.y = y / (HAUTEUR / M);
	res.x = x / (LARGEUR / N);
	/*printf("x = %d y = %d\n", res.y, res.x);
	printf("mange = %d\n", pos->t.tab[res.y][res.x]);*/
	while(est_legal(pos, &res) == MANGE){
		printf("déjà mangé\n");
		MLV_wait_mouse(&x, &y);
		res.y = y / (HAUTEUR / M);
		res.x = x / (LARGEUR / N);
	}
	return res;
}

/*renvoie le nombre des partie à partier le nb des deux partie saisie par les deux joueurs*/
int moyenne(int a, int b){
	return (a + b) / 2;
}


Joueur joueur_gagnant(Position *pos){
	int fin=est_jeu_termine(pos,&(pos->J));
	if(fin ==1){
		if(pos->J == JOUEUR_A){
			MLV_draw_adapted_text_box(500, 520, "JOUEUR_A agagné",20,MLV_COLOR_RED,MLV_COLOR_BLACK , MLV_COLOR_RED, MLV_TEXT_CENTER);
			return JOUEUR_B;
		}
		else{
			MLV_draw_adapted_text_box(500, 520, "JOUEUR_B a gagné",20, MLV_COLOR_RED,MLV_COLOR_BLACK , MLV_COLOR_RED, MLV_TEXT_CENTER);
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


/*calcul le nb de fois chaque joueur a gagné*/
void score(int *a, int *b,Position pos){
	if(joueur_gagnant(&pos) == JOUEUR_B){
		(*a) += 1;}
	else{
		(*b) += 1;}
	
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
	for(int i = 0; i < nb_de_match; i++){/*debut du match*/
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
