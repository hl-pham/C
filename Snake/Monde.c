#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


#include "Monde.h"


void ajouter_pomme_monde(Monde *mon){
	Pomme p;
	int i;
	assert(mon != NULL);
	p = pomme_gen_alea(N, M);
	for(i = 0; i < mon->s.taille; i++){
		if(mon->s.tab[i].x == p.x && mon->s.tab[i].y == p.y){
			ajouter_pomme_monde(mon);
			break;
		}
	}
	for(i = 0; i < NB_POMMES; i++){
		if(mon->pommes[i].x == p.x && mon->pommes[i].y == p.y){
			ajouter_pomme_monde(mon);
			break;
		}
		else{
			if(mon->pommes[i].x == -1 && mon->pommes[i].y == -1){
				mon->pommes[i] = p;
				break;
			}
		}
	}
}

void init_pomme(Monde *mon){
	int i;
	assert(mon != NULL);
	for(i = 0; i < NB_POMMES; i++){
		mon->pommes[i].x = -1;
		mon->pommes[i].y = -1;
	}
}

Monde init_monde(int nb_pommes){
    Monde mon;
    int i;
    assert(nb_pommes >= 1);
    mon.s= init_serpent();
    mon.nb_pommes_mangees = 0;
    init_pomme(&mon);
    for (i = 0; i < nb_pommes; ++i){
        ajouter_pomme_monde(&mon);
    }
    return mon;
}

int verif_position(Monde *mon, Case *c){
	int i;
	assert(mon != NULL);
	if(c->x >= M || c->y >= N || c->x < 0 || c->y < 0){
		return -1;
	}
	for(i = 1; i < mon->s.taille; i++){
		if(mon->s.tab[i].x == c->x && mon->s.tab[i].y == c->y){
			return -1;
		}
	}
	for(i = 0; i < NB_POMMES; i++){
		if(mon->pommes[i].x == c->x && mon->pommes[i].y == c->y){
			return i+1;
		}
	}
	return 0;
}

void direction_serpent(Monde * mon, Case *c){
	assert(mon != NULL);
	assert(c != NULL);
	if(mon->s.dir == NORD)
		c->y = c->y - 1;
	else if(mon->s.dir == SUD)
		c->y = c->y + 1;
	else if(mon->s.dir == EST)
		c->x = c->x + 1;
	else if(mon->s.dir == OUEST)
		c->x = c->x - 1;
}

int deplacer_serpent(Monde *mon){
	int i, verif;	
	Case c, tmp;
	assert(mon != NULL);
	c = mon->s.tab[0];
	direction_serpent(mon, &c);
	verif = verif_position(mon, &c);
	if(! verif){
		for(i = 0; i < mon->s.taille; i++){
			tmp = mon->s.tab[i];
			mon->s.tab[i] = c;
			c = tmp;
		}
		return 1;
	}
	return 0;
}

int manger_pomme_serpent(Monde *mon){
	int num, i;
	Case c, tmp;
	assert(mon != NULL);
	c = mon->s.tab[0];
	direction_serpent(mon, &c);
	num = verif_position(mon, &c);
	if(num > 0){
		num--;
		mon->pommes[num].x = -1;
		mon->pommes[num].y = -1;
		mon->s.taille ++;
		for(i = 0; i < mon->s.taille; i++){
			tmp = mon->s.tab[i];
			mon->s.tab[i] = c;
			c = tmp;
		}
		mon->nb_pommes_mangees ++;
		return 1;
	}
	return 0;
}

int mort_serpent(Monde *mon){
	int verif;
	Case c;
	assert(mon != NULL);
	c = mon->s.tab[0];
	direction_serpent(mon, &c);
	verif = verif_position(mon, &c);
	if(verif == -1)
		return 1;
	return 0;
}