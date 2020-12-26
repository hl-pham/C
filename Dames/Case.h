#ifndef __CASE__
#define __CASE__

typedef unsigned long long Position;

Position tab_cases_attaquees[64];

typedef enum {
	A1, B1, C1, D1, E1, F1, G1, H1,
	A2, B2, C2, D2, E2, F2, G2, H2,
	A3, B3, C3, D3, E3, F3, G3, H3,
	A4, B4, C4, D4, E4, F4, G4, H4,
	A5, B5, C5, D5, E5, F5, G5, H5,
	A6, B6, C6, D6, E6, F6, G6, H6,
	A7, B7, C7, D7, E7, F7, G7, H7,
	A8, B8, C8, D8, E8, F8, G8, H8
} Case;

/* test si le c_ieme bit de pos est a 1,
 * renvoie 1 si c'est le cas, renvoie 0 sinon */
int est_case_occupee(Position pos, Case c);

/* place 1 au c_ieme bit de pos,
 * renvoie pos */
int placer_dans_position(Position *pos, Case c);

/* affiche la position pos, renvoie 1 si tout s'est bien passé,
 * renvoie 0 sinon */
int afficher_position(Position pos);

/* calcule les cases mangees par une dame
 * dans pos, en position c. Renvoie 1 si
 * tout s'est bien passe, renvoie 0 sinon */ 
int calculer_cases_attaquees(Position *pose, Case c);

/* calcule toutes les cases mangees par toutes
 * les dames dans pos, renvoie 1 si aucune dames
 * ne se mangent mutuellement, renvoie 0 sinon */
int est_sans_attaque_mutuelle(Position pos);

#endif