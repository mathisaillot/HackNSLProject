//
// Created by Mathis Saillot on 01/07/2022.
//

#include "VisitorDessinateur.h"
#include "Connexion.h"
#include <cmath>

Vecteur2D<double> VisitorDessinateurStation::pentagone_corners[5] = {
        Vecteur2D<double>(cos(M_PI/2),sin(M_PI/2)),
        Vecteur2D<double>(cos(9*M_PI/10),sin(9*M_PI/10)),
        Vecteur2D<double>(cos(13*M_PI/10),sin(13*M_PI/10)),
        Vecteur2D<double>(cos(17*M_PI/10),sin(17*M_PI/10)),
        Vecteur2D<double>(cos(21*M_PI/10),sin(21*M_PI/10))
                };

Vecteur2D<double> VisitorDessinateurStation::square_corners[4] = {
        Vecteur2D<double>(cos(M_PI/4),sin(M_PI/4)),
        Vecteur2D<double>(cos(3*M_PI/4),sin(3*M_PI/4)),
        Vecteur2D<double>(cos(5*M_PI/4),sin(5*M_PI/4)),
        Vecteur2D<double>(cos(7*M_PI/4),sin(7*M_PI/4))
};

Vecteur2D<double> VisitorDessinateurStation::triangle_corners[3] = {
        Vecteur2D<double>(cos(M_PI/2),sin(M_PI/2)),
        Vecteur2D<double>(cos(7*M_PI/6),sin(7*M_PI/6)),
        Vecteur2D<double>(cos(11*M_PI/6),sin(11*M_PI/6))
};

void VisitorDessinateurStation::accept(const Station &obj) const {
    auto position = getCenterPosition(obj);
    fenetre->dessineDisque(position,rayon_outer_circle, couleur_outer_circle);

    switch (obj.getType()) {
        case SQUARE:
            dessineSquare(position); break;
        case CIRCLE:
            dessineCircle(position); break;
        case PENTAGONE:
            dessinePentagone(position); break;
        case TRIANGLE:
            dessineTriangle(position); break;
        default:
            dessineJoker(position); break;
    }
}

Vecteur2D<double> VisitorDessinateurStation::getCenterPosition(const Station &station) {
    return {station.getCol(), - station.getRow()};
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

void VisitorDessinateurStation::dessinePolygone(const Vecteur2D<double> &center, const Vecteur2D<double> * corners,
                                                int size) const {
    for (int i = 0; i < size; ++i) {
        fenetre->dessineSegment(center + corners[i] * scale,
                                center + corners[(i+1)%size] * scale, couleur_inner, epaisseur_inner);
    }
}

void VisitorDessinateurConnexion::accept(const Connexion &obj) const {
    Vecteur2D<double> p1(stoi(obj.getConcatId().substr(1,1)),  -stoi(obj.getConcatId().substr(0,1)));
    Vecteur2D<double> p2(stoi(obj.getConcatId().substr(3,1)),  -stoi(obj.getConcatId().substr(2,1)));
    fenetre->dessineSegment(p1,p2, couleur_segment);
}

VisitorDessinateurMonde::VisitorDessinateurMonde(FenetreMonde *fenetre, AbstractVisitor<Station> *dessinateurStation,
                                                 AbstractVisitor<Connexion> *dessinateurConnexion) : fenetre(fenetre),
                                                                                                   dessinateurStation(
                                                                                                           dessinateurStation),
                                                                                                   dessinateurConnexion(
                                                                                                           dessinateurConnexion) {}

void VisitorDessinateurMonde::accept(const Monde &obj) const {
    for (auto & co: obj.getListeConnexions()) {
        co.visit(dessinateurConnexion);
    }
    for (auto & st: obj.getListeStations()) {
        st.visit(dessinateurStation);
    }
}
