//
// Created by Mathis Saillot on 07/07/2022.
//

#ifndef HACKNSLPROJECT_OUTILSENUM_H
#define HACKNSLPROJECT_OUTILSENUM_H

#include <string>
#include <map>

using namespace std;

#define VIRGULE ,
#define CONCAT(A, B) A ## B

#define ENUMBUILDER(NAME, list, max) enum NAME { list }; \
class CONCAT(NAME, Parseur) {\
protected:\
    static map<string, NAME> dico;\
    static string list_names[max];\
    static bool init;\
    \
    static void initDico()  {\
        for (int i = 0; i < max; ++i) {\
            dico[list_names[i]] = (NAME)(i);\
        }\
        init = true;\
    }\
public:\
    static NAME getTypeFromString(const string & nom) {\
        if (!init) initDico();\
        return dico[nom];\
    }\
    \
    static string getNameFromType(const NAME & type) {\
        return list_names[type];\
    }\
};

#define ENUMBUILDERCPP(NAME, STRINGLIST, NUMBERNUM) \
map<string, NAME> CONCAT(NAME, Parseur)::dico;\
\
string CONCAT(NAME, Parseur)::list_names[NUMBERNUM] = {\
        STRINGLIST\
};\
\
bool CONCAT(NAME, Parseur)::init = false;

#endif //HACKNSLPROJECT_OUTILSENUM_H
