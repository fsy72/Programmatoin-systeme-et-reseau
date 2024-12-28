#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    pid_t pid1, pid2;
    int i = 0;
    while(i<10) {
        pid1 = fork();
        switch(pid1) {
            case -1:
                perror("Erreur");
                break;
            case 0:
                printf("%d -> %d;\n", getppid(), getpid());
                return 0;
            default:
                wait(NULL);
        }
        i++;
    }
    return 0;
}