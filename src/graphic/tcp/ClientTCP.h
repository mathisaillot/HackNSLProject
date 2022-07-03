/*
 *      Author: Dominique Michel
 */

#ifndef CLIENTTCP_H_
#define CLIENTTCP_H_


#ifdef __APPLE__

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define SOCKADDR_IN struct sockaddr_in
#define SD_BOTH SHUT_RDWR
#define SOCKET int
#else
#include <WinSock2.h>
#endif

class ClientTCP {
    SOCKET socket1;
public:

/**
 * connecte ce client au serveur (adresseServeur, portServeur)
 *
 *
 * Lance une Erreur en cas d'échec
 * */
    ClientTCP(const char *adresseServeur, const int portServeur);

    ~ClientTCP();

/**
 *
 * DONNEES : *this, message[0], message[1], ..., message[m]
 * RESULTATS : n tel que message[0], message[1], ..., message[n] ont été effectivement envoyés, avec n <= m
 * TACHE : envoie message[0], message[1], ..., message[n] sur le socket
 *
 * Lance une Erreur en cas d'échec
 * */
    int envoie(const char message[], const int m);

/**
 * Notons n, la valeur renvoyée par return
 * DONNEES : *this, m tel que les cases messageRecu[0], messageRecu[1], ..., messageRecu[m] existent
 * RESULTATS : messageRecu[0], messageRecu[1], ..., messageRecu[n] et n par return
 * TACHE : reçoit au plus m+1 octets et remplit le tableau messageRecu avec ces valeurs. Le nombre d'octets effectivement reçus est n+1 avec n <= m
 *
 *
 * Lance une Erreur en cas d'échec
 * */
    int recoit(char messageRecu[], const int m);

    void ferme();
};

#endif /* CLIENTTCP_H_ */
