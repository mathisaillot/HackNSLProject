/*
 *      Author: Dominique Michel
 */

#ifndef CLIENTTCPSTRING_H_
#define CLIENTTCPSTRING_H_

#include <string>

#include "ClientTCP.h"

using namespace std;

class ClientTCPString : public ClientTCP {
public:

    static int LONGUEURMAXMESSAGE;
    static int L; // tel que L = LONGUEURMAXMESSAGE-1


    ClientTCPString();

/**
 * connecte ce client au serveur (adresseServeur, portServeur)
 *
 *
 * Lance une Erreur en cas d'échec
 * */
    ClientTCPString(const char *adresseServeur, const int portServeur) : ClientTCP(adresseServeur, portServeur) {}

/**
 * connecte ce client au serveur (adresseServeur, portServeur)
 *
 *
 * Lance une Erreur en cas d'échec
 * */
    ClientTCPString(const string &adresseServeur, const int portServeur) : ClientTCPString(adresseServeur.c_str(),
                                                                                           portServeur) {}


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
    bool envoie(const char *message);


/**
 *
 * DONNEES : *this, message
 * RESULTATS : un booléen indiquant si l'envoi a été effectué complètement
 * TACHE : envoie message sur le socket
 *
 * message est d'abord complété par "\r\n" avant l'envoi
 *
 * le caractère '\0' de fin n'est pas envoyé
 *
 * Lance une Erreur en cas d'échec
 * */
    bool envoie(const string &message) { return envoie(message.c_str()); }


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
    const string recoit();

};

#endif /* CLIENTTCPSTRING_H_ */
