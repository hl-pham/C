#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N 20


/*

Vérifier la fonction jouerOuvrir
Pourquoi le première lettre de chaque ligne disparait ?
Voir 365 - 394

*/







  /*********************************************/
 /*			PARTIE CREATION DE LA GRILLE      */
/*********************************************/



int creerGrille(void) {
	/**
	 *	Cette fonction permet de saisir et de renvoyer la taille n de la grille
	 */
	int n;
	do {
		printf("Saisissez la taille de la grille : ");
		scanf("%d", &n);
	} while (n > N || n < 5);
	return n;
}



void directionMot(int *directionX, int *directionY, int direction) {	
	/**
	 *	int *directionX : Sens d'écriture du mot selon l'axe X, horizontal. Indice des éléments d'une ligne (colonne)
	 *	int *directionY : Sens d'écriture du mot selon l'axe Y, vertical. Indice des éléments du tableau grille (ligne)
	 *	int direction : Sens d'écriture du mot selon l'énoncé du sujet
	 *
	 *	Cette fonction permet de définir dans quel sens le mot sera écrit,
	 *	en modifiant les valeurs de directionX et directionY à l'aide de leur adresse
	 */
	switch(direction) {
		case 0:
			*directionX = -1;
			*directionY = -1;
			printf("Votre mot sera ecrit vers la diagonale haut-gauche.\n");
			break;
		case 1:
			*directionX = 0;
			*directionY = -1;
			printf("Votre mot sera ecrit vers le haut.\n");
			break;
		case 2:
			*directionX = 1;
			*directionY = -1;
			printf("Votre mot sera ecrit vers la diagonale haut-droite.\n");
			break;
		case 3:
			*directionX = -1;
			*directionY = 0;
			printf("Votre mot sera ecrit vers la gauche.\n");
			break;
		case 4:
			*directionX = 1;
			*directionY = 0;
			printf("Votre mot sera ecrit vers la droite.\n");
			break;
		case 5:
			*directionX = -1;
			*directionY = 1;
			printf("Votre mot sera ecrit vers la diagonale bas-droite.\n");
			break;
		case 6:
			*directionX = 0;
			*directionY = 1;
			printf("Votre mot sera ecrit vers le bas.\n");
			break;
		case 7:
			*directionX = 1;
			*directionY = 1;
			printf("Votre mot sera ecrit vers la diagonale bas-droite.\n");
			break;
	}
}



int ecrireMot(int n, char grille[][n], int directionX, int directionY, char mot[], int coordX, int coordY) {
	/**
	 *	int n : Taille de la grille
	 *	char grille[][n] : Grille dans laquelle seront affichés les mots
	 *	int directionX : Sens d'écriture du mot selon l'axe X, horizontal. Indice des éléments d'une ligne (colonne)
	 *	int directionY : Sens d'écriture du mot selon l'axe Y, vertical. Indice des éléments du tableau grille (ligne)
	 *	char mot[] : Mot que l'on souhaite introduire dans la grille
	 *	int coordX : Coordonnée X de la première lettre du mot
	 *	int coordY : Coordonnée Y de la première lettre du mot
	 *
	 *	Cette fonction permet de :
	 *		- Vérifier si le mot ne sort pas de la grille
	 *		- Vérifier si le mot ne chevauche pas un mot incompatible
	 *		- Ecrit le mot dans la grille

	 *	Renvoie 0 si on ne peut pas écrire le mot dans la grille
	 *	Renvoie 1 si on peut écrire le mot dans la grille
	 */
	for (int i = 0; i < strlen(mot); i++) {
		// On vérifie si la coordonnée à laquelle on souhaite écrire notre lettre ne sort pas de la grille
		if (coordY + (directionY * i) < 0 || coordY + (directionY * i) >= n || coordX + (directionX * i) < 0 || coordX + (directionX * i) >= n) {
			printf("Le mot sort de la grille.\n");
			return 0;
		// On vérifie si le caractère à l'emplacement que l'on veut écrire la lettre est le même
		} else if (grille[coordY + (directionY * i)][coordX + (directionX * i)] != mot[i] && grille[coordY + (directionY * i)][coordX + (directionX * i)] != '-') {
			printf("Le mot entre en conflit dans la grille.\n");
			return 0;
		}
	}
	// Le mot ne sort pas de la grille et n'entre en conflit avec aucun autre mot
	for (int i = 0; i < strlen(mot); i++) {
		grille[coordY + (directionY * i)][coordX + (directionX * i)] = mot[i];
	}
	return 1;
}



