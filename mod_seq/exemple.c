#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char *optarg;
extern int optopt;

int main(int argc, char *argv[]) {

    // declarer la variable qui recoit le code de l'option
    int opt;
    int pas = 1;
    int nmax = 0;
    while((opt = getopt(argc, argv, ":n:p:")) != -1) {
        switch(opt) {
            case 'n' :
                nmax = atoi(optarg);
                break;
            case 'p' :
                pas = atoi(optarg);
                break;
            case ':' :
                printf("Erreur : L'option %c attend un argument\n",optopt);
                break;
            case '?' :
                printf("Erreur : option %c inconnue", optopt);
                break;
        }
    }
    for(int i=0; i<=nmax; i+=pas)
        printf("%d\n",i);

    return 0;
}