//
// Created by Mathis Saillot on 30/06/2022.
//

#include "StationType.h"

map<string, StationType> StationTypeParseur::dico;

string StationTypeParseur::list_names[NDIFFERENTTYPES] = {
        "joker", "circle", "triangle", "pentagon", "square"
};

bool StationTypeParseur::init = false;