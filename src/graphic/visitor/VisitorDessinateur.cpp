//
// Created by Mathis Saillot on 01/07/2022.
//

#include "VisitorDessinateur.h"
#include "Connexion.h"
#include <cmath>

void VisitorDessinateurStation::accept(const Station &obj) const {
    auto position = getCenterPosition(obj);
    fenetre->dessineDisque(position, rayon_outer_circle, couleur_outer_circle);

    if (obj.isTourist()) {
        fenetre->dessineCercle(position, rayon_tourist, couleur_outer_circle, 3);
    }

    DessinateurStationType::dessineStationType(fenetre, obj.getType(), position, scale, couleur_inner, epaisseur_inner);
}

Vecteur2D<double> VisitorDessinateurStation::getCenterPosition(const Station &station) {
    return {station.getCol(), -station.getRow()};
}

void VisitorDessinateurConnexion::accept(const Connexion &obj) const {
    Vecteur2D<double> p1(stoi(obj.getConcatId().substr(1, 1)), -stoi(obj.getConcatId().substr(0, 1)));
    Vecteur2D<double> p2(stoi(obj.getConcatId().substr(3, 1)), -stoi(obj.getConcatId().substr(2, 1)));
    fenetre->dessineSegment(p1, p2, couleur_segment, epaisseur_segment);
}

VisitorDessinateurConnexion::VisitorDessinateurConnexion(FenetreMonde *fenetre, const Couleur &couleurSegment,
                                                         int epaisseurSegment) : fenetre(fenetre),
                                                                                 couleur_segment(couleurSegment),
                                                                                 epaisseur_segment(epaisseurSegment) {}

VisitorDessinateurMonde::VisitorDessinateurMonde(FenetreMonde *fenetre, AbstractVisitor<Station> *dessinateurStation,
                                                 AbstractVisitor<Connexion> *dessinateurConnexion) : fenetre(fenetre),
                                                                                                     dessinateurStation(
                                                                                                             dessinateurStation),
                                                                                                     dessinateurConnexion(
                                                                                                             dessinateurConnexion) {}

void VisitorDessinateurMonde::accept(const Monde &obj) const {

    double XMIN = -.5, XMAX = 9.5, YMIN = -9.5, YMAX = .5;

    //Dessine les regions (à la main)
    Vecteur2D<double> P1[] = {Vecteur2D<double>(XMIN, YMIN),// contours
                              Vecteur2D<double>(XMIN, YMIN),
                              Vecteur2D<double>(XMAX, YMAX),
                              Vecteur2D<double>(XMAX, YMAX),

                              Vecteur2D<double>(XMIN + 1, YMIN ), // coin 1
                              Vecteur2D<double>(XMIN, YMIN +1), // coin 1
                              Vecteur2D<double>(XMIN + 1, YMAX ), // coin 2
                              Vecteur2D<double>(XMIN, YMAX -1), // coin 2
                              Vecteur2D<double>(XMAX - 1, YMAX ), // coin 3
                              Vecteur2D<double>(XMAX, YMAX -1), // coin 3
                              Vecteur2D<double>(XMAX - 1, YMIN ), // coin 4
                              Vecteur2D<double>(XMAX, YMIN +1), // coin 4
                              Vecteur2D<double>(XMIN + 3, YMIN), // verticale 1
                              Vecteur2D<double>(XMAX - 3, YMIN), // verticale 2
                              Vecteur2D<double>(XMIN, YMIN + 3), // horizontale 1
                              Vecteur2D<double>(XMIN, YMAX - 3), // horizontale 2
                                      };

    Vecteur2D<double> P2[] = {Vecteur2D<double>(XMAX, YMIN),//contours
                              Vecteur2D<double>(XMIN, YMAX),
                              Vecteur2D<double>(XMAX, YMIN),
                              Vecteur2D<double>(XMIN, YMAX),
                              Vecteur2D<double>(XMIN + 1, YMIN + 1), // coin 1
                              Vecteur2D<double>(XMIN + 1, YMIN + 1), // coin 1
                              Vecteur2D<double>(XMIN + 1, YMAX - 1), // coin 2
                              Vecteur2D<double>(XMIN + 1, YMAX - 1), // coin 2
                              Vecteur2D<double>(XMAX - 1, YMAX - 1), // coin 3
                              Vecteur2D<double>(XMAX - 1, YMAX - 1), // coin 3
                              Vecteur2D<double>(XMAX - 1, YMIN + 1), // coin 4
                              Vecteur2D<double>(XMAX - 1, YMIN + 1), // coin 4
                              Vecteur2D<double>(XMIN + 3, YMAX), // verticale 1
                              Vecteur2D<double>(XMAX - 3, YMAX), // verticale 2
                              Vecteur2D<double>(XMAX, YMIN + 3), // horizontale 1
                              Vecteur2D<double>(XMAX, YMAX - 3), // horizontale 2
            };

    fenetre->setGroupeDessin("zones");

    for (int i = 0; i < 16; ++i) {
        fenetre->dessineSegment(P1[i], P2[i], (Couleur) "Orange", 3);
    }

    fenetre->setGroupeDessin("tamise");

    //Dessine la tamise
    Vecteur2D<double> tamise[] = {
            Vecteur2D<double>(XMIN, YMAX - 4),
            Vecteur2D<double>(XMIN + 2.5, YMAX - 4),
            Vecteur2D<double>(XMIN + 4.5, YMAX - 6),
            Vecteur2D<double>(XMIN + 5.5, YMAX - 6),
            Vecteur2D<double>(XMIN + 6.5, YMAX - 5),
            Vecteur2D<double>(XMAX, YMAX - 5),
    };

    for (int i = 0; i < 5; ++i) {
        fenetre->dessineSegment(tamise[i], tamise[i + 1], (Couleur) "Blue", 10);
    }

    fenetre->setGroupeDessin("connexions");

    //Dessine connexions
    for (auto &co: obj.getListeConnexions()) {
        co.visit(dessinateurConnexion);
    }

    fenetre->setGroupeDessin("stations");

    //Dessine les stations
    for (auto &st: obj.getListeStations()) {
        st.visit(dessinateurStation);
    }
}

VisitorDessinateurMonde::~VisitorDessinateurMonde() {
 delete dessinateurConnexion;
 delete dessinateurStation;
}

void VisitorDessinateurCard::accept(const Card &obj) const {
    DessinateurStationType::dessineStationType(fenetre, obj.getType(), position, rayon, couleur, epaisseur);

    fenetre->dessineSquareSimple(position, rayon * 2, couleur, 1);
    if (obj.isDeviation()) {
        fenetre->dessineMessage("Deviation", position + Vecteur2D<double> (-rayon, rayon * -1.75), couleur);
    }
}
