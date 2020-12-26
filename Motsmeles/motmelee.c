#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define N 20



int afficher_coordonnee(char tab[],int taille){
	/** Fonction permettant a l'utilisateur de voir toute les coordonnées qu'il peut saisir **/

	printf("Voici la grille avec les coordonnées (ligne,colonne) de chaque position que vous pouvez saisir: \n ");


	for(int i=0;i<taille;i++) {
		printf("\n");
		for(int j=0;j<taille;j++) {
			printf(" (%d,%d)",i,j );
		}

	}
	printf("\n");

	return 0;
}

int afficher_direction(void){
	/** Fonction permettant a l'utilisateur de voir toute les directions qu'il peut saisir **/

	printf("\n");
	printf(" Voici les directions que vous pouvez saisir :\n");
	printf(" [ 0  1  2 \n   3     4 \n   5  6  7 ] \n");

	return 0;
}

int init_grille(int taille, char grille[][taille]){
	/** Fonction permettant d'initialiser la grille au debut pour qu'elle ne contienne que des '-' **/

	for(int i=0;i<taille;i++) {
		printf("\n");
		for(int j=0;j<taille;j++) {

			grille[i][j]='-';
			printf("%c", grille[i][j]);
		}

	printf("\n");	

	}

	return 0;

}

int actualiser_grille(int taille, char grille[][taille]) {
	/** Fonction permettant d'actualiser/afficher la grille **/

		for(int i=0;i<taille;i++) {
		printf("\n");
		for(int j=0;j<taille;j++) {

			printf("%c", grille[i][j]);

		}

	printf("\n");	

	}

	return 0;

}

void direction_grille(int direction, int *direction_ligne,int *direction_colonne){
	/** Fonction permettant de se deplacer dans la grille en fonction de la direction **/ 

	switch(direction){
		case 0:
			*direction_ligne =-1;
			*direction_colonne =-1;
			break;
		case 1:
			*direction_ligne =-1;
			*direction_colonne =0;
			break;
		case 2:
			*direction_ligne =-1;
			*direction_colonne =1;
			break;
		case 3:
			*direction_ligne =0;
			*direction_colonne =-1;
			break;
		case 4:
			*direction_ligne =0;
			*direction_colonne =1;
			break;
		case 5:
			*direction_ligne =1;
			*direction_colonne =-1;
			break;
		case 6:
			*direction_ligne =1;
			*direction_colonne =0;
			break;	
		case 7:
			*direction_ligne =1;
			*direction_colonne =1;
			break;						
	}

}




int inserer(char mot[],int taille,char grille[][taille],int direction,int position_i, int position_j,char bibliotheque[][taille]){
	/** Permet d'inserer le mot dans la grille **/ 

	int direction_ligne,direction_colonne,ligne,colonne;
	direction_grille(direction,&direction_ligne,&direction_colonne);

	for(int i=0;i<strlen(mot);i++){


		ligne=position_i+ direction_ligne*i;
		colonne=position_j + direction_colonne*i;

		if((ligne<0 || ligne>taille || colonne<0 || colonne > taille) || (grille[ligne][colonne]!=mot[i] && grille[ligne][colonne]!= '-' )){
			printf("Le mot n'est pas valide, il depasse la grille ou ne coincide pas avec le mot déja présent.");
			return 1; /* Si on retourne 1 alors le mot n'est pas valide */ 
		}

	}

	for(int i=0;i<strlen(mot);i++){


		ligne=position_i+ direction_ligne*i;
		colonne=position_j + direction_colonne*i;

		grille[ligne][colonne]=mot[i];

		}

	
	
	
	
	return 0;





}


