//
// Created by Mathis Saillot on 04/07/2022.
//

#ifndef HACKNSLPROJECT_VISITORDESSINATEURFACTORY_H
#define HACKNSLPROJECT_VISITORDESSINATEURFACTORY_H

#include <VisitorFilter.h>
#include <VisitorDessinateur.h>
#include <Station.h>
#include <Connexion.h>
#include <GameState.h>

//typedef bool (&ConnexionFilter)(const Connexion &);
typedef function<bool(const Station &)> StationFilter;
typedef function<bool(const Connexion &)> ConnexionFilter;

bool testConnexionTamise(const Connexion & connexion);

StationFilter getFilterById(int id);

//ConnexionFilter createFilterWithBitField(const uint64_t bitfield[CONNEXIONBITSIZE]);

class VisitorDessinateurFactory {
protected:
    FenetreMonde * fenetre;
public:
    explicit VisitorDessinateurFactory(FenetreMonde *fenetre) : fenetre(fenetre) {}

    VisitorDessinateurStation * getVisitorStationDefault();

    AbstractVisitor<Station> * getVisitorStationDepart(const Monde &monde);

    VisitorDessinateurConnexion * getVisitorConnexionDefault();

    VisitorFilter<Connexion, ConnexionFilter> * getVisitorConnexionTamise();

    AbstractVisitor<Connexion> * getVisitorConnexionChemin(const Monde & monde, GameState state);
};

class ConnexionFilterBitField : public AbstractVisitor<Connexion> {
protected:
    uint64_t bitfield[CONNEXIONBITSIZE] = {};
    VisitorFilter<Connexion, ConnexionFilterBitField&> * filter;
public:
    ConnexionFilterBitField(FenetreMonde * fenetre, const Monde & monde, GameState state, const PenColor &pen,
                            AbstractVisitor<Connexion> * visitor_default) {
        monde.calculateAllConnexions(state, pen, bitfield);
        filter = new VisitorFilter<Connexion, ConnexionFilterBitField&>(new VisitorDessinateurConnexion(fenetre, (Couleur) pen, 4),
                                                               visitor_default, (*this));
    }

    bool operator()(const Connexion & connexion) {
        return GETFIELDBIT(bitfield, connexion.getId());
    }

    ~ConnexionFilterBitField() override {
        delete filter;
    }

    void accept(const Connexion &obj) const override {
        obj.visit(filter);
    }

};

#endif //HACKNSLPROJECT_VISITORDESSINATEURFACTORY_H
