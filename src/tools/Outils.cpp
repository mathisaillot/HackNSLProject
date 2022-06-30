#include "Outils.hpp"

#include <sstream>
#include <fstream>
#include <regex>
// #include <algorithm>

std::string OutStr::fileToStringOneLine(const std::string & dest) {
    std::string mot;
    std::ostringstream oss;
    std::ifstream fichier(dest, std::ios::in);
    if(fichier) {
        while(fichier >> mot) {
            oss << mot << " ";
        }
        fichier.close();
    } else {
        std::cerr << "erreur : fichier " << dest;
    }

    return oss.str();
}
std::vector<std::string> OutStr::split(const std::string & adresse , char cara) {
    std::vector<std::string> resultat;
    std::stringstream ss(adresse);
    std::string mot;
    std::ostringstream oss;
    
    while(std::getline(ss, mot, cara)) {
        resultat.push_back(mot);
    }

    return resultat;
}
std::string & OutStr::remplace(
    std::string & base, 
    const std::string & oldWord, 
    const std::string & newWord
) {
    base = std::regex_replace(base, std::regex(oldWord), newWord);
    return base;
}