int mot_a_inserer(int taille,int nb_mots,char grille[][taille],char mot[],int position_i, int position_j, int direction,char bibliotheque[][N]){
	/** Permet de saisir le mot,sa position et sa direction **/ 


	int nb_max=taille,compteur=0,valide=0;
	do {



	do{
	printf("Vous avez saisie %d/%d mot(s). ",compteur, nb_mots);
	printf("Veuillez rentrez le mot que vous voulez en majuscule :\n");
	scanf("%s",mot);
	}
	while( strlen(mot)>taille);
	
	compteur+=1;

	do {
	printf("\n Sa position: (ligne colonne) :\n");
	scanf(" %d %d",&position_i,&position_j);	
	}
	while(position_i>taille || position_j>taille);

	do{	
		printf("\n Sa direction:\n");
		scanf("%d",&direction);
		}
	while(direction<0 || direction>7);


	valide=inserer(mot,taille,grille,direction,position_i,position_j,bibliotheque);
	if(valide==1){
		compteur-=1;
	}



	else{
		int i;
		for(i=0;i<strlen(mot);i++){
				bibliotheque[compteur-1][i]=mot[i];
				printf("%c", bibliotheque[compteur-1][i]);
			}
			bibliotheque[compteur-1][i+1]='\0';
			printf("%s", bibliotheque[compteur-1]);
		}
	


	printf("\nVoici la grille actuellement après saisie du mot :\n");
	actualiser_grille(taille,grille);




	}
	while(compteur<nb_max && compteur<nb_mots);
	


	return 0;

}

int remplir_grille(int taille, char grille[][taille]){

	printf("\n \n \nVoici la grille final: \n ");
	for(int i=0;i<taille;i++) {

		for(int j=0;j<taille;j++) {
			if (grille[i][j]=='-'){
				grille[i][j]=(rand() % 26) + 97;

			

		}
			}
	

	}

	return 0;
}





void sauvegarde_fichier(char const *argv[],int taille,int nb_mots, char grille[][taille],char bibliotheque[][N]){
	
	FILE * file = fopen(argv[2],"w");

	fprintf(file,"%d \n", taille);
	fprintf(file,"%d \n", nb_mots);
	
	for (int i = 0; i < nb_mots; i ++){
		fprintf(file,"%s ",bibliotheque[i]);
		fprintf(file,"\n");
	}
	
	
	for (int i = 0; i < taille; i ++){

		for(int j=0; j<taille; j++){
			fprintf(file,"%c ",grille[i][j]);
			}
		fprintf(file,"\n");
	}
	fclose(file);
}


int afficher_bibliotheque(int nb_mots,char bibliotheque[][N]){

	printf("\nVoici les mots à chercher : \n");
	for(int i=0;i<nb_mots;i++){
		printf("%d. %s\n",i,bibliotheque[i]);



	}
return 0;

}


int joueur_saisie(int *num_mot,int *x_1erlettre,int *y_1erlettre,int *x_derlettre,int *y_derlettre,int nb_mot,int taille){
	

	do {
		printf("Saisir le numéro du mot: \n");
		scanf("%d", num_mot);
		if (*num_mot < 0){ /* Si le joueur abandonne */ 
			return -1;
		}
	}while (*num_mot > nb_mot - 1);

	do {
		printf("Saisir la position de la 1ere lettre du mot (ligne colonne): \n");
		scanf("%d %d",x_1erlettre,y_1erlettre);
		if (*x_1erlettre < 0 || *y_1erlettre < 0){
			return -1;
		}
		}while (*x_1erlettre >  taille - 1 || *y_1erlettre > taille - 1 );
	
	
	do {
		printf("Saisir la position de la dernière lettre du mot (ligne colonne): \n");
		scanf("%d %d",x_derlettre,y_derlettre);
		if (*x_1erlettre < 0 || *y_1erlettre < 0){
			return -1;
		}
		}while (*x_derlettre >  taille - 1 || *y_derlettre > taille - 1 );	
	
	return 0;
}

int verification_mot(int num_mot,int taille, char mot_joueur[][taille], char bibliotheque[][taille]){


	for(int i=0;i<taille;i++){
		if(mot_joueur[num_mot][i] != bibliotheque[num_mot][i]){
			return -1;
		}

	}
return 0;
}
	

