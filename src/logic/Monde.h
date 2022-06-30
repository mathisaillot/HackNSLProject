//
// Created by Mathis Saillot on 30/06/2022.
//

#ifndef HACKNSLPROJECT_MONDE_H
#define HACKNSLPROJECT_MONDE_H

#include <vector>
#include <string>
#include <Station.h>
#include <Connexion.h>

using namespace std;

class Monde {

protected:
    vector<Station> liste_stations;
    vector<Connexion> liste_connexions;

public:

    Monde();

    inline const vector<Station> & getListeStations() const {
        return liste_stations;
    }

};


#endif //HACKNSLPROJECT_MONDE_H
