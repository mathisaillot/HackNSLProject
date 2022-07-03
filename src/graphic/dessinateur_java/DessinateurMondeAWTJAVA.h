/*
 *      Author: Dominique Michel
 */

#ifndef DESSINATEURMONDEAWTJAVA_H_
#define DESSINATEURMONDEAWTJAVA_H_

#include "tcp/ClientTCPString.h"
#include "DessinateurMonde.h"

/**
 * fabrique de fenêtre : abstract factory
 *
 * respecte le contrat défini par la classe DessinateurMonde et fait exécuter ses instructions de dessin
 * par un serveur JAVA défini par (adresseServeur, portServeur)
 * adresseServeur est une adresse TCP au format textuel
 *
 * */
class DessinateurMondeAWTJAVA : public DessinateurMonde
{
string  adresseServeur ;
int portServeur;
public:
DessinateurMondeAWTJAVA(const string & adresseServeur, const int portServeur);

virtual FenetreMonde * ouvreFenetre( const Vecteur2D<double> & coinBG, const Vecteur2D<double> & coinHD,
                                     const int gauche, const int haut, const int largeur, const int hauteur,
                                     const string & titre, const string & legende = "");
virtual ~DessinateurMondeAWTJAVA()=default;

};

#endif /* DESSINATEURMONDEAWTJAVA_H_ */
