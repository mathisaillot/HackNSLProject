//
// Created by Mathis Saillot on 30/06/2022.
//

#ifndef HACKNSLPROJECT_STATIONTYPE_H
#define HACKNSLPROJECT_STATIONTYPE_H

#include <map>
#include <string>
#include <OutilsEnum.h>

using namespace std;

ENUMBUILDER(StationType,
            JOKER = 0 VIRGULE\
            CIRCLE = 1 VIRGULE\
            TRIANGLE = 2 VIRGULE\
            PENTAGONE = 3 VIRGULE\
            SQUARE = 4 VIRGULE \
            STATIONTYPESNUMBER = 5,
            STATIONTYPESNUMBER)


#endif //HACKNSLPROJECT_STATIONTYPE_H
