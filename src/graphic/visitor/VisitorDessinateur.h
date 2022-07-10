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
#include <DessinateurStationType.h>
#include <Card.h>

class VisitorDessinateurStation : public AbstractVisitor<Station>  {
protected:
    FenetreMonde * fenetre;
    double rayon_outer_circle, scale = 0.13, rayon_tourist;
    int epaisseur_inner = 3;
    const Couleur couleur_outer_circle;
    const Couleur couleur_inner;

    static Vecteur2D<double> getCenterPosition(const Station & station);

public:

    explicit VisitorDessinateurStation(FenetreMonde *fenetre, const Couleur &couleurOuterCircle = (Couleur) "Black",
                                       const Couleur &couleurInner = (Couleur) "White", double rayonOuterCircle = 0.2,
                                       double rayonTourist = 0.3)
            : fenetre(fenetre), rayon_outer_circle(rayonOuterCircle), rayon_tourist(rayonTourist), couleur_outer_circle(couleurOuterCircle),
              couleur_inner(couleurInner) {}

    void accept(const Station &obj) const override;
};

class  VisitorDessinateurConnexion : public AbstractVisitor<Connexion> {
protected:
    FenetreMonde * fenetre;
    const Couleur couleur_segment;
    int epaisseur_segment;
public:
    VisitorDessinateurConnexion(FenetreMonde *fenetre, const Couleur &couleurSegment = (Couleur)"Black", int epaisseurSegment = 1);

    void accept(const Connexion &obj) const override;
};

class VisitorDessinateurMonde : public AbstractVisitor<Monde> {
protected:
    FenetreMonde * fenetre;
    AbstractVisitor<Station> * dessinateurStation;
    AbstractVisitor<Connexion> * dessinateurConnexion;
public:

    ~VisitorDessinateurMonde() override;

    VisitorDessinateurMonde(FenetreMonde *fenetre, AbstractVisitor<Station> *dessinateurStation,
                            AbstractVisitor<Connexion> *dessinateurConnexion);

    void accept(const Monde &obj) const override;
};

class  VisitorDessinateurCard : public AbstractVisitor<Card> {
protected:
    FenetreMonde * fenetre;
    const Couleur couleur;
    int epaisseur;
    Vecteur2D<double> position;
    double rayon;
public:

    ~VisitorDessinateurCard() override = default;

    explicit VisitorDessinateurCard(FenetreMonde *fenetre, const Couleur &couleur = (Couleur)  "Black", int epaisseur = 5,
                           const Vecteur2D<double> &position = Vecteur2D<double>(-2.5,-3), double rayon = 0.5) : fenetre(fenetre), couleur(couleur),
                                                                              epaisseur(epaisseur), position(position),
                                                                              rayon(rayon) {}

    void accept(const Card &obj) const override;
};


#endif //HACKNSLPROJECT_VISITORDESSINATEUR_H
