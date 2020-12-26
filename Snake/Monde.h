#ifndef __Monde__
#define __Monde__

#include "Serpent.h"

 typedef struct Monde{
 	Serpent s;
 	Pomme pommes[NB_POMMES];
 	int nb_pommes_mangees;
 }Monde;

void ajouter_pomme_monde(Monde *mon);

void init_pomme(Monde *mon);

Monde init_monde(int nb_pommes);

int verif_position(Monde *mon, Case *c);

void direction_serpent(Monde * mon, Case *c);

int deplacer_serpent(Monde *mon);

int manger_pomme_serpent(Monde *mon);

int mort_serpent(Monde *mon);

 #endif