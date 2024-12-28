#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char*argv[]){

	if (argc<3){
		printf ("Erreur : Nombre d'argument insuffisant \n");
		printf ("usage : %s n nomfichier \n ", argv[0]);
		return 0;
	}

	int nmax = atoi (argv [1]);
	int fd = open( argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

	if (fd == -1){

		perror ("Erreur d'ouverture \n");
		return 0;

	}
	char textBuff [255];
	int nbWrite=0;
	for (int i =0; i<nmax;i++){
		sprintf (textBuff, "%d ", i);
		nbWrite = write (fd, textBuff, strlen (textBuff));
		if (nbWrite<=0){
			perror ("Erreur d'ouverture\n");
			return 0;
		}
	}
	close (fd);
	return 0;
}