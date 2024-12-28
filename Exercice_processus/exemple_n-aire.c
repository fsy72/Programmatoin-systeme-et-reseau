#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char *optarg;

int main(int argc, char *argv[]) {

    if(argc < 3 || argc > 5){
        printf("Usage: %s -n 1 -k 1", argv[0]);
        exit(-1);
    } 
    int opt;
    int niveau = 1;
    int nb_fils = 1;
    while((opt = getopt(argc, argv, ":n:k:")) != -1) {
        switch(opt) {
            case 'n':
                niveau = atoi(optarg) - 2;
                break;
            case 'k':
                nb_fils = atoi(optarg);
                break;
            // case ':':
            case '?':
                fprintf(stderr, "Option inconnue ou argument manquant\n");
                printf("Usage: %s -n 3 -k 2", argv[0]);
                return 1;
        }
    }
    pid_t pid1, pid2;
    int profondeur = 0;
    for(int i=0; i<nb_fils; ) {
        pid1 = fork();
        switch(pid1) {
            case -1:
                perror("Erreur");
                break;
            case 0:
                printf("%d -> %d;\n", getppid(), getpid());
                profondeur++;
                if(profondeur > niveau) {
                    return 0;
                }
                i = 0;
                break;
            default:
                wait(NULL);
                i++;
                if(i >= nb_fils) {
                    return 0;
                }
        }
    }
    return 0;
}