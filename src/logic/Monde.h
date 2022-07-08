//
// Created by Mathis Saillot on 30/06/2022.
//

#ifndef HACKNSLPROJECT_MONDE_H
#define HACKNSLPROJECT_MONDE_H

#include <vector>
#include <string>
#include <Station.h>
#include <Connexion.h>
#include <FenetreMonde.h>
#include <AbstractVisitor.h>
#include <GameInstance.h>
#include <GameState.h>

using namespace std;

class Monde {

protected:
    vector<Station> liste_stations;
    vector<Connexion> liste_connexions;
    GameInstance * instance;
    int stations_depart[PENCOLORNUMBER];

public:

    Monde();

    virtual ~Monde();

    inline int getIdStationDepart(const PenColor & color) const {
        return stations_depart[color];
    }

    inline const GameInstance * getGameInstance() const{
        return instance;
    }

    inline const vector<Station> & getListeStations() const {
        return liste_stations;
    }

    inline const vector<Connexion> & getListeConnexions() const {
        return liste_connexions;
    }

    inline unsigned long getNumberStation() const { return liste_stations.size(); }

    inline unsigned long getNumberConnexion() const { return liste_connexions.size(); }

    int calculateAllPossibleMoves(GameState state, PenColor pen, vector<int> & list_moves);

    DECLAREVISITMETHOD(Monde)

};


#endif //HACKNSLPROJECT_MONDE_H
