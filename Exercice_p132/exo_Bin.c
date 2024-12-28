#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main (int argc, char*argv[]){

	if (argc<3){
		printf ("Erreur : Nombre d'argument insuffisant \n");
		printf ("usage : %s nomfichier \n ", argv[1]);
		return 0;
	}

	int nmax= atoi (argv [1]);
	int fd= open( argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

	if (fd == -1){

		perror ("Erreur d'ouverture \n");
		return 0;

	}
	char buff;
	int nbWrite = 0;
	for (int i = 0; i<nmax;i++){
		nbWrite = write (fd, &i, sizeof (int));
		if (nbWrite<=0){
			perror ("Erreur d'ouverture\n");
			return 0;
		}
	}

	close (fd);


return 0;
}