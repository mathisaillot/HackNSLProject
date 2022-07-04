//
// Created by Mathis Saillot on 04/07/2022.
//

#ifndef HACKNSLPROJECT_VISITORDESSINATEURFACTORY_H
#define HACKNSLPROJECT_VISITORDESSINATEURFACTORY_H

#include <VisitorFilter.h>
#include <VisitorDessinateur.h>
#include <Station.h>
#include <Connexion.h>

typedef bool (&ConnexionFilter)(const Connexion &);
bool testConnexionTamise(const Connexion & connexion);

class VisitorDessinateurFactory {
protected:
    FenetreMonde * fenetre;
public:
    explicit VisitorDessinateurFactory(FenetreMonde *fenetre) : fenetre(fenetre) {}

    VisitorDessinateurStation * getVisitorStationDefault();

    VisitorDessinateurStation * getVisitorStationDepart();

    VisitorDessinateurConnexion * getVisitorConnexionDefault();

    VisitorFilter<Connexion, ConnexionFilter> * getVisitorConnexionTamise();
};

#endif //HACKNSLPROJECT_VISITORDESSINATEURFACTORY_H
