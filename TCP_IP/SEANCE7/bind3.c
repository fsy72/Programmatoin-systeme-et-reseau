#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
        if(argc < 2)
    {

     printf("Erreur : nombre d'argument insuffisant\n");
     printf("Usage : %s  PORT \n",argv[0]);
    return 0;

    }

    //creation de socket TCP
   int socketServeurTCP= socket (AF_INET , SOCK_STREAM ,0);

   if(socketServeurTCP==-1)
   {
       perror("Erreur de creation de la socket TCP");
        return 0;

   }

     printf("Creation de la socket TCP avec succes \n");

        struct sockaddr_in addrServer;

          memset(&addrServer , 0, sizeof(struct sockaddr_in));

        addrServer.sin_family =AF_INET;
        addrServer.sin_port= htons(atoi(argv[1]));
        addrServer.sin_addr.s_addr=inet_addr("0.0.0.0");


       //3. Appel de bind

      int resultat =bind(socketServeurTCP,(struct sockaddr *) &addrServer,  sizeof(struct sockaddr_in));


       resultat=listen(socketServeurTCP,5);
       if(resultat==-1)
      {
       perror("Erreur de lancement de listen");
        return 0;
     }


      printf("Execution de listen avec succes \n");

     //accept
     //Declare la structure qui va contenir l'adresse distante
       struct sockaddr_in addrClient;
      int taille=sizeof(struct sockaddr_in);

      int socketClientTCP;

      //buffers
       char buffSend[]="Png";
       char buffReceive[10];

       while(1){

       socketClientTCP=accept(socketServeurTCP, (struct sockaddr *) &addrClient , &taille);
       printf("Connexion acceptee pour le client %s :  %d \n",   inet_ntoa(addrClient.sin_addr), ntohs(addrClient.sin_port) );

     


       //envoyer ping
       send(socketClientTCP, buffSend ,strlen(buffSend) ,0);
       printf("[#Serveur# %d] (Server) %s:%d > %s:%d (Server) %s \n", i,
          inet_ntoa(addrServer.sin_addr), ntohs(addrServer.sin_port),
          inet_ntoa(addrClient.sin_port), ntohs(addrClient.sin_port),
          buffSend
        );

        sleep(1);

       memset(buffReceive,0,10);
       recv(socketClientTCP, buffReceive , 5 * sizeof(char), 0 );

       printf("[#Serveur# %d] (Server) %s:%d > %s:%d \n", i,
          inet_ntoa(addrClent.sin_addr), ntohs(addrClent.sin_port),
          inet_ntoa(addrServer.sin_port), ntohs(addrServer.sin_port),
          buffReceive
        );
}
      close(socketClientTCP);



    return 0;

}