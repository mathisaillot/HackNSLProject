//
// Created by Mathis Saillot on 30/06/2022.
//

#ifndef HACKNSLPROJECT_STATIONTYPE_H
#define HACKNSLPROJECT_STATIONTYPE_H

#include <map>
#include <string>

using namespace std;

enum StationType {
    JOKER = 0,
    CIRCLE = 1,
    TRIANGLE = 2,
    HEXAGONE = 3,
    SQUARE = 4,
    NDIFFERENTTYPES = 5
};

class StationTypeParseur {
protected:
    static map<string, StationType> dico;
    static string list_names[NDIFFERENTTYPES];
    static bool init;

    static void initDico()  {
        for (int i = 0; i < NDIFFERENTTYPES; ++i) {
            dico[list_names[i]] = (StationType)i;
        }
    }
public:
    static StationType getTypeFromString(const string & name) {
        if (!init) initDico();
        return dico[name];
    }

    static string getNameFromType(const StationType & type) {
        return list_names[type];
    }
};


#endif //HACKNSLPROJECT_STATIONTYPE_H
