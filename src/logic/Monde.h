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
#include <cassert>

#define NOMBREZONES 13

using namespace std;

class GameScore;

class Monde {

protected:
    vector<Station> liste_stations;
    vector<Connexion> liste_connexions;
    GameInstance * instance;
    int stations_depart[PENCOLORNUMBER];

public:

    Monde();

    virtual ~Monde();

    inline void setInstance(GameInstance *instance) {
        Monde::instance = instance;
    }

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

    /**
     * Calcul tous les coups possibles pour le tour actuel
     * @param state l'état du jeu
     * @param pen la couleur du stylos
     * @param list_moves la liste des coups possibles à remplir
     * @return le  numéro du tour actuel, -1 si plus de tours possibles pour ce stylos
     */
    int calculateAllPossibleMoves(GameState state, PenColor pen, vector<uint16_t> &list_moves) const;

    /**
     * Remplie @param connexion_bit_field avec les connexions de la couleur @param pen.
     * @param state l'état du jeu
     * @param pen la couleur du stylos
     * @param connexion_bit_field le bit_field à remplir
     * @return le nombre de coups joués pour cette couleur
     */
    int calculateAllConnexions(GameState state, PenColor pen, uint64_t * connexion_bit_field) const;

    bool addMoveToBitField(const uint16_t & move, PenColor pen, uint64_t * connexion_bit_field) const;

    void convertListMovesToBitField(const vector<Move> &list_moves, PenColor pen, uint64_t *connexion_bit_field) const;

    template<typename FONCTEUR>
    bool extractConnexionsFromMove(const uint16_t & move, PenColor pen, FONCTEUR f) const;

    GameScore * calculateScore(GameState state) const;

    DECLAREVISITMETHOD(Monde)

};


#endif //HACKNSLPROJECT_MONDE_H
