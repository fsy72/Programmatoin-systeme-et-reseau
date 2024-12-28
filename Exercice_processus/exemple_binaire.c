#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    pid_t pid1, pid2;
    int profondeur = 0;
    for(int nb_fils=0; nb_fils<2; ) {
        pid1 = fork();
        switch(pid1) {
            case -1:
                perror("Erreur");
                break;
            case 0:
                printf("%d -> %d;\n", getppid(), getpid());
                profondeur++;
                if(profondeur > 3) {
                    return 0;
                }
                nb_fils = 0;
                break;
            default:
                wait(NULL);
                nb_fils++;
                if(nb_fils >= 2) {
                    return 0;
                }
        }
    }
    return 0;
}