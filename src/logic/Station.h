//
// Created by Mathis Saillot on 30/06/2022.
//

#ifndef HACKNSLPROJECT_STATION_H
#define HACKNSLPROJECT_STATION_H

#include <string>
#include <StationType.h>
#include <json/json.h>
#include <AbstractVisitor.h>
#include <FenetreMonde.h>

using namespace std;
using namespace Json;


class Station {
protected:
    string id_, concat_id;
    int int_id, zone_, row_, col_;
    bool tourist_;
    StationType type_;
    vector<int> liste_connexions;

public:

    explicit Station(const Value & json_input);

    virtual ~Station();

    const string &getId() const;

    const string &getConcatId() const;

    int getIntId() const;

    int getZone() const;

    int getRow() const;

    int getCol() const;

    bool isTourist() const;

    StationType getType() const;

    static string toString(const Station &station);

    explicit operator string() const;

    void addConnexion(int connexion_id);

    friend ostream &operator<<(ostream &os, const Station &station) {
        return os << (string) station;
    }

    DECLAREVISITMETHOD(Station)

};





#endif //HACKNSLPROJECT_STATION_H
