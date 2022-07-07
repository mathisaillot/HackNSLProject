//
// Created by Mathis Saillot on 06/07/2022.
//

#include "PenColor.h"

map<string, PenColor> PenColorParseur::dico;

string PenColorParseur::list_names[PENNUMBER] = {
        "blue", "pink", "green", "purple"
};

bool PenColorParseur::init = false;