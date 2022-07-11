//
// Created by Mathis Saillot on 04/07/2022.
//

#include "VisitorDessinateurFactory.h"

VisitorDessinateurStation *VisitorDessinateurFactory::getVisitorStationDefault() {
    return new VisitorDessinateurStation(fenetre,
                                         (Couleur) "Black",
                                         (Couleur) "White",
                                         0.2, 0.3);
}

AbstractVisitor<Station> *VisitorDessinateurFactory::getVisitorStationDepart(const Monde &monde) {

    AbstractVisitor<Station> *visitor = getVisitorStationDefault();
    for (int i = 0; i < PENCOLORNUMBER; ++i) {
        auto pen = (PenColor) i;
        visitor = new VisitorFilter<Station, StationFilter>(
                new VisitorDessinateurStation(fenetre, (Couleur) pen),
                visitor,
                getFilterById(monde.getIdStationDepart(pen))
        );
    }
    return visitor;
}

VisitorDessinateurConnexion *VisitorDessinateurFactory::getVisitorConnexionDefault() {
    return new VisitorDessinateurConnexion(fenetre, (Couleur) "Black", 1);
}

VisitorFilter<Connexion, ConnexionFilter> *VisitorDessinateurFactory::getVisitorConnexionTamise() {
    return new VisitorFilter<Connexion, ConnexionFilter>(
            new VisitorDessinateurConnexion(fenetre, (Couleur) "Cyan", 2),
            getVisitorConnexionDefault(),
            testConnexionTamise);
}

AbstractVisitor<Connexion> *VisitorDessinateurFactory::getVisitorConnexionChemin(const Monde &monde, GameState state) {
    AbstractVisitor<Connexion> *visitor = getVisitorConnexionDefault();
    for (int i = 0; i < PENCOLORNUMBER; ++i) {

        auto pen = (PenColor) i;

        visitor = new ConnexionFilterBitField(fenetre, monde, state, pen, visitor);

    }
    return visitor;
}

AbstractVisitor<Connexion> *
VisitorDessinateurFactory::getVisitorConnexionChoixMoves(const Monde &monde, GameState state,
                                                         const vector<Move> &list_moves, const PenColor &pen) {
    return new ConnexionFilterBitField(fenetre, monde, pen,
                                       (Couleur) "25,25,25",
                                       list_moves,
                                       getVisitorConnexionChemin(monde, state));
}

AbstractVisitor<Connexion> *
VisitorDessinateurFactory::getVisitorConnexionCrossings(const Monde &monde, const int &id_connexion) {
    auto ptx_monde = &monde;
    return new VisitorFilter<Connexion, ConnexionFilter>(
            new VisitorDessinateurConnexion(fenetre, (Couleur) "Red", 5),
            new VisitorFilter<Connexion, ConnexionFilter>(
                    new VisitorDessinateurConnexion(fenetre, (Couleur) "Blue", 5),
                    getVisitorConnexionDefault(),
                    [=](const Connexion &connexion) {
                        //cout << connexion.getId() << " == " << id_connexion << " " << (connexion.getId() == id_connexion) << endl;
                        return connexion.getId() == id_connexion;
                    }
            ),
            [=](const Connexion &connexion) {
                for (auto & cross: ptx_monde->getListeConnexions()[id_connexion].getCrossings()) {
                    if (connexion.getId() == cross) return true;
                }
                return false;
            }
    );
}

bool testConnexionTamise(const Connexion &connexion) {
    return connexion.crossTamise();
}

StationFilter getFilterById(int id) {
    return [=](const Station &a) { return a.getIntId() == id; };
}

/*ConnexionFilter createFilterWithBitField(const uint64_t bitfield[CONNEXIONBITSIZE]) {
    return [=](const Connexion & co) -> bool {
        if (!co.getId()) {
            for (int j = 0; j < CONNEXIONBITSIZE; ++j) {
                cout << bitfield[j] << endl;
            }
        }
        return GETFIELDBIT(bitfield, co.getId());
    };
}*/