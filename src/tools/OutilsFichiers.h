#ifndef OUTILSFICHIERS_H_
#define OUTILSFICHIERS_H_

#include <string>
#include <sstream>
#include <regex>

using namespace std;

/**
 * Système simple de gestion de chemins de fichiers OS indépendant.
 *
 */

#ifndef DATA_ROOT
    #define DATA_ROOT "../data"
#endif

#ifndef FILE_SEP
    #define FILE_SEP "/"
#endif

/**
 * Donne le chemin absolu vers le dossier DATA du projet. OS indépendant.
 * @return le chemin au format string
 */
inline string getCheminDossierData() {return DATA_ROOT;}

/**
 * Retourne le chemin vers un dossier fils depuis un repertoire racine.
 * @param cheminRacine le chemin vers le dossier racine
 * @param nomDossierFils le nom du dossier fils
 * @return le chemin vers le dossier fils
 */
inline string getCheminDossierFils(const string & cheminRacine, const string & nomDossierFils) {
    return cheminRacine + FILE_SEP + nomDossierFils;
}

/**
 * Retourne le chemin vers plusieurs dossier fils depuis un repertoire racine.
 * @param cheminRacine le chemin vers le dossier racine
 * @param nomsFils la liste des noms des dossiers fils
 * @return le chemin vers le dossier fils le plus profond
 */
inline string getCheminDossierFils(const string & cheminRacine, initializer_list<const string> nomsFils) {
    string chemin = cheminRacine;
    for( const auto& fils : nomsFils )
    {
        chemin += FILE_SEP +  fils;
    }
    return chemin;
}

const regex regex_replacement_chemin("(" FILE_SEP "[^" FILE_SEP "]*)$");

inline string getCheminDossierParent(const string & cheminRacine) {
    return regex_replace(cheminRacine, regex_replacement_chemin, "");
}


#endif /* OUTILSFICHIERS_H_ */
