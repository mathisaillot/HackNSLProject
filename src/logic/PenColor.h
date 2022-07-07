//
// Created by Mathis Saillot on 06/07/2022.
//

#ifndef HACKNSLPROJECT_PENCOLOR_H
#define HACKNSLPROJECT_PENCOLOR_H

#include <string>
#include <map>

using namespace std;

enum PenColor {
    BLUE = 0,
    PINK = 1,
    GREEN = 2,
    PURPLE = 3,
    PENNUMBER = 4
};

class PenColorParseur {
protected:
    static map<string, PenColor> dico;
    static string list_names[PENNUMBER];
    static bool init;

    static void initDico()  {
        for (int i = 0; i < PENNUMBER; ++i) {
            dico[list_names[i]] = (PenColor)(i);
        }
        init = true;
    }
public:
    static PenColor getColorFromString(const string & name) {
        if (!init) initDico();
        return dico[name];
    }

    static string getNameFromColor(const PenColor & type) {
        return list_names[type];
    }
};


#endif //HACKNSLPROJECT_PENCOLOR_H
