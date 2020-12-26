#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HAUTEUR 480
#define LARGEUR 640
#define N 8
#define M 11


#define NB_POMME 3

#define TETE 2
#define CORPS 1
#define DANS_CASE 3


typedef struct Case{
	int x;
	int y;
} Case;

typedef enum direction{
	North,
	East,
	South,
	West
} Direction;

typedef struct serpent{
	Case c[N*M];
	int taille;
	Direction d;
} Serpent;

typedef struct pomme{
	int x;
	int y;
} Pomme;

typedef struct monde{
	Serpent s;
	Pomme p[NB_POMME];
	int mange_p;
} Monde;

Pomme pomme_gen_alea(int n, int m){
	Pomme pomme;
	pomme.x = MLV_get_random_integer(0, m-1);
	pomme.y = MLV_get_random_integer(0, n-1);
	return pomme;
}

void ajouter_pomme_monde(Monde *mon){
	Pomme p;
	int i, j;
	p = pomme_gen_alea(N,M);
	printf("pomme.x = %d pomme.y = %d\n", p.x, p.y);
	int temp_x = p.x;
	int temp_y = p.y;
	for(i = 0; i < mon->s.taille; i++){
		if(mon->s.c[i].x == temp_x && mon->s.c[i].y == temp_y){
			printf("error\n");
			ajouter_pomme_monde(mon);
		}
	}
	for(i = 0; i < NB_POMME; i++){
		//printf("i = %d\n", i);
		if(mon->p[i].x == -1 && mon->p[i].y == -1){
			if(i == 0){
				mon->p[i] = p;
			}
			for(j = 0; j < i; j++){
				if(mon->p[j].x == p.x && mon->p[j].y == p.y){
					//printf("aaaa\n");
					i--;
					break;
				}
				else{
					mon->p[i] = p;
				}
			}
			if(mon->p[NB_POMME-1].x == -1){
				ajouter_pomme_monde(mon);
			}
		}
	}
}

void init_pomme(Monde *mon){
	int i;
	for(i = 0; i < NB_POMME; i++){
		mon->p[i].x = -1;
		mon->p[i].y = -1;
	}
}

Serpent init_serpent(){
	int x, y;
	int i;
	Serpent s;
	s.d = East;
	x = M / 2;
	y = N / 2;
	s.taille = 3;
	s.c[0].x = x;
	s.c[0].y = y;
	for(i = 1; i < s.taille; i++){
		x--;
		s.c[i].x = x;
		s.c[i].y = y;
	}
	return s;
}

Monde init_monde(int nb_pomme){
	Monde mon;
	init_pomme(&mon);
	mon.mange_p = 0;
	mon.s = init_serpent();
	ajouter_pomme_monde(&mon);
	return mon;
}

int verifie_pos(Monde mon, int x, int y){
	int i;
	if(x >= M || y >= N || x < 0 || y < 0){
		printf("test\n");
		return -1;
	}
	for(i = 1; i < mon.s.taille; i++){
		if(mon.s.c[i].x == x && mon.s.c[i].y == y){
			return -1;
		}
	}
	for(i = 0; i < NB_POMME; i++){
		if(mon.p[i].x == x && mon.p[i].y == y){
			return i+1;
		}
	}
	return 0;
}

int manger_pomme_serpent(Monde *mon, int new_x, int new_y, int res){
	int temp_x, temp_y;
	int grow_x, grow_y;
	int i;

	grow_x = mon->s.c[mon->s.taille-1].x;
	grow_y = mon->s.c[mon->s.taille-1].y;
	
	for(i = 0; i < mon->s.taille; i++){
		temp_x = mon->s.c[i].x;
		temp_y = mon->s.c[i].y;
		mon->s.c[i].x = new_x;
		mon->s.c[i].y = new_y;
		new_x = temp_x;
		new_y = temp_y;
	}	

	mon->s.taille += 1;
	mon->mange_p ++;
	mon->s.c[mon->s.taille-1].x = grow_x;
	mon->s.c[mon->s.taille-1].y = grow_y;

	mon->p[res].x = -1;
	mon->p[res].y = -1;

	ajouter_pomme_monde(mon);

	return 1;
}

int deplacer_serpent(Monde *mon){
	int temp_x, temp_y;
	int new_x, new_y;
	int res, i;
	int mange;
	new_x = mon->s.c[0].x;
	new_y = mon->s.c[0].y;
	if(mon->s.d == East){
		//printf("test1\n");
		new_x ++;
	}
	if(mon->s.d == South){
		//printf("test2\n");
		new_y ++;
	}
	if(mon->s.d == West){
		//printf("test3\n");
		new_x --;
	}
	if(mon->s.d == North){
		//printf("test4\n");
		new_y --;
	}
	printf("n_tete x =%d y =%d\n", new_x, new_y);
	res = verifie_pos(*mon, new_x, new_y);
	printf("move = %d\n", res);
	if(res == -1){
		return 0;
	}
//deplacer	
	else if(res == 0){
		for(i = 0; i < mon->s.taille; i++){
			temp_x = mon->s.c[i].x;
			temp_y = mon->s.c[i].y;
			mon->s.c[i].x = new_x;
			mon->s.c[i].y = new_y;
			new_x = temp_x;
			new_y = temp_y;
		}	
	}
//manger
	else if(res > 0){
		mange = manger_pomme_serpent(mon, new_x, new_y, res-1);
		printf("mangé = %d p[%d]\n", mange, res-1);
		return 2;
	}

	return 1;
}


