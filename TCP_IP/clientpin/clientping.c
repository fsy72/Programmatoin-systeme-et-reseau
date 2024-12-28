#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>


int main(int argc, char *argv[]) {

    if(argc < 3) {
        printf("Erreur: nombre d'arguments insuffisant\n");
        printf("Usage: %s ADRESSE_IP PORT\n", argv[0]);
    }

    int socketClient = socket(AF_INET, SOCK_STREAM, 0);
    if(socketClient == -1) {
        perror("Erreur de creation de socket");
        return 0;
    }

    // 2.
    struct sockaddr_in addrServeur;
    memset(&addrServeur, 0, sizeof(struct sockaddr_in));
    addrServeur.sin_family = AF_INET;
    addrServeur.sin_port = htons(atoi(argv[2]));
    addrServeur.sin_addr.s_addr = inet_addr(argv[1]);

    // 3. Connect
    int resultat = connect(socketClient, (struct sockaddr *)&addrServeur, sizeof(struct sockaddr_in));
    if(resultat == -1) {
        perror("Erreur d'ouverture de la connnexion");
        return 0;
    }

    // 4. Logique de l'application
    char buffReceive[10];
    char buffSend[] = "Pong";
    int nbreceive = 0;
    int i = 0;
    while(1) {
        memset(buffReceive, 0, 10*sizeof(char));
        nbreceive = recv(socketClient, buffReceive, 10*sizeof(char), 0);
        if(nbreceive > 0) {
            printf("[%d]Client > Serveur %s\n", i, buffReceive);
        }
        sleep(1);
        send(socketClient, buffSend, strlen(buffSend), 0);
        printf("[%d]Client > Serveur %s\n", i, buffSend);
        i++;
    }
    close(socketClient);

    return 0;
}