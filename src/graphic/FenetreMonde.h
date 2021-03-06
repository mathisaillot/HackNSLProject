/*
 *      Author: Dominique Michel
 */

#ifndef FENETREMONDE_H_
#define FENETREMONDE_H_

#include <string>
#include <Vecteur2D.h>
#include <Couleur.h>

using namespace std;

class FenetreMonde {
protected:
    static Vecteur2D<double> pentagone_corners[5];
    static Vecteur2D<double> square_corners[4];
    static Vecteur2D<double> triangle_corners[3];

public:

    virtual ~FenetreMonde() = default;

    void
    dessineTriangleSimple(const Vecteur2D<double> &centre, double rayon, const Couleur &couleur = (Couleur) "black",
                          int epaisseurTraitEnPixel = 1);

    void dessineSquareSimple(const Vecteur2D<double> &centre, double rayon, const Couleur &couleur = (Couleur) "black",
                             int epaisseurTraitEnPixel = 1);

    void dessineCrossSimple(const Vecteur2D<double> &centre, double rayon, const Couleur &couleur = (Couleur) "black",
                            int epaisseurTraitEnPixel = 1);

    void
    dessinePentagoneSimple(const Vecteur2D<double> &centre, double rayon, const Couleur &couleur = (Couleur) "black",
                           int epaisseurTraitEnPixel = 1);

    void
    dessinePolygoneSimple(const Vecteur2D<double> &centre, const Vecteur2D<double> *corners, int size,
                          double rayon, const Couleur &couleur, int epaisseurTraitEnPixel);


    virtual void
    dessineSegment(const Vecteur2D<double> &A1, const Vecteur2D<double> &A2, const Couleur &couleur = (Couleur) "black",
                   int epaisseurTraitEnPixel = 1) = 0;

    virtual void
    dessineMessage(const string &message, const Vecteur2D<double> &A, const Couleur &couleur = (Couleur) "black") = 0;

    virtual void
    dessineMessage(const char *message, const Vecteur2D<double> &A, const Couleur &couleur = (Couleur) "black") {
        dessineMessage(string(message), A, couleur);
    }

    virtual void
    dessineCercle(const Vecteur2D<double> &centre, const double &rayon, const Couleur &couleur = (Couleur) "black",
                  const int epaisseurTraitEnPixel = 1) = 0;

    virtual void
    dessineDisque(const Vecteur2D<double> &centre, const double &rayon, const Couleur &couleur = (Couleur) "black") = 0;

    virtual void
    dessinePoint(const Vecteur2D<double> &centre, const int &rayonEnPixel,
                 const Couleur &couleur = (Couleur) "black") = 0;

/**
 * TACHE : dessine le polygone plein d??fini par le contour sommets. couleurInterieur est la couleur de remplissage.
 * DONNEES : {sommets[0],sommets[1], ... , sommets[m]}, couleurInterieur
 * RESULTATS : *this modifi??
 *
 * HYPOTHESES : on suppose que "sommets" contient au moins 3 sommets, on a donc 2 <= m
 * On suppose que le polygone ?? colorier est ferm??.
 * Attention : On suppose que sommets[0] != sommets[m]
 * La m??thode ferme donc elle-m??me le contour en consid??rant le segment [ sommets[m] ---> sommets[0] ]
 * Le contour {sommets[0],sommets[1], ... , sommets[m]} est suppos?? donn?? dans le sens trigo croissant
 * Le polygone est quelconque, il n'est donc pas n??cessaire qu'il soit convexe
 * Le polygone ne doit pas ??tre d??g??n??r??
 * Le polygone ne doit pas pr??senter d'auto-intersection
 *
 * */
    virtual void dessinePolygonePlein(const Vecteur2D<double> sommets[], const int m,
                                      const Couleur &couleurInterieur = (Couleur) "yellow") = 0;

/**
 * TACHE : efface tous les dessins ??ventuellement visibles dans la fen??tre
 * */
    virtual void effaceTout() = 0;

    /**
     * Supprime un groupe de dessin l'effa??ant de la fen??tre
     */
    virtual void removeGroupe(string nom) = 0;

    virtual void ferme() = 0;

    /**
     * Les prochaines instructions de dessin se trouveront dans un nouveau groupe.
     */
    virtual void setGroupeDessin(string nom) = 0;

    /**
     * Permet de cr??er un menu avec une liste de label de boutons
     * @param n nombre de boutons
     * @param labels liste des label des boutons
     * @return l'indice du bouton choisi
     */
    virtual int creerMenu(int n, string *labels) = 0;

    /**
     * Permet de poser une question avec une r??ponse oui ou non.
     * @param question la question ?? poser
     * @return la r??ponse en bool??en
     */
    virtual bool questionUtilisateurBinaire(string &question) = 0;

    /**
     * Permet de poser une question avec une textuelle de l'utilisateur
     * @param question la question ?? poser
     * @return la r??ponse en string
     */
    virtual string questionUtilisateurTexte(string &question) = 0;

    /**
     * Se synchronise avec la fen??tre
     * @return true si la fen??tre r??pond
     */
    virtual bool ping() = 0;

    /**
     * Ajoute un bouton
     * @param code l'identifiant du bouton
     * @param label le label du bouton
     */
    virtual void addBouton(int code, string label) = 0;

    /**
     * Retire le bouton avec l'identifiant code
     * @param code l'identifiant du bouton
     */
    virtual void removeBouton(int code) = 0;

    /**
     * Attend un retour utilisateur
     * @return l'input re??u en string
     */
    virtual string listen() = 0;
};


#endif /* FENETREMONDE_H_ */
