#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// extern char *optarg;
// extern int optopt;
// extern int optind; // l'index du premier element de argv qui n'est ni option ni parametre d'option

int main(int argc, char const *argv[]) {

    int fd = open(argv[1], O_RDONLY);
    if(fd==-1) {
        perror("Erreur d'ouverture en lecture seule");
    }
    else {
        printf("Ouverture en lecture seule OK\n");
    }
    close(fd);

    fd = open(argv[1], O_WRONLY);
    if(fd==-1) {
        perror("Erreur d'ouverture en ecriture seule");
    }
    else {
        printf("Ouverture en ecriture seule OK\n");
    }
    close(fd);

    fd = open(argv[1], O_RDWR);
    if(fd==-1) {
        perror("Erreur d'ouverture en lecture-ecriture");
    }
    else {
        printf("Ouverture en lecture-ecriture OK\n");
    }
    close(fd);

    return 0;
}