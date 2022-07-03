/*
 *      Author: Dominique Michel
 */

#include <sstream>
#ifdef _WIN32
    #include <WinSock2.h>
#endif
#include "Erreur.h"
#include "MaConnexion.h"

using namespace std;

/*static*/ MaConnexion * MaConnexion :: maConnexion = NULL;


MaConnexion::MaConnexion()
{
#ifdef _WIN32
    WSADATA wsadata; // initialisation de quoi au juste ? chargement de la dll

int r = WSAStartup(MAKEWORD(2,0),&wsadata); // initialisation des ressources nécessaires à ouvrir un socket avec la librairie winsock2

// si tout s'est bien passé, retourne 0

if (r)  // si r est non nul, il indique un n° d'erreur
   erreurResultatWinsock( "WSAStartup()", r);
#endif


}

/**Initialise exactement une fois la librairie Winsock2. Lance une Erreur en cas d'échec
 *
 *
 * */
/*static*/ MaConnexion * MaConnexion :: getMaConnexion()
{
if (!maConnexion) maConnexion = new MaConnexion();

return maConnexion;
}


MaConnexion::~MaConnexion()
{
#ifdef _WIN32
WSACleanup(); // libère les ressources requisitionnées par WSAStartup()
#endif
}

/**
 * Lance une Erreur contenant le texte défini par message et r
 *
 *
 * */

void erreurResultatWinsock( const char * message, const int r)
{
ostringstream oss;
oss << "l'appel à "<< message << " échoue, code d'erreur détaillé = " << r;
throw Erreur(oss.str());
}
