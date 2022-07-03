/*
 *      Author: Dominique Michel
 */

#ifndef DESSINATEURMONDE_H_
#define DESSINATEURMONDE_H_

#include <string>
#include "Vecteur2D.h"
#include <Couleur.h>
#include "FenetreMonde.h"

using namespace std;



/**
 * fabrique de fenêtre : abstract factory
 *
 * */
class DessinateurMonde
{
public:
/**
 * Ouvre une fenêtre titrée et légendée faisant correspondre le rectangle ( coinBG, coinHD) défini en coordonnées monde au
 * rectangle écran défini par le coin HG (gauche,haut) et de largeur et hauteur indiquées.
 *
 * respecte les proportions et orientations du rectangle monde
 * */
virtual FenetreMonde * ouvreFenetre( const Vecteur2D<double> & coinBG, const Vecteur2D<double> & coinHD,
                                     const int gauche, const int haut, const int largeur, const int hauteur,
                                     const string & titre, const string & legende = "") = 0;

virtual ~DessinateurMonde() = default;
};


#endif /* DESSINATEURMONDE_H_ */