int choisirMot(int n, char grille[][n], int directionX, int directionY, char mot[], int coordX, int coordY, int numero, int nbMots, char listeMots[nbMots][n]) {
	/**
	 *	int n : Taille de la grille
	 *	char grille[][n] : Grille dans laquelle seront affichés les mots
	 *	int directionX : Sens d'écriture du mot selon l'axe X, horizontal. Indice des éléments d'une ligne (colonne)
	 *	int directionY : Sens d'écriture du mot selon l'axe Y, vertical. Indice des éléments du tableau grille (ligne)
	 *	char mot[] : Mot que l'on souhaite introduire dans la grille
	 *	int coordX : Coordonnée X de la première lettre du mot
	 *	int coordY : Coordonnée Y de la première lettre du mot
	 *	int numero : Numéro du mot à entrer (Inférieur à n)
	 *	int nbMots : Nombre de mot à entrer (Inférieur à n)
	 *	char listeMots[nbMots][n] : Liste des mots saisis
	 *
	 *	Cette fonction permet de :
	 *		- Saisir le mot que l'on souhaite entrer
	 *		- Définir sa position de départ
	 *		- Définir son sens d'écriture
	 *
	 *	Renvoie motValide pour indiquer au programme que le mot suivant peut être saisi
	 */
	int motValide, direction, finMot;
	do {
		printf("\nQuel est votre %de mot ? (%d lettres max) ", numero+1, n);
		scanf("%s", mot);
		strupr(mot); // Fonctionne sous Windows, ne fonctionne pas sous Linux
		// mot = mot - 'a' + 'A';	// Fonctionne sous Linux, ne fonctionne pas correctement sous Windows
	} while (strlen(mot) > n);

	for (int j = 0; j < n; j++) {
		if (mot[j] < 'A' || mot[j] > 'Z') {	// Les mots sont séparés par des espaces, donc si le caractère n'est pas une lettre majuscule, alors le mot est terminé, on passe au suivant
			finMot = 1;
		}
		if (finMot == 1) {	// On met \0 pour indiquer la fin de la chaîne
			listeMots[numero][j] = '\0';
		} else {			// Sinon, c'est une lettre, on l'ajoute
			listeMots[numero][j] = mot[j];
		}
	}

	do {
		printf("Ou se situe votre mot ? ");
		scanf("%d %d", &coordY, &coordX);
	} while (((grille[coordY][coordX] != '-') ^ (grille[coordY][coordX] == mot[0])) || (0 > coordY || coordY >= n || 0 > coordX || coordX >= n));

	do {
		printf("Dans quelle direction souhaitez-vous ecrire votre mot ? ");
		scanf("%d", &direction);
		directionMot(&directionX, &directionY, direction);
	} while (direction < 0 || direction > 7);

	motValide = ecrireMot(n, grille, directionX, directionY, mot, coordX, coordY);
	return motValide;
}



void afficherGrille(int taille, char grille[][taille], int creation) {
	/**
	 *	int taille : Taille de la grille
	 *	char grille[][taille] : Grille de taille taille x taille
	 *	int creation : Variable permettant de vérifier si on est en train d'initialiser la grille ou non
	 *
	 *	Cette fonction permet :
	 *		- D'initialiser la grille
	 *		- D'afficher la grille
	 *	Si creation = 1, on crée la grille
	 *	Si creation = 0, on affiche simplement la grille
	 */
	// On affiche les abscisses de la grille
	printf("\n  ");
	for (int x = 0; x < taille; x++) {
		printf("%d", x);
	}
	printf("\n");

	for (int ligne = 0; ligne < taille; ligne++) {
		// On affiche les ordonnées de la grille
		printf("%d ", ligne);
		for (int colonne = 0; colonne < taille; colonne++) {
			if (creation == 1) {
				grille[ligne][colonne] = '-';	// On initialise la grille
			}
			// On affiche la grille
			printf("%c", grille[ligne][colonne]);
		}
		printf("\n");
	}
}



