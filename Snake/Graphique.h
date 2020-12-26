#ifndef __Graphique__
#define __Graphique__

#include "Serpent.h"
#include "Monde.h"

#define HAUTEUR 600
#define LARGEUR 1000
#define TAILLE_CARRE (LARGEUR/M - 1)

void afficher_quadrillage(Monde *mon);

void afficher_pomme(Pomme *pom);

void afficher_serpent(Serpent *ser);

void afficher_monde(Monde *mon);

 #endif