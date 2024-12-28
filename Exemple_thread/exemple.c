#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>

int compteurPrincipale = 0, compteurSecondaire = 0, compteurTertiaire = 0;
int i = 0;

void *fthreadsecondaire(void *arg) {
    while(1) {
        printf("%3d %3d %3d %3d\r", i++, compteurPrincipale, compteurSecondaire++, compteurTertiaire);
        // sleep(1);
    }
    pthread_exit(NULL);
}
void *fthreadtertiaire(void *arg) {
    while(1) {
        printf("%3d %3d %3d %3d\r", i++, compteurPrincipale, compteurSecondaire++, compteurTertiaire++);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

    pthread_t th1, th2;
    int resultat = pthread_create(&th1, NULL, fthreadsecondaire, (void*)NULL);
    if(resultat==-1) {
        perror("Error thread secondaire");
    }

    resultat = pthread_create(&th2, NULL, fthreadtertiaire, (void*)NULL);
    if(resultat==-1) {
        perror("Error thread secondaire");
    }

    while(1) {
        printf("%3d %3d %3d %3d\r", i++, compteurPrincipale++, compteurSecondaire, compteurTertiaire);
    }
    // pthread_join(th1, NULL);
    return 0;
}