void remplirGrille(int n, char grille[][n]) {
	/**
	 *	int n : Taille de la grille
	 *	char grille[][n] : Grille de taille n x n
	 *
	 *	Cette fonction permet de remplir la grille de lettres aléatoires une fois que
	 *	l'on a fini de saisir nos n mots
	 */
	for (int ligne = 0; ligne < n; ligne++) {
		for (int colonne = 0; colonne < n; colonne++) {
			if (grille[ligne][colonne] == '-') {
				grille[ligne][colonne] = (char) ((rand() % 26) + 97);
			}
		}
	}
}



void creationGrille(FILE *fp) {
	/**
	 *	FILE *fp : Fichier dans lequel on souhaite sauvegarder la grille
	 *
	 *	Cette fonction permet de créer entièrement la grille, et de l'enregistrer dans le fichier fp
	 */
	int coordX = 0, coordY = 0, motValide = 0, directionX = 0, directionY = 0, nbMots = 0, creation = 1, n = creerGrille();
	char grille[n][n], mot[n];

	afficherGrille(n, grille, creation);
	creation = 0;

	// On insère la taille de la grille dans le fichier
	fprintf(fp, "%d\n", n);

	do {
		printf("Combien de mots souhaitez-vous inserer dans la grille ? ");
		scanf("%d", &nbMots);
	} while (nbMots > n || nbMots <= 0);

	// On insère le nombre de mots dans le fichier
	fprintf(fp, "%d\n", nbMots);
	// On initialise la liste des mots, nbMots = nombre de mots, n = longueur max des mots
	char listeMots[nbMots][n];

	// Boucle permettant de saisir les n mots de la grille
	for (int numero = 0; numero < nbMots; numero++) {
		motValide = 0;

		do {		// On demande un mot et on l'affiche dans la grille s'il est valide
			motValide = choisirMot(n, grille, directionX, directionY, mot, coordX, coordY, numero, nbMots, listeMots);
		} while (motValide != 1);

		// On affiche la grille à chaque fois qu'un mot est validé
		afficherGrille(n, grille, creation);
	}

	remplirGrille(n, grille);
	afficherGrille(n, grille, creation);

	// On insère chaque mots dans le fichier
	for (int i = 0; i < nbMots; i++) {
		// for (int j = 0; j < n; j++) {
		fprintf(fp, "%s ", listeMots[i]);
		// }
		// fprintf(fp, " ");
	}
	fprintf(fp, "\n");
	
	// On insère la grille dans le fichier
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fprintf(fp, "%c", grille[i][j]);
		}
		fprintf(fp, "\n");
	}
}






  /*********************************************/
 /*			PARTIE RESOUDRE LA GRILLE         */
/*********************************************/



void jouer(int taille, int nbMots, char grille[][taille], char listeMots[nbMots][taille]) {
	int creation = 0, initX = 0, initY = 0, finX = 0, finY = 0, choix;
	do {
		afficherGrille(taille, grille, creation);
		for (int i = 0; i < nbMots; i++) {
			printf("%d. %s", i, listeMots[i]);			
			printf("\n");
		}
		printf("Quel est le mot que vous avez trouve ? ");
		scanf("%d", &choix);
	} while (initX >= 0 || initY >= 0 || finX >= 0 || finY >= 0);
}



