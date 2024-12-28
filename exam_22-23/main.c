#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "archive.h"

extern char *optarg;
extern int optind, opterr, optopt;

int main(int argc, char *argv[]) {

    if(argc < 2) {
        printf("Erreur Nombre d'argumments insuffisant \n");
        printf("Usage: -f archive_name [-c] [ -r|-e file_name ] [-l] [file ...] %s\n", argv[0]);
        return 1;
    }
    char nom_archive[255]; char nom_fichier[255];
    int to_create = 0; int to_list = 0; int add_file = 0; int opt;

    while((opt = getopt(argc, argv, ":alcf:r:e:")) != -1) {
        switch(opt) {
            case -1: perror("Erreur "); break;
            case 'f':
                strcpy(nom_archive, optarg);
                break;
            case 'c':
                to_create = 1;
                break;
            case 'a':
                add_file = 1;
                break;
            case 'r':
                strcpy(nom_fichier, optarg);
                break;
            case 'e':
                strcpy(nom_fichier, optarg);
                break;
            case 'l':
                to_list = 1;
                break;
            case ':':
                printf("Option -%c n'a pas d'arguments.\n", optopt);
                break;
            case '?':
                printf("Option -%c inconnue.\n", optopt);
                break;
        }
    }

    if(to_create) { create_archive(nom_archive);}

    int i;
    if(add_file) {
        for(i = optind; i<argc; i++) {
            printf("Archivage de %s\n", argv[i]);
            archive_file(nom_archive, argv[i]);
        }
    }

    if(to_list) {
        show_files(nom_archive);
    }

    return 0;
}