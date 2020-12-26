#ifndef __MLV__
#define __MLV__

#include "Case.h"

void afficher_position_MLV(Position pos);

/* calcule l'indice d'un bit entre 0 et 63 a placer dans pos
 * en fonction des coordonnees du clic de
 * l'utilisateur, renvoie 1 si tout s'est bien passe */
int case_selectionnee(int *x, int *y, Case *c);

#endif