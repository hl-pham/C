#include <assert.h>
#include <stdlib.h>

#include "Serpent.h"

Serpent init_serpent(){
	int x, y;
	int i;
	Serpent s;
	Case c;
	s.taille = 4;
	s.dir = EST;
	x = M / 2 - 1;
	y = N / 2 - 1;
	c.x = x;
	c.y = y;
	s.tab[0] = c;
	for(i = 1; i < s.taille; i++){
		x --;
		c.x = x;
		s.tab[i] = c;
	}
	return s;
}

Pomme pomme_gen_alea(int n, int m){
	Pomme p;
	assert(n > 0);
	assert(m > 0);
	p.x = rand()%m;
	p.y = rand()%n;
	return p;
}