void jouerOuvrir(FILE *fp) {
	/**
	 *	FILE * fp : Le fichier qu'on ouvre
	 *
	 *	Cette fonction permet d'extraire toutes les informations nécessaires au jeu,
	 *	puis de lancer le jeu
	 *
	 *	taille -> Taille du tableau
	 *	nbMots -> Nombre de mots
	 *	listeMots -> Le tableau qui contient tous les mots à chercher
	 *	grille -> La grille de jeu
	 */
	int i = 0, position = 0, sautLigne = 0, ligneMots = 0, ligneGrille = -1, taille, nbMots, boucle/*, cpt = 0*/;
	char tailleGrille[N], nombreMots[N];
	while (i != EOF) {
		i = fgetc(fp);								// On récupère un par un chaque caractère 
		if (i == 10) {								// On a un \n dans le fichier
			sautLigne += 1;							// On passe à la ligne suivante
			position = 0;							// On repasse à 0 pour pouvoir réutiliser le compteur de position pour une autre liste
		}
		if (sautLigne == 0) {
			tailleGrille[position] = i;

		} else if (sautLigne == 1) {
			nombreMots[position] = i;

		} else if (sautLigne > 1) {
			break;
		}
		position++;
	}

	taille = atoi(tailleGrille);				// Conversion de la chaîne de caractère de la taille en int
	nbMots = atoi(nombreMots);					// Conversion de la chaîne de caractère du nombre de mots en int
	char listeMots[nbMots][taille], grille[taille][taille];

	// On cherche maintenant à initialiser les tableaux dans lesquels on aura la liste des mots et la grille
	while (i != EOF) {
		i = fgetc(fp);
		// printf("%c", i);
		if (i == 10) {								// On a un \n dans le fichier
			sautLigne += 1;							// On passe à la ligne suivante
			position = 0;							// On repasse à 0 pour pouvoir réutiliser le compteur de position pour une autre liste
		}

		if (sautLigne == 2) {
			if (i != 32) {							// On vérifie si i est une espace
				listeMots[ligneMots][position] = i;
				position++;							// On passe à la case suivante du tableau listeMots[ligneMots] (la lettre suivante)
			} else if (i == 32) {					// Si c'est un espace
				listeMots[ligneMots][position] = '\0';
				position = 0;						// On reset colonne pour pouvoir la réutiliser
				ligneMots++;						// On passe à la ligne suivante (au mot suivant)
			}
		} else if (sautLigne > 2) {					// Dernier cas, c'est la grille
			if (i != 10 && i != 32) {				// On vérifie si i est un retour à la ligne \n
				grille[ligneGrille][position] = i;
				printf("%d%c-- ", ligneGrille, grille[0][0]);
				position++;							// On passe à la lettre suivante

			} else {
				grille[ligneGrille][position] = '\0';
				position = 0;						// On passe à la première lettre
				ligneGrille++;						// On passe à la ligne suivante
			}
		}
	}
	printf("%c--", grille[0][0]);
	jouer(taille, nbMots, grille, listeMots);
}




int main(int argc, char const* argv[]) {
	srand(time(NULL));

	int create = 0;
	FILE * fp = NULL;
	/*
	Pour choisir si on ouvre le fichier en lecture ou en écriture, on peut essayer de vérifier le nombre d'argument d'options
	Si on a que -a ou -g (strlen(argument) == 1), on ouvre le fichier en lecture
	Si on a au moins -c, on ouvre le fichier en écriture. Par défaut, -c sera en ASCII
	Pour ce faire, il faut changer la position du switch, pour que la condition if (NULL = fp) se trouve dans chaque cas du switch
	Sinon, on ne pourra pas ouvrir le fichier
	*/

	for (int i = 1; i < argc; ++i) {
		if (argv[i][0] == '-') {
			continue;
		} else {
			if (argv[1][0] == '-') {	// On vérifie d'abord si on souhaite créer une grille avant de commencer
				for (int verifC = 0; verifC < strlen(argv[1]); verifC++) {
					if (argv[1][verifC] == 'c') {
						create = 1;	// On souhaite créer une grille
					}
				}

				// On annonce quelle mode on veut
				for (int j = 0; argv[1][j] != '\0'; j++) {
					switch(argv[1][j]) {
						case 'a':
							printf("Affichage ASCII.\n");
							break;
						case 'g':
							printf("Affichage graphique.\n");
							break;
					}
				}

				// On créer la grille
				if (create == 1) {
					printf("Creation d'une grille.\n");
					fp = fopen(argv[i], "w");
					if (NULL == fp) {
						continue;
					} else {
						creationGrille(fp);
					}
				} else {
					printf("Lancement du jeu.\n");
					fp = fopen(argv[i], "r");
					if (NULL == fp) {
						continue;
					} else {
						jouerOuvrir(fp);
					}
				}
			}

		}
	}
	return 0;
}