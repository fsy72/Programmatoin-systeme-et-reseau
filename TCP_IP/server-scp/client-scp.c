#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include "utils.h"


int main(int argc, char *argv[]) {

    if(argc < 4) {
        printf("Erreur: nombre d'arguments insuffisant\n");
        printf("Usage: %s ADRESSE_IP PORT FICHIER\n", argv[0]);
    }
    
    // connexion au serveur
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

    // 4. copie
    // 4.1 récuperer les informations du fichiers

    struct stat stfile;
    stat(&stfile);

    // Envoyer OK ou NOK
    struct infofile info;
    info.taille = stfile.st_size;
    info.mode = stfile.st_mode;
    strcpy(info.nomfichier, argv[3]);

    int ndsend = send(socketClient, &info, sizeof(struct infofile), 0);

    if(nbsend <= 0) {
        perror("Erreur d'envoi des données du fichier");
        return 0;
    }

    char buffRecv[255];
    memset(buffRecv, 0, 255*sizeof(char));
    recv(socketClient, buffRecv, 255*sizeof(char), 0);

    if(strcmp(buffRecv, "OK") != 0) {
        perror("Erreur de creation du fichier distance");
        return 0;
    }

    close(socketClient);
    return 0;
}