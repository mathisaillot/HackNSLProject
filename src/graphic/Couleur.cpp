/*
 *      Author: Dominique Michel
 */

#include "Couleur.h"

using namespace std;

//---------------- quelques belles couleurs en composantes RGB -----------------------------

/*static*/ const  string  Couleur::VERT_CLAIR  = "102, 255, 102";
/*static*/ const  string Couleur::BLEU_CLAIR   = "102, 255, 255";
/*static*/ const  string Couleur::MAUVE_CLAIR  = "204, 153, 255";
/*static*/ const  string Couleur::JAUNE_CLAIR  = "255, 255,  51";
/*static*/ const  string Couleur::TURQUOISE    = " 64, 224, 208";

Couleur::Couleur(const string & couleur):couleur(couleur){}

Couleur::operator string() const
{
return couleur;
}

/*static*/ const string Couleur::toString(const Couleur & couleur)
{
return (string)couleur;
}


ostream & operator << (ostream & os, const Couleur & couleur)
{
return os << (string)couleur;
}
