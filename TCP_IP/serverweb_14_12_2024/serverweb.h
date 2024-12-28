#ifndef SERVERWEB_H
#define SERVERWEB_H

void affiche_socketaddr(struct sockaddr_in sockaddr);
void affiche_requete(char* bufferReceive);
int repondre_requete(int sock, char requete[]);
#endif // SERVERWEB_H