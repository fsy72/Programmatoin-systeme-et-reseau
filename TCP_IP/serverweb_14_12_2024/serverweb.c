#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include "serverweb.h"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Erreur : nombre d'arguments insuffisant\n");
        printf("Usage : %s  < PORT>\n", argv[0]);
        return 0; 
    }

    // 1. création de la socket
    int socketServer = socket(AF_INET, SOCK_STREAM, 0);
    if(socketServer == -1) {
        perror("Erreur de creation de la socket");
        return 0;
    }
    printf("[#Serveur web#] creation de la socket ........ OK\n");

    // 2. Initialiser la structure d'adresse
    struct sockaddr_in addServer;
    memset(&addServer, 0, sizeof(addServer));

    addServer.sin_family = AF_INET;
    addServer.sin_port = htons(atoi(argv[1]));
    addServer.sin_addr.s_addr = inet_addr("0.0.0.0");
    printf("[#Serveur web#] Initialisation de structure ................ OK\n");

    // 3. Nommage de la structure
    int resultat = bind(socketServer, (struct sockaddr*) &addServer, sizeof(struct sockaddr_in));
    if(resultat == -1) {
        perror("Erreur de nommage de la socket avec BIND ");
        return 0;
    }
    printf("[#Serveur web#] nommage de la socket avec BIND ........ OK\n");

    // 4. Appel de listen
    resultat = listen(socketServer, 5);
    if(resultat == -1) {
        perror("Erreur d'appel de listen ");
        return 0;
    }

    struct sockaddr_in addrClient;
    int taille_addr = sizeof(struct sockaddr_in);
    int socketClient;
    char buffReceive[8192];
    int nbReceive;
    //
    while(1) {
        socketClient = accept(socketServer, (struct sockaddr *)&addrClient, &taille_addr);

        affiche_socketaddr(addrClient);

        // initialiser le buffer
        memset(buffReceive, 0, 8192*sizeof(char));
        nbReceive = recv(socketClient, buffReceive, 8192*sizeof(char), 0);
        if(nbReceive < 0) {
            perror("Erreur de reception de la requete");
            return 0;
        }
        affiche_requete(buffReceive);
        reponse_requete(socketClient);
        close(socketClient);
    }
    
    return 0 ;
}

void affiche_socketaddr(struct sockaddr_in sockaddr) {
    printf("Client Accepté :\n");
    printf("==============================================\n");
    printf("Adresse IP : %s\n", inet_ntoa(sockaddr.sin_addr));
    printf("Numero de port %d \n", ntohs(sockaddr.sin_port));
    printf("==============================================\n");
}
void affiche_requete(char* bufferReceive) {
    printf("Requete du client :\n");
    printf("%s\n", bufferReceive);
    printf("==============================================\n");
}
int reponse_requete(int sock) {
    char reponse[8192] = "HTTP/1.1 200 OK\n\
Date :Sat, 14 Dec 2024 12:07:21 GMT\n\
Server: Apache UGB\n\
Content-Type: text/html; charset=UTF-8\n\
Content-Length: 50\n\
\n\
<h1>Bonjour le premier message du serveur :) </h1>";

    int nbsend = send(sock, reponse, strlen(reponse), 0);
    if(nbsend < 0) {
        perror("Erreur d'envoi de la reponse");
        return -1;
    }
    return 0;
}