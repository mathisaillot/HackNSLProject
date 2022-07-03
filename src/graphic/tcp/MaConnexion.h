/*
 *      Author: Dominique Michel
 */

#ifndef MACONNEXION_H_
#define MACONNEXION_H_

#ifdef __APPLE__
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#else
#include <WinSock2.h>
#endif

class MaConnexion
{
static MaConnexion * maConnexion;

MaConnexion();



public:

~MaConnexion();

/**Initialise exactement une fois la librairie Winsock2. Lance une Erreur en cas d'échec
 *
 *
 * */
static MaConnexion * getMaConnexion();
};

/**
 * Lance une Erreur contenant le texte défini par message et r
 *
 *
 * */
#ifdef __APPLE__
    void erreurResultatWinsock( const char * message, const int r = 0);
#else
    void erreurResultatWinsock( const char * message, const int r = WSAGetLastError());
#endif


#endif /* MACONNEXION_H_ */