int recuperation_mot(int taille, int nb_mots, char grille[][N], char bibliotheque[][N],char mot_joueur[taille],int *num_mot,int *x_1erlettre,int *y_1erlettre,int *x_derlettre,int *y_derlettre){
	;
	
	int direction=0;

	printf("ICI : %d %d %d %d %d",*num_mot,*x_1erlettre,*y_1erlettre,*x_derlettre,*y_derlettre);

	
		/* Si la direction est 0 */ 
		if ((*x_derlettre<*x_1erlettre )&& (*y_derlettre<*y_1erlettre)){
			while(*x_1erlettre-direction>=*x_derlettre){
				printf("\n %d \n",direction);
				mot_joueur[direction]=grille[*x_1erlettre-direction][*y_1erlettre-direction];
				direction+=1;
			}
		}



		/* Si la direction est 1 */
		else if ((*x_derlettre < *x_1erlettre) && (*y_derlettre == *y_1erlettre))	{
			while(*x_1erlettre-direction>=*x_derlettre){
				printf("\n %d \n",direction);
				mot_joueur[direction]=grille[*x_1erlettre-direction][*y_1erlettre];
				direction+=1;
			}				
		}



		/* Si la direction est 2 */ 
		else if ((*x_derlettre< *x_1erlettre) &&( *y_derlettre > *y_1erlettre)) {
			while(*x_1erlettre-direction>=*x_derlettre){
				printf("\n %d \n",direction);
				mot_joueur[direction]=grille[*x_1erlettre-direction][*y_1erlettre+direction];
				direction+=1;
			}
		}



		/* Si la direction est 3 */ 
		else if (( *x_derlettre == *x_1erlettre) && (*y_derlettre<*y_1erlettre)){
			while(*y_1erlettre-direction>=*y_derlettre){
				printf("\n %d \n",direction);
				mot_joueur[direction]=grille[*x_1erlettre][*y_1erlettre-direction];
				direction+=1;
			}
		}



		/* Si la direction est 4*/
		else if ( (*x_derlettre == *x_1erlettre) && (*y_derlettre>*y_1erlettre)){
			while(*y_1erlettre+direction<=*y_derlettre){
				printf("\n %d \n",direction);
				mot_joueur[direction]=grille[*x_1erlettre][*y_1erlettre+direction];
				direction+=1;
			}
		}


		/* Si la direction est 5*/
		else if ( (*x_derlettre > *x_1erlettre) && (*y_derlettre<*y_1erlettre)){
			while(*x_1erlettre+direction<=*x_derlettre){
				printf("\n %d \n",direction);
				mot_joueur[direction]=grille[*x_1erlettre+direction][*y_1erlettre-direction];
				direction+=1;
			}
		}



		/* Si la direction est 6*/
		else if ( (*x_derlettre > *x_1erlettre) && (*y_derlettre==*y_1erlettre)){
			while(*x_1erlettre+direction<=*x_derlettre){
				printf("\n %d \n",direction);
				mot_joueur[direction]=grille[*x_1erlettre+direction][*y_1erlettre];
				direction+=1;
			}
		}



		/* Si la direction est 7*/
		else if ( (*x_derlettre > *x_1erlettre) &&(*y_derlettre>*y_1erlettre)){
			while(*x_1erlettre+direction<=*x_derlettre){
				printf("\n %d \n",direction);
				mot_joueur[direction]=grille[*x_1erlettre+direction][*y_1erlettre+direction];
				direction+=1;
			}			
		}

		for(int i=0;i<taille;i++){
			printf("\n BON BON BON :%c",mot_joueur[i] );
		}
return 0;
}




int main(int argc,char const *argv[]){


	if (strcmp(argv[1], "-ac") == 0 || strcmp(argv[1], "-ca") == 0){

		int taille;
		printf("Veuillez rentrez la taille de la grille: \n" );
		scanf("%d", &taille);
		char tab[N][N];

		int nb_mots;
		do{
		printf("Veuillez rentrez le nombre de mots que vous souhaitez saisir (%d max) : \n",taille);
		scanf("%d", &nb_mots);
		}while(nb_mots> taille || nb_mots<1);

		char bibliotheque[N][N];



		afficher_coordonnee(tab[taille],taille);
		afficher_direction();

		init_grille(taille, tab);

		char mot[taille];
		int position_i,position_j, direction;

		mot_a_inserer(taille,nb_mots,tab,mot,position_i,position_j,direction,bibliotheque);
		remplir_grille(taille,tab);
		actualiser_grille(taille,tab);


		sauvegarde_fichier(argv,taille,nb_mots,tab,bibliotheque);

		afficher_bibliotheque(nb_mots,bibliotheque);

		int num_mot,x_1erlettre,x_derlettre,y_1erlettre,y_derlettre;

		joueur_saisie(&num_mot,&x_1erlettre,&y_1erlettre,&x_derlettre, &y_derlettre,nb_mots, taille);

		char mot_joueur[N];
		recuperation_mot(taille,nb_mots,tab, bibliotheque,mot_joueur,&num_mot,&x_1erlettre,&y_1erlettre,&x_derlettre, &y_derlettre);


	}
	return 0;

}