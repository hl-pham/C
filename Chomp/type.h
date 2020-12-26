#ifndef TYPE_H_
#define TYPE_H_

#define N 8
#define M 16
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

#endif