//
// Created by Mathis Saillot on 01/07/2022.
//

#include "VisitorDessinateur.h"
#include "Connexion.h"
#include <cmath>

Vecteur2D<double> VisitorDessinateurStation::pentagone_corners[5] = {
        Vecteur2D<double>(cos(M_PI / 2), sin(M_PI / 2)),
        Vecteur2D<double>(cos(9 * M_PI / 10), sin(9 * M_PI / 10)),
        Vecteur2D<double>(cos(13 * M_PI / 10), sin(13 * M_PI / 10)),
        Vecteur2D<double>(cos(17 * M_PI / 10), sin(17 * M_PI / 10)),
        Vecteur2D<double>(cos(21 * M_PI / 10), sin(21 * M_PI / 10))
};

Vecteur2D<double> VisitorDessinateurStation::square_corners[4] = {
        Vecteur2D<double>(cos(M_PI / 4), sin(M_PI / 4)),
        Vecteur2D<double>(cos(3 * M_PI / 4), sin(3 * M_PI / 4)),
        Vecteur2D<double>(cos(5 * M_PI / 4), sin(5 * M_PI / 4)),
        Vecteur2D<double>(cos(7 * M_PI / 4), sin(7 * M_PI / 4))
};

Vecteur2D<double> VisitorDessinateurStation::triangle_corners[3] = {
        Vecteur2D<double>(cos(M_PI / 2), sin(M_PI / 2)),
        Vecteur2D<double>(cos(7 * M_PI / 6), sin(7 * M_PI / 6)),
        Vecteur2D<double>(cos(11 * M_PI / 6), sin(11 * M_PI / 6))
};

void VisitorDessinateurStation::accept(const Station &obj) const {
    auto position = getCenterPosition(obj);
    fenetre->dessineDisque(position, rayon_outer_circle, couleur_outer_circle);

    if (obj.isTourist()) {
        fenetre->dessineCercle(position, rayon_tourist, couleur_outer_circle, 3);
    }

    switch (obj.getType()) {
        case SQUARE:
            dessineSquare(position);
            break;
        case CIRCLE:
            dessineCircle(position);
            break;
        case PENTAGONE:
            dessinePentagone(position);
            break;
        case TRIANGLE:
            dessineTriangle(position);
            break;
        default:
            dessineJoker(position);
            break;
    }
}

Vecteur2D<double> VisitorDessinateurStation::getCenterPosition(const Station &station) {
    return {station.getCol(), -station.getRow()};
}

void VisitorDessinateurStation::dessineSquare(const Vecteur2D<double> &center) const {
    dessinePolygone(center, square_corners, 4);
}

void VisitorDessinateurStation::dessinePentagone(const Vecteur2D<double> &center) const {
    dessinePolygone(center, pentagone_corners, 5);
}

void VisitorDessinateurStation::dessineCircle(const Vecteur2D<double> &center) const {
    fenetre->dessineCercle(center, scale, couleur_inner, epaisseur_inner);
}

void VisitorDessinateurStation::dessineTriangle(const Vecteur2D<double> &center) const {
    dessinePolygone(center, triangle_corners, 3);
}

void VisitorDessinateurStation::dessineJoker(const Vecteur2D<double> &center) const {

}

void VisitorDessinateurStation::dessinePolygone(const Vecteur2D<double> &center, const Vecteur2D<double> *corners,
                                                int size) const {
    for (int i = 0; i < size; ++i) {
        fenetre->dessineSegment(center + corners[i] * scale,
                                center + corners[(i + 1) % size] * scale, couleur_inner, epaisseur_inner);
    }
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
