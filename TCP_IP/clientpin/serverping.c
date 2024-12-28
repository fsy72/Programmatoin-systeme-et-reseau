#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h> 

//pour tester : nc 0.0.0.0 port


int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Erreur : aucun fichier spécifié\n");
        printf("Usage : %s  < PORT>\n", argv[0]);
        return 1; 
    }

    //creation socket TCP
    int socketServerTCP = socket(AF_INET , SOCK_STREAM , 0) ;
    
    if(socketServerTCP == -1){
        perror("Erreur! creation socket TCP" ) ;
    }
        
    printf("Creation socketTCP reussie 🥳 \n");	

    //init de la struct de nommage du server
    struct sockaddr_in addrServer;
    memset(&addrServer, 0, sizeof(struct sockaddr_in));
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(atoi(argv[1]));
    addrServer.sin_addr.s_addr = inet_addr("0.0.0.0");


    //nommage du server avec bind

    int result = bind(socketServerTCP, (struct sockaddr*) &addrServer, sizeof(struct sockaddr_in));

    if(result==-1){
        perror("Error de bind");
        exit(1);
    }

    printf("Execution bind success 🥳 \n");

    result = listen(socketServerTCP, 5);

    if(result==-1){
        perror("Error de Listen");
        exit(1);
    }
    printf("Execution de listen success 🥳 \n");

    //adresse du client distant
    struct sockaddr_in addrClient;
    //taille de l adress du client distant
    int tailleAddrClient = sizeof(addrClient);
    //socket secondaire
    int socketClientDistant = accept(socketServerTCP, (struct sockaddr*) &addrClient, &tailleAddrClient);

    if(socketClientDistant == -1){
    perror("socketClientDistant error");
    exit(1);
    }

    printf("Connexion du client %s:%d reussie\n", inet_ntoa(addrClient.sin_addr), ntohs(addrClient.sin_port));

    char buffReceive[10];
    char buffSend[] = "ping";

    int nbRcv;
    int nbSend;
    int i = 0 ;


    while(1){
        //envoyer ping
        nbSend = send(socketClientDistant, buffSend, strlen(buffSend) , 0);
        printf("[Server# %d] (Serveur) %s:%d --> %s : %d  %d \n", i, 
            inet_ntoa(addrServer.sin_addr), ntohs(addrServer.sin_port) ,
            inet_ntoa(addrClient.sin_addr), ntohs(addrClient.sin_port), 
            buffSend);
        sleep(1);

        //recevoir pong
        memset(buffReceive , 0 ,10) ;
        nbRcv = recv(socketClientDistant, buffReceive, 5*sizeof(char), 0);
        printf("[Server# %d] %s:%d --> %s : %d  (Serveur)  %s\n", i, 
            inet_ntoa(addrClient.sin_addr), ntohs(addrClient.sin_port), 
            inet_ntoa(addrServer.sin_addr), ntohs(addrServer.sin_port) ,
            buffReceive);
            
        // printf("Donnee recu : %s \n",buffReceive) ;
        // printf("[%d] Serveur >client : %s", i ,buffSend);
        i++ ;
    }
    return 0 ;
}
