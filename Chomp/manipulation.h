#ifndef MANITPULATION_H_
#define MANITPULATION_H_

#include "type.h"


#define N 8
#define M 16
#define MANGE 0
#define TRANDIS 1




Tablette creer_tablette();

void show_tab(Tablette t);

void manger(Tablette *t, int x, int y);

int est_legal(Position *pos, Coup *coup);

int est_jeu_termine(Position *pos, Joueur *joueur_gagnant);

void jouer_coup(Position *pos, Coup *coup);

int moyenne(int a, int b);

void score(int *a, int *b,Position pos);



#endif
