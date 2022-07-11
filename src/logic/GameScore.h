//
// Created by Mathis Saillot on 10/07/2022.
//

#ifndef HACKNSLPROJECT_GAMESCORE_H
#define HACKNSLPROJECT_GAMESCORE_H

#include <GameState.h>
#include <GameInstance.h>
#include <Monde.h>

class GameScore {
protected:
    const Monde * monde;
    static const int TOURISTSCORE[30];
    static const int SCORETAMISE;
    static const int SCORECROSSINGS[PENCOLORNUMBER + 1];

public:

    int nombre_zones_visitees[PENCOLORNUMBER] = {};
    int max_visites[PENCOLORNUMBER] = {};
    int nombre_stations_par_zone[PENCOLORNUMBER][NOMBREZONES] = {};
    int nombre_traversees_tamise[PENCOLORNUMBER] = {};
    int nombre_stations_touristiques[PENCOLORNUMBER] = {};
    int points_couleur[PENCOLORNUMBER] = {};
    int score_final = 0;
    int score_tourist = 0;
    int nombre_stations_touristiques_total = 0;
    int nombre_stations_crossed[PENCOLORNUMBER+1] = {};

    uint64_t stations_visitees[PENCOLORNUMBER] = {};


    explicit GameScore(const Monde *monde) : monde(monde) {}

    void addConnexion(const Connexion & connexion, const PenColor & pen);

    void addStation(const Station & station, const PenColor & pen);

    int calculateScoreFinal();

    int calculateScorePen(const PenColor & pen);

    int calculateScoreTourist() const;

    explicit operator string() const;

    friend ostream &operator<<(ostream &os, const GameScore &score) {
        return os << (string) score;
    }



};


#endif //HACKNSLPROJECT_GAMESCORE_H
