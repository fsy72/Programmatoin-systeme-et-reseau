#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>

int compteurPrincipale = 0, compteurSecondaire = 0, compteurTertiaire = 0;
int i = 0, compteur = 0;

sem_t sem_se, sem_te;

void *fthreadsecondaire(void *arg) {
    while(1) {
        sem_wait(&sem_se);
        printf("%d %10d\n", i++, compteur++);
        sem_post(&sem_te);
    }
    pthread_exit(NULL);
}
void *fthreadtertiaire(void *arg) {
    while(1) {
        sem_wait(&sem_te);
        printf("%d %10d\n", i++, compteur--);
        sem_post(&sem_se);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

    int resultat = sem_init(&sem_se, 0, 10);
    if(resultat==-1) {
        perror("Error semaphore secondaire");
    }

    resultat = sem_init(&sem_te, 0, 0);
    if(resultat==-1) {
        perror("Error semaphore tertiaire");
    }

    pthread_t th1, th2;
    resultat = pthread_create(&th1, NULL, fthreadsecondaire, (void*)NULL);
    if(resultat==-1) {
        perror("Error thread secondaire");
    }

    resultat = pthread_create(&th2, NULL, fthreadtertiaire, (void*)NULL);
    if(resultat==-1) {
        perror("Error thread tertiaire");
    }

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    sem_destroy(&sem_te);
    sem_destroy(&sem_se);
    return 0;
}