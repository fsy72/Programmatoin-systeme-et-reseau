#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main (int argc, char*argv[]){

	if (argc<2){
		printf ("Erreur : Nombre d'argument insuffisant \n");
		printf ("usage : %s nomfichier \n ", argv[0]);
		return 0;
	}

	int fd= open( argv[1], O_RDONLY);

	if (fd == -1){

		perror ("Erreur d'ouverture \n");
		return 0;

	}

	char buff;
	int nbRead=0;
	do {
		nbRead = read (fd, &buff, sizeof (char));
		if (nbRead >0) {
			printf ("%c", buff);
		}
	}while (nbRead>0);
	close (fd);
	return 0;
}