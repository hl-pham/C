FLAGS = -ansi -pedantic -Wall -Wno-long-long -lMLV

Dames : Main.o Case.o MLV.o
	gcc -o Dames Main.o Case.o MLV.o $(FLAGS)

Main.o : Main.c MLV.h
	gcc -c Main.c $(FLAGS)

Case.o : Case.c Case.h
	gcc -c Case.c $(FLAGS)

MLV.o : MLV.c Case.h
	gcc -c MLV.c $(FLAGS)
