#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
int main (int argc, char*argv[]){

	if (argc<3){
			printf ("Erreur : Nombre d'argument insuffisant \n");
			printf ("usage : %s source destination\n ", argv[1]);
			return 0;
		}
	int fdSrc= open (argv[1], O_RDONLY);

	if (fdSrc == -1){

		perror ("Erreur d'ouverture \n");
		return 0;
	}
	printf ("Ouverture du fichier source avec succes \n");

	struct stat stFichierSrc;
	int resultat = fstat (fdSrc, &stFichierSrc);

	if (resultat==-1){
		perror ("Erreur de recuperation des informations sur le fichier source");
		return 0;
	}

	printf ("taille %d\n", stFichierSrc.st_size);
	printf ("Permission: %o\n", stFichierSrc.st_mode);

	int fdDest= open (argv[3], O_WRONLY | O_CREAT, stFichierSrc.st_mode);
	if (fdDest == -1){

		perror ("Erreur d'ouverture \n");
		return 0;
	}

	printf ("creation  du fichier destination avec succes \n");


	char Buff;
	int nbread , nbWrite;
	int nbTotal=0;

	do{
		nbread= read (fdSrc, &Buff, sizeof (char));
		if (nbread>0){
			nbWrite= write (fdDest, &Buff, sizeof (char));
			if (nbWrite <=0){
				perror ("Erreur d'ecriture \n");
				return 0;
			}
			else{
				nbTotal = nbTotal + nbWrite;
				printf ("\r%.4f%%", 100.0 * nbtotal / stFichierSrc.st_size);

			}


		}
	}while (nbread >0);
	close (fdSrc);
	close (fdDst);q

	return 0;
}