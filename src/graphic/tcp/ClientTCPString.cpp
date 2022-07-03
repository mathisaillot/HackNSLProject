/*
 *      Author: Dominique Michel
 */

#include "Erreur.h"
#include "ClientTCPString.h"


/*static*/ int ClientTCPString::LONGUEURMAXMESSAGE = 100;
/*static*/ int ClientTCPString::L = ClientTCPString::LONGUEURMAXMESSAGE - 1;


/**
 *
 * DONNEES : *this, message
 * RESULTATS : un booléen indiquant si l'envoi a été effectué complètement
 * TACHE : envoie message sur le socket
 *
 * message est d'abord complété par "\r\n" avant l'envoi
 * le caractère '\0' de fin n'est pas envoyé
 * Lance une Erreur en cas d'échec
 * */
/*bool ClientTCPString::envoie(const string & message)
{
int l = message.length();
char * paquet = new char[l+3];
strcpy(paquet,message.c_str());
strcat(paquet,"\r\n");
int m = l+1;
int r = this->ClientTCP::envoie(paquet,m);     // on envoie l+2 caractères qui sont numérotés de 0 à l+1

delete[] paquet;

//int envoie(const char message[], const int m);

return r == m;
}*/

/*
 bool ClientTCPString::envoie(const string & message)
{
int l = message.length();
char * paquet = new char[l+3];
strcpy(paquet,message.c_str());
strcat(paquet,"\r\n");
int m = l+1;
int r = this->ClientTCP::envoie(paquet,m);     // on envoie l+2 caractères qui sont numérotés de 0 à l+1

delete[] paquet;

//int envoie(const char message[], const int m);

return r == m;
}
*/

/**
 *
 * DONNEES : *this, message
 * RESULTATS : un booléen indiquant si l'envoi a été effectué complètement
 * TACHE : envoie message sur le socket
 *
 * message est d'abord complété par "\r\n" avant l'envoi
 * le caractère '\0' de fin n'est pas envoyé
 * Lance une Erreur en cas d'échec
 * */
bool ClientTCPString::envoie(const char *message) {
    int l = strlen(message);
    char *paquet = new char[l + 3];
    strcpy(paquet, message);
    strcat(paquet, "\r\n");
    int m = l + 1;
    int r = this->ClientTCP::envoie(paquet, m);     // on envoie l+2 caractères qui sont numérotés de 0 à l+1

    delete[] paquet;

//int envoie(const char message[], const int m);

    return r == m;
}

/**
 * DONNEES : *this
 * RESULTATS : une chaîne par return
 *
 * On suppose que la chaîne reçue finit par "\r\n"
 *
 * La fin de chaîne "\r\n" n'est PAS incluse dans le résultat
 *
 * Lance une Erreur en cas d'échec
 * */
const string ClientTCPString::recoit() {
    char paquet[LONGUEURMAXMESSAGE];

    int r = this->ClientTCP::recoit(paquet, L);
    int m = r - 1;
    if (paquet[r] != '\n') throw Erreur(" dans ClientTCPString::recoit() : la chaîne reçue ne termine pas par \"\n\"");

    paquet[r] = '\0';

    return string(paquet);
}

