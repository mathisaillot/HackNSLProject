//
// Created by Mathis Saillot on 01/07/2022.
//

#ifndef HACKNSLPROJECT_VISITORDESSINATEUR_H
#define HACKNSLPROJECT_VISITORDESSINATEUR_H

#include "visitor/AbstractVisitor.h"
#include "Station.h"
#include "FenetreMonde.h"
#include "Vecteur2D.h"
#include "Monde.h"

class VisitorDessinateurStation : public AbstractVisitor<Station>  {
protected:
    FenetreMonde * fenetre;
    double rayon_outer_circle, scale = 0.13;
    int epaisseur_inner = 3;
    const Couleur & couleur_outer_circle;
    const Couleur & couleur_inner;

    static Vecteur2D<double> pentagone_corners[5];
    static Vecteur2D<double> square_corners[4];
    static Vecteur2D<double> triangle_corners[3];

    static Vecteur2D<double> getCenterPosition(const Station & station);

    void dessineSquare(const Vecteur2D<double> & center) const;
    void dessinePentagone(const Vecteur2D<double> & center) const;
    void dessineCircle(const Vecteur2D<double> & center) const;
    void dessineTriangle(const Vecteur2D<double> & center) const;
    void dessineJoker(const Vecteur2D<double> & center) const;
    void dessinePolygone(const Vecteur2D<double> & center, const Vecteur2D<double> * corners, int size) const;

public:

    explicit VisitorDessinateurStation(FenetreMonde *fenetre, double rayonOuterCircle = 0.2,
                                       const Couleur &couleurOuterCircle = (Couleur) "Black",
                                       const Couleur &couleurInner = (Couleur) "White")
            : fenetre(fenetre), rayon_outer_circle(rayonOuterCircle), couleur_outer_circle(couleurOuterCircle),
              couleur_inner(couleurInner) {}

    void accept(const Station &obj) const override;
};

class  VisitorDessinateurConnexion : public AbstractVisitor<Connexion> {
protected:
    FenetreMonde * fenetre;
    const Couleur & couleur_segment;
public:
    explicit VisitorDessinateurConnexion(FenetreMonde *fenetre, const Couleur &couleurSegment = (Couleur)"Black") : fenetre(fenetre),
                                                                                        couleur_segment(
                                                                                                couleurSegment) {}

    void accept(const Connexion &obj) const override;
};

class VisitorDessinateurMonde : public AbstractVisitor<Monde> {
protected:
    FenetreMonde * fenetre;
    AbstractVisitor<Station> * dessinateurStation;
    AbstractVisitor<Connexion> * dessinateurConnexion;
public:
    VisitorDessinateurMonde(FenetreMonde *fenetre, AbstractVisitor<Station> *dessinateurStation,
                            AbstractVisitor<Connexion> *dessinateurConnexion);

    void accept(const Monde &obj) const override;
};


#endif //HACKNSLPROJECT_VISITORDESSINATEUR_H
