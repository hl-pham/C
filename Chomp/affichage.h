#ifndef AFFICHAGE_H_
#define AFFICHAGE_H_
#include "type.h"
#include <MLV/MLV_all.h>

#define MANGE 0
#define TRANDIS 1
#define HAUTEUR 480
#define LARGEUR 640


void afficher(Position *pos);

void affiche_position(Position *pos);

Coup lire_coup(Position *pos);

Joueur joueur_gagnant(Position *pos);

void affiche_Partie(int n);

void affiche_phrase(int n, char chaine[],int Y);

void affiche_joueur_gagnant(int a ,int b);



#endif
