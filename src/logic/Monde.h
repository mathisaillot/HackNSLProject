//
// Created by Mathis Saillot on 30/06/2022.
//

#ifndef HACKNSLPROJECT_MONDE_H
#define HACKNSLPROJECT_MONDE_H

#include <vector>
#include <string>
#include <Station.h>
#include <Connexion.h>
#include <FenetreMonde.h>
#include <AbstractVisitor.h>

using namespace std;

class Monde {

protected:
    vector<Station> liste_stations;
    vector<Connexion> liste_connexions;

public:

    Monde();

    virtual ~Monde();

    inline const vector<Station> & getListeStations() const {
        return liste_stations;
    }

    inline const vector<Connexion> & getListeConnexions() const {
        return liste_connexions;
    }

    inline unsigned long getNumberStation() const { return liste_stations.size(); }

    inline unsigned long getNumberConnexion() const { return liste_connexions.size(); }

    DECLAREVISITMETHOD(Monde)

};


#endif //HACKNSLPROJECT_MONDE_H
