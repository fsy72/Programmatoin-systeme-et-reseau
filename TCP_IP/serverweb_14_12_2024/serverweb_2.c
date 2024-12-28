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
#include <fcntl.h>
#include <sys/stat.h>
#include "serverweb.h"

char *RACIN_SITE = "/home/kali/Desktop/Prog.SR/TCP_IP/serverweb_14_12_2024";

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
        repondre_requete(socketClient, buffReceive);
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
int repondre_requete(int sock, char requete[]) {

    char requeteTmp[8192];
    strcpy(requeteTmp, requete);
    printf("++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("RequeteTemp : %s\n", requeteTmp);
    printf("++++++++++++++++++++++++++++++++++++++++++++++\n");
    char templateEntete[8192] = "HTTP/1.1 200 OK\n\
Date :Sat, 14 Dec 2024 12:07:21 GMT\n\
Server: Apache UGB\n\
Content-Type: %s\n\
Content-Length: %d\n\
\n";

    char *nomFichierRecu = strtok(requeteTmp, " ");
    nomFichierRecu = strtok(NULL, " ");
    char nomFichierComplet[255]; // contiendra le cheùin absolu local du fichier
    char extensionFichier[100];

    if(strcmp(nomFichierRecu, "/") == 0) {
        sprintf(nomFichierComplet, "%s%sindex.html", RACIN_SITE, nomFichierRecu);
        strcpy(extensionFichier, "html");
    } else { // cas ou le nom du fichier est spécifié
        sprintf(nomFichierComplet, "%s%s", RACIN_SITE, nomFichierRecu);
        strcpy(requeteTmp, nomFichierRecu);
        strcpy(extensionFichier, strtok(requeteTmp, "."));
        strcpy(extensionFichier, strtok(NULL, "."));
    }

    printf("Nom fichier complet: %s\n", nomFichierComplet);

    char typeMime[255]; // type MIME à spécifier sur la réponse
    if(strcmp(extensionFichier, "html") == 0) {
        strcpy(typeMime, "application/xhtml+xml");
    } else if(strcmp(extensionFichier, "pdf") == 0) {
        strcpy(typeMime, "application/pdf");
    } else if(strcmp(extensionFichier, "mp4") == 0) {
        strcpy(typeMime, "video/mp4");
    } else if(strcmp(extensionFichier, "image/png") == 0) {
        strcpy(typeMime, "image/png");
    }

    struct stat stfile;
    stat(nomFichierComplet, &stfile);
    char reponseComplet[8192];
    sprintf(reponseComplet, templateEntete, typeMime, stfile.st_size);

    printf("Reponse %s\n", reponseComplet);
    int nbsend = send(sock, reponseComplet, strlen(reponseComplet), 0);

    if(nbsend < 0) {
        perror("Erreur d'envoi de la reponse ");
        return -1;
    }

    int fd = open(nomFichierComplet, O_RDONLY);
    if(fd == -1) {
        perror("Erreur d'ouverture du fichier ");
        return 0;
    }
    char buffRead[1048576];
    int nbRead, nbReadTotal = 0;
    do {
        nbRead = read(fd, buffRead, 1048576*sizeof(char));
        if(nbRead > 0) {
            nbsend = send(sock, buffRead, nbRead*sizeof(char), 0);
            if(nbsend < 0) {
                perror("Erreur d'envoi de la reponse ");
                return -1;
            }
            nbReadTotal += nbsend;
            printf("========> %d\n", nbReadTotal);
        }
    }while(nbRead > 0);

    close(fd);

    // int nbsend = send(sock, reponse, strlen(reponse), 0);
    // if(nbsend < 0) {
    //     perror("Erreur d'envoi de la reponse");
    //     return -1;
    // }
    return 0;
}