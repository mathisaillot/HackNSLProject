/*
 *      Author: Dominique Michel
 */

#ifdef __APPLE__

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define SOCKADDR_IN struct sockaddr_in
#define SD_BOTH SHUT_RDWR
#define closesocket(a) close((a))

#else
#include <WinSock2.h>

#endif

#include "Erreur.h"
#include "MaConnexion.h"
#include "ClientTCP.h"

/*
class ClientTCP
{
SOCKET socket1;
public:
ClientTCP(const char * adresseServeur, const int portServeur);
~ClientTCP();
void envoie(const char * message);
template <int L>
void recoit(char messageRecu[L]);
void ferme();
};
*/


/**
 * connecte ce client au serveur (adresseServeur, portServeur)
 *
 *
 * Lance une Erreur en cas d'échec
 * */
ClientTCP::ClientTCP(const char *adresseServeur, const int portServeur) {
#ifdef _WIN32
    MaConnexion::getMaConnexion();          // initialisation de la librairie. Effectuée exactement une seule fois : MaConnexion est un singleton
    // création de l'adresse à requêter
#endif

    SOCKADDR_IN socketAddress;
    socketAddress.sin_addr.s_addr = inet_addr(adresseServeur);         // adresse du serveur à requêter

    if (socketAddress.sin_addr.s_addr == INADDR_NONE)
        throw Erreur("adresse invalide");

    socketAddress.sin_family = AF_INET;                                             // famille d'adresses, c'est le cas général, correspond à IP v4
    socketAddress.sin_port = htons(
            portServeur);                                   // port d'écoute du serveur à requêter

//struct sockaddr_in {
//      short   sin_family;
//      u_short sin_port;
//      struct  in_addr sin_addr;
//      char    sin_zero[8];

    socket1 = socket(AF_INET, SOCK_STREAM, 0);     // création du socket  SOCK_STREAM pour mode connecté (!= UDP)

#ifdef __APPLE__
    if (socket1 < 0)
#else
        if (socket1 == INVALID_SOCKET)
#endif
        erreurResultatWinsock("socket()");


    int r = connect(socket1, (const sockaddr *) &socketAddress, sizeof(socketAddress));

#ifdef __APPLE__
    if (r < 0)
#else
        if (r == SOCKET_ERROR)
#endif
        erreurResultatWinsock("connect()");

}

ClientTCP::~ClientTCP() { ferme(); }

/**
 *
 * DONNEES : *this, message[0], message[1], ..., message[m]
 * RESULTATS : n tel que message[0], message[1], ..., message[n] ont été effectivement envoyés, avec n <= m
 * TACHE : envoie message[0], message[1], ..., message[n] sur le socket
 *
 * Lance une Erreur en cas d'échec
 *
 * */
int ClientTCP::envoie(const char message[], const int m) {
    int l = m + 1;

    int r = send(socket1, message, l, 0);

//cout << "requête envoyée = " << message << endl;

#ifdef __APPLE__
    if (r < 0)
#else
        if (r == SOCKET_ERROR)
#endif
        erreurResultatWinsock("send()");

    return r - 1;
}

/**
 * Notons n, la valeur renvoyée par return
 * DONNEES : *this, m tel que les cases messageRecu[0], messageRecu[1], ..., messageRecu[m] existent
 * RESULTATS : messageRecu[0], messageRecu[1], ..., messageRecu[n] et n par return
 * TACHE : reçoit au plus m+1 octets et remplit le tableau messageRecu avec ces valeurs. Le nombre d'octets effectivement reçus est n+1 avec n <= m
 *
 * Lance une Erreur en cas d'échec
 *
 * */
int ClientTCP::recoit(char messageRecu[], const int m) {

    int r = recv(socket1, messageRecu, m + 1, 0);

#ifdef __APPLE__
    if (r < 0)
#else
        if (r == SOCKET_ERROR)
#endif
        erreurResultatWinsock("recv()");

    return r - 1;
}


void ClientTCP::ferme() {

    shutdown(socket1, SD_BOTH);
    closesocket(socket1);

}
