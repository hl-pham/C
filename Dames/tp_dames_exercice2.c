#include <stdio.h>
#include <stdlib.h>

void de_decimal_a_binaire(int i) {
	if (i < 2) {
		printf("%d", i % 2);
	}
	else {
		de_decimal_a_binaire(i / 2);	
		printf("%d", i % 2);
	}
}

int main(int argc, char *argv[]) {
	int a;
	int b;
	int c;

	a = 1;
	b = 2;
	c = 3;
	printf("a = %d b = %d\n", a, b);

	/* 1 */
	printf("a (15e bit a 1 et autres a 0) = %d\n", (a << 14));

	/* 2 */
	printf("a (14e bit a 0 et autres a 1) = %d\n", ~(a << 13));

	/* 3 */
	printf("b (13e bit a 1) = %d\n", b | (1 << 12));

	/* 4 */ 
	printf("b (12e bit a 0) = %d\n", b & (~(1 << 11)));

	/* 5 */
	printf("test si le 11e bit de b est 1: %d\n", (b & (1 << 10)) == 0 ? 0 : 1);

	/* 6 */
	printf("test si les 3 premiers bits de b sont tous 1: %d\n", (b & 7) == 7 ? 1 : 0);

	/* 7 */
	printf("test si les 4 premiers bits de b sont tous 0: %d\n", (b & 15) == 0 ? 1 : 0);

	/* 8 */
	printf("test si le 10e bits de 2 entiers sont egaux: %d\n", ((b & (1 << 9)) == (c & (1 << 9))) ? 1 : 0);

	/* 9 */
	printf("test si 2 entiers ont au moins un bit a 1 en commun: %d\n", (b & c) == 0 ? 0 : 1);

	/* 10 */
	printf("test si tous les bits des 2 entiers sont egaux: %d\n", (((b & c) == c) && ((b & c) == b)) ? 1 : 0);

	/* 11 */
	printf("test si tous les bits des 2 entiers sont differents: %d\n", (b & c) == 0 ? 1 : 0);
	
	return 0;
}