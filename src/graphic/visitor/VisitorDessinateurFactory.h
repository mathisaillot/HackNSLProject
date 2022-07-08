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
typedef function<bool(const Station &)> StationFilter;

bool testConnexionTamise(const Connexion & connexion);

StationFilter getFilterById(int id);

class VisitorDessinateurFactory {
protected:
    FenetreMonde * fenetre;
public:
    explicit VisitorDessinateurFactory(FenetreMonde *fenetre) : fenetre(fenetre) {}

    VisitorDessinateurStation * getVisitorStationDefault();

    AbstractVisitor<Station> * getVisitorStationDepart(const Monde &monde);

    VisitorDessinateurConnexion * getVisitorConnexionDefault();

    VisitorFilter<Connexion, ConnexionFilter> * getVisitorConnexionTamise();
};

#endif //HACKNSLPROJECT_VISITORDESSINATEURFACTORY_H
