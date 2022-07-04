//
// Created by Mathis Saillot on 04/07/2022.
//

#include "VisitorDessinateurFactory.h"

VisitorDessinateurStation * VisitorDessinateurFactory::getVisitorStationDefault() {
    return new VisitorDessinateurStation(fenetre,
                                         0.2,
                                         (Couleur)"Black",
                                         (Couleur)"White");
}

VisitorDessinateurStation * VisitorDessinateurFactory::getVisitorStationDepart() {
    return new VisitorDessinateurStation(fenetre);
}

VisitorDessinateurConnexion * VisitorDessinateurFactory::getVisitorConnexionDefault() {
    return new VisitorDessinateurConnexion(fenetre, (Couleur)"Black", 1);
}

VisitorFilter<Connexion, ConnexionFilter> * VisitorDessinateurFactory::getVisitorConnexionTamise() {
    return new VisitorFilter<Connexion, ConnexionFilter>(
            new VisitorDessinateurConnexion(fenetre, (Couleur) "Cyan", 2),
            getVisitorConnexionDefault(),
            testConnexionTamise);
}

bool testConnexionTamise(const Connexion & connexion) {
    return connexion.crossTamise();
}