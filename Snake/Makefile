CC=gcc
CFLAGS=-ansi -pedantic -Wall -Wfatal-errors
LDFLAGS= -lMLV
OBJS=Main.o Monde.o Graphique.o Serpent.o

Snake:$(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

Main.o: Main.c Graphique.h Monde.h Serpent.h
	$(CC) -c $< $(CFLAGS)
Monde.o: Monde.c Monde.h Serpent.h
	$(CC) -c $< $(CFLAGS)
Graphique.o: Graphique.c Graphique.h Monde.h Serpent.h
	$(CC) -c $< $(CFLAGS)
Serpent.o: Serpent.c Serpent.h
	$(CC) -c $< $(CFLAGS)


clean:
	rm -f *.o
mrproper: clean
	rm -f Snake
