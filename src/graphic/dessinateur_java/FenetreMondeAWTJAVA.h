/*
 *      Author: Dominique Michel
 */

#ifndef FENETREMONDEAWTJAVA_H_
#define FENETREMONDEAWTJAVA_H_

#include "tcp/ClientTCPString.h"
#include "FenetreMonde.h"
#include "Operateurs.h"

class FenetreMondeAWTJAVA : public FenetreMonde {
    ClientTCPString client;
    FromString<int> parseurint;
public:
    void removeGroupe(string nom) override;

public:
    bool ping() override;

/**
 * Ouvre une fenêtre titrée et légendée faisant correspondre le rectangle ( coinBG, coinHD) défini en coordonnées monde au
 * rectangle écran défini par le coin HG (gauche,haut) et de largeur et hauteur indiquées.
 *
 * respecte les proportions et orientations du rectangle monde
 *
 * la fenêtre est ouverte par un serveur JAVA défini par (adresseServeur, portServeur)
 *
 * */
    FenetreMondeAWTJAVA(const string &adresseServeur, const int portServeur,
                        const Vecteur2D<double> &coinBG, const Vecteur2D<double> &coinHD,
                        const int gauche, const int haut, const int largeur, const int hauteur,
                        const string &titre, const string &legende = "");

    ~FenetreMondeAWTJAVA() override;

/**
 * !!!! ATTENTION !!!!!
 * Dans les méthodes qui suivent, les valeurs double et Vecteur2D<double> sont TOUJOURS données par rapport au repère MONDE
 * et les valeurs entières sont toujours données par rapport au repère écran.
 * Les valeurs entières restent donc constantes lorsque la fenêtre écran subit des modifications
 *
 * Les transformations affines seront donc appliquées côté JAVA
 *
 * */
    void dessineSegment(const Vecteur2D<double> &A1, const Vecteur2D<double> &A2, const Couleur &couleur = (Couleur) "black",
                                const int epaisseurTraitEnPixel = 1) override;

    void dessineMessage(const string &message, const Vecteur2D<double> &A, const Couleur &couleur = (Couleur) "black") override;

    void dessineCercle(const Vecteur2D<double> &centre, const double &rayon, const Couleur &couleur = (Couleur) "black",
                               const int epaisseurTraitEnPixel = 1) override;

    void
    dessineDisque(const Vecteur2D<double> &centre, const double &rayon, const Couleur &couleur = (Couleur) "black") override;

    void
    dessinePoint(const Vecteur2D<double> &centre, const int &rayonEnPixel, const Couleur &couleur = (Couleur) "black") override;

/**
 * TACHE : dessine le polygone plein défini par le contour sommets. couleurInterieur est la couleur de remplissage.
 * DONNEES : {sommets[0],sommets[1], ... , sommets[m]}, couleurInterieur
 * RESULTATS : *this modifié
 *
 * HYPOTHESES : on suppose que "sommets" contient au moins 3 sommets, on a donc 2 <= m
 * On suppose que le polygone à colorier est fermé.
 * Attention : On suppose que sommets[0] != sommets[m]
 * La méthode ferme donc elle-même le contour en considérant le segment [ sommets[m] ---> sommets[0] ]
 * Le contour {sommets[0],sommets[1], ... , sommets[m]} est supposé donné dans le sens trigo croissant
 * Le polygone est quelconque, il n'est donc pas nécessaire qu'il soit convexe
 * Le polygone ne doit pas être dégénéré
 * Le polygone ne doit pas présenter d'auto-intersection
 *
 * */
    void
    dessinePolygonePlein(const Vecteur2D<double> sommets[], const int m, const Couleur &couleurInterieur = (Couleur) "yellow") override;

/**
 * TACHE : efface tous les dessins éventuellement visibles dans la fenêtre
 * */
    void effaceTout() override;

    void ferme() override;

    void setGroupeDessin(string nom) override;

    int creerMenu(int n, string *labels) override;

    void addBouton(int code, string label) override;

    void removeBouton(int code) override;

    bool questionUtilisateurBinaire(string &question) override;

    string questionUtilisateurTexte(string &question) override;

    string listen() override;

protected:
    string questionUtilisateur(string & question, int code);
};


#endif /* FENETREMONDEAWTJAVA_H_ */
