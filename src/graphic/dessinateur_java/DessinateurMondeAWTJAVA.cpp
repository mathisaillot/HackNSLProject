/*
 *      Author: Dominique Michel
 */

#include <sstream>

#include "FenetreMondeAWTJAVA.h"
#include "DessinateurMondeAWTJAVA.h"

using namespace std;


DessinateurMondeAWTJAVA::DessinateurMondeAWTJAVA(const string &adresseServeur, const int portServeur) : adresseServeur(
        adresseServeur), portServeur(portServeur) {}

/**
 * fabrique de fenêtre : abstract factory
 *
 * */

/*virtual*/ FenetreMonde *DessinateurMondeAWTJAVA::
ouvreFenetre(const Vecteur2D<double> &coinBG, const Vecteur2D<double> &coinHD,
             const int gauche, const int haut, const int largeur, const int hauteur,
             const string &titre, const string &legende) {
    return new FenetreMondeAWTJAVA(adresseServeur, portServeur,
                                   coinBG, coinHD,
                                   gauche, haut, largeur, hauteur,
                                   titre, legende);

}
