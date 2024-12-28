#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[], char *arge[]) {

    char *argvbis[] = {
        "ls",
        "-l",
        "-a",
        (char*) NULL
    };

    printf("Nouvelle commande ls\n");
    // execlp("ls","ls","-l","-a",(char*) 0);
    // execvp("ls", argvbis);
    execve("/ls", argvbis, arge);
    printf("Erreur d'execution de exec\n");

    return 0;
}