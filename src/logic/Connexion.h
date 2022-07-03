//
// Created by Mathis Saillot on 30/06/2022.
//

#ifndef HACKNSLPROJECT_CONNEXION_H
#define HACKNSLPROJECT_CONNEXION_H

#include <Station.h>
#include <json/json.h>
#include <vector>
#include <AbstractVisitor.h>

using namespace std;
using namespace Json;

class Connexion {
protected:
    int id_;
    bool tamise_;
    int stations_id[2];
    string concat_id_;
    vector<int> crossings;

public:

    Connexion(const Value & json_data, vector<Station> & stations);

    virtual ~Connexion();

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

    const string &getConcatId() const;

    DECLAREVISITMETHOD(Connexion)

};


#endif //HACKNSLPROJECT_CONNEXION_H
