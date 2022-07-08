//
// Created by Mathis Saillot on 04/07/2022.
//

#include "VisitorDessinateurFactory.h"

VisitorDessinateurStation * VisitorDessinateurFactory::getVisitorStationDefault() {
    return new VisitorDessinateurStation(fenetre,
                                         (Couleur) "Black",
                                         (Couleur) "White",
                                         0.2, 0.3);
}

AbstractVisitor<Station> * VisitorDessinateurFactory::getVisitorStationDepart(const Monde &monde) {

    AbstractVisitor<Station> * visitor = getVisitorStationDefault();
    for (int i = 0; i < PENCOLORNUMBER; ++i) {
        auto pen = (PenColor) i;
        visitor = new VisitorFilter<Station, StationFilter>(
                new VisitorDessinateurStation(fenetre, (Couleur) pen),
                visitor,
                getFilterById(monde.getIdStationDepart(pen))
                );
    }
    return visitor;
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

StationFilter getFilterById(int id) {
    return [=](const Station & a){ return a.getIntId() == id;};
}