int mort_serpent(Monde *mon){
	if(verifie_pos(*mon, mon->s.c[0].x , mon->s.c[0].y) == -1 ){
		printf("test\n");
		return 1;
	}
	return 0;
}

void show_pos_serpent(Monde mon){
	int i;
	printf("tete: x = %d y = %d\n", mon.s.c[0].x, mon.s.c[0].y);
	for(i = 1; i < mon.s.taille; i++){
		printf("corps %d: x = %d y = %d\n", i, mon.s.c[i].x, mon.s.c[i].y);
	}
}

void show_pomme(Monde mon){
	int i;
	for(i = 0; i < NB_POMME; i++){
		printf("p.x = %d, p.y = %d\n", mon.p[i].x, mon.p[i].y);
	}
}

void afficher_quadrillage(Monde *mon){
	int i, j;
	int temp_x, temp_y;

	temp_x = 58;
	temp_y = 58;
	MLV_draw_filled_rectangle(0, 0, LARGEUR, HAUTEUR, MLV_COLOR_ANTIQUE_WHITE);
	for(i = 0; i < N; i++){
		for(j = 0; j < M; j++){
			MLV_draw_rectangle(j * temp_x, i * temp_y, temp_x, temp_y, MLV_COLOR_CHOCOLATE);
		}
	}
}

void afficher_pomme(Pomme *pom){
	int i;
	for(i = 0; i < NB_POMME; i++){
		MLV_draw_filled_circle((pom[i].x*58)+(58/2),(pom[i].y*58)+(58/2), 20 , MLV_COLOR_RED);
	}
}

void afficher_serpent(Serpent *ser){
	int i;
	MLV_draw_filled_circle((ser->c[0].x*58)+(58/2),(ser->c[0].y*58)+(58/2), 20 , MLV_COLOR_BLACK);
	for(i = 1; i < ser->taille; i++){
		MLV_draw_filled_rectangle((ser->c[i].x*59), (ser->c[i].y*59), 50, 50, MLV_COLOR_DARK_GREEN);
	}
}

void afficher_monde(Monde *mon) {
	int i =0;
	afficher_quadrillage(mon);
	afficher_serpent(&mon->s);
	afficher_pomme(&mon->p[i]);
	MLV_actualise_window();
}


	
int main(int argc, char *argv[]){
	Monde mon;
	MLV_Keyboard_button d;
	MLV_Button_state etat;
	MLV_Event event;
	char *score = "Partie terminee";
	char *fin_jeu = "Mort !!";
	int jeu = 1;

	MLV_create_window( "tp3", "tp3", LARGEUR, HAUTEUR);
	mon = init_monde(NB_POMME);
	afficher_monde(&mon);
	MLV_draw_adapted_text_box(238, 0, "Press On SPACE to START!", 20, MLV_COLOR_RED,MLV_COLOR_BLACK , MLV_COLOR_RED, MLV_TEXT_CENTER);
	MLV_actualise_window();
	MLV_wait_keyboard(&d, NULL, NULL);
	if (d == MLV_KEYBOARD_SPACE) {
		while (1) {
			event = MLV_get_event(&d, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &etat);
			if (event == MLV_KEY) {
				if (etat == MLV_PRESSED) {
					;
				}
			}

			if (d == MLV_KEYBOARD_UP) {
				if (mon.s.d != South) {
					mon.s.d = North;
				}
			}

			if (d == MLV_KEYBOARD_DOWN) {
				if (mon.s.d != North) {
					mon.s.d = South;
				}
			}

			if (d == MLV_KEYBOARD_LEFT) {
				if (mon.s.d != East) {
					mon.s.d = West;
				}
			}

			if (d == MLV_KEYBOARD_RIGHT) {
				if (mon.s.d != West) {
					mon.s.d = East;
				}
			}
			jeu = deplacer_serpent(&mon);
			//MLV_clear_window(MLV_COLOR_BLACK);
			afficher_monde(&mon);
			MLV_wait_milliseconds(250);
			if(jeu == 0){
				printf("die\n");
				MLV_draw_adapted_text_box((LARGEUR+ 50) / 2 - 45, (HAUTEUR + 50)/ 2, fin_jeu, 20, MLV_COLOR_RED,MLV_COLOR_BLACK , MLV_COLOR_RED, MLV_TEXT_CENTER);
				MLV_actualise_window();
				MLV_wait_seconds(2);
				break;
			}
		}
		MLV_clear_window(MLV_COLOR_BLACK);
		/*MLV_draw_text((LARGEUR+ 50) / 2 - 45, (HAUTEUR + 50)/ 2, score, MLV_COLOR_WHITE);*/
		MLV_draw_adapted_text_box((LARGEUR+ 50) / 2 - 45, (HAUTEUR + 50)/ 2, score, 20, MLV_COLOR_RED,MLV_COLOR_BLACK , MLV_COLOR_RED, MLV_TEXT_CENTER);
		MLV_actualise_window();
		MLV_wait_seconds(2);
	}

	MLV_actualise_window();
	MLV_free_window();
	return 0;
}
