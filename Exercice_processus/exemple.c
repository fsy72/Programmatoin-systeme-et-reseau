#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    pid_t pid1;
    int i = 0;
    while(i<10) {
        pid1 = fork();
        switch(pid1) {
            case -1:
                perror("Erreur");
                break;
            case 0:
                printf("%d -> %d;\n", getppid(), getpid());
                break;
            default:
                wait(NULL);
                return 0;
        }
        i++;
    }

    return 0;
}