#ifndef __Serpent__
#define __Serpent__

#define N 16
#define M 32
#define NB_POMMES 3

typedef struct Case{
	int x;
	int y;
}Case;

typedef enum Direction{
	NORD,
	EST,
	SUD,
	OUEST
}Direction;

typedef struct {
	Case tab[N * M];
	int taille;
	Direction dir;
}Serpent;

typedef struct Case Pomme;

Serpent init_serpent();

Pomme pomme_gen_alea(int n, int m);


#endif