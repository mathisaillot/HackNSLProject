/*
 *      Author: Dominique Michel
 */

#ifndef COULEUR_H_
#define COULEUR_H_


#include <string>
#include <iostream>

using namespace std;

class Couleur {
    string couleur;
public:

//---------------- quelques belles couleurs en composantes RGB -----------------------------

    static const string VERT_CLAIR;
    static const string BLEU_CLAIR;
    static const string MAUVE_CLAIR;
    static const string JAUNE_CLAIR;
    static const string TURQUOISE;
    static const string ROSE;
    static const string VERT;
    static const string BLEU;
    static const string VIOLET;


    explicit Couleur(string couleur);

    explicit operator string() const;

    static const string toString(const Couleur &couleur);
};

ostream &operator<<(ostream &os, const Couleur &couleur);

#endif /* COULEUR_H_ */
