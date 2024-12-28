#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>

int main(int argc, char const *argv[])
{
    //creation de socket TCP
   int socketTCP= socket (AF_INET , SOCK_STREAM ,0);

   if(socketTCP==-1)
   {
       perror("Erreur de creation de la socket TCP");
        return 0;

   }

     printf("Creation de la socket TCP avec succes \n");


    //creation de socket UDP
   int socketUDP= socket (AF_INET , SOCK_DGRAM ,0);

   if(socketUDP==-1)
   {
       perror("Erreur de creation de la socket TCP");
        return 0;

   }

     printf("Creation de la socket UDP avec succes \n");




      return 0;
}










