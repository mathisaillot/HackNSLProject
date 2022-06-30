#pragma once

/*
    cet espace de nom regroupe tout les outils
    pratique sur la manipulation de std::string
*/
#include <iostream>
#include <string>
#include <vector>

#include <ctime>
#include <cmath>

namespace OutStr {
    std::string fileToStringOneLine(const std::string & dest);
    std::vector<std::string> split(const std::string & adresse , char cara);
    std::string & remplace(
        std::string & base, 
        const std::string & oldWord, 
        const std::string & newWord
    );
}
