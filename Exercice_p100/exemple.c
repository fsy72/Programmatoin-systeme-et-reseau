#include <stdio.h>
#include <unistd.h>

extern char *optarg;
extern int optopt;

int main(int argc, char *argv[]) {

    // declarer la variable qui recoit le code de l'option
    int opt;
    while((opt = getopt(argc, argv, "lm:nk:")) != -1) {
        switch(opt) {
            case 'l' :
            case 'n' :
                printf("L'option %c est fournir\n", opt);
                break;
            case 'm' :
            case 'k' :
                printf("L'option %c est fournir avec comme argument %s\n", opt, optarg);
                break;
            case ':' :
                printf("Erreur : L'option %c attend un argument\n",optopt);
                break;
            case '?' :
                printf("Erreur : option %c inconnue", optopt);
                break;
        }
    }

    return 0;
}