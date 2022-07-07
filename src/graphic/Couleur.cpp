/*
 *      Author: Dominique Michel
 */

#include "Couleur.h"

#include <utility>

using namespace std;

//---------------- quelques belles couleurs en composantes RGB -----------------------------

/*static*/ const string  Couleur::VERT_CLAIR = "102, 255, 102";
/*static*/ const string Couleur::BLEU_CLAIR = "102, 255, 255";
/*static*/ const string Couleur::MAUVE_CLAIR = "204, 153, 255";
/*static*/ const string Couleur::JAUNE_CLAIR = "255, 255,  51";
/*static*/ const string Couleur::TURQUOISE = " 64, 224, 208";
/*static*/ const string Couleur::ROSE = " 222, 16, 100";
/*static*/ const string Couleur::VERT = " 64, 157, 47";
/*static*/ const string Couleur::BLEU = " 66, 142, 224";
/*static*/ const string Couleur::VIOLET = " 90, 37, 120";

Couleur::Couleur(string couleur) : couleur(std::move(couleur)) {}

Couleur::operator string() const {
    return couleur;
}

/*static*/ const string Couleur::toString(const Couleur &couleur) {
    return (string) couleur;
}


ostream &operator<<(ostream &os, const Couleur &couleur) {
    return os << (string) couleur;
}
