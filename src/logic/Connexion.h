//
// Created by Mathis Saillot on 30/06/2022.
//

#ifndef HACKNSLPROJECT_CONNEXION_H
#define HACKNSLPROJECT_CONNEXION_H


#include <Station.h>
#include <json/json.h>
#include <vector>

using namespace std;
using namespace Json;

class Connexion {
protected:
    int id_;
    bool tamise_;
    int stations_id[2];
    vector<int> crossings;

public:

    inline int getId() const {
        return id_;
    }

    inline bool crossTamise() const {
        return tamise_;
    }

    inline const int * getStationsId() const {
        return stations_id;
    }

    inline const vector<int> &getCrossings() const {
        return crossings;
    }

};


#endif //HACKNSLPROJECT_CONNEXION_H
