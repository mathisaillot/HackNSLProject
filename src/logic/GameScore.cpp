//
// Created by Mathis Saillot on 10/07/2022.
//

#include "GameScore.h"

int const GameScore::TOURISTSCORE[30]  = {0, 1, 2, 4, 6, 8, 11, 14, 17, 21, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25};
const int GameScore::SCORETAMISE = 2;
const int GameScore::SCORECROSSINGS[PENCOLORNUMBER + 1] = {0,0,2,5,9};

void GameScore::addConnexion(const Connexion &connexion, const PenColor &pen) {
    for (int i = 0; i < 2; ++i) {
        auto station = monde->getListeStations()[connexion.getStationsId()[i]];

        if (!GETBIT(stations_visitees[pen], station.getIntId())) {
            addStation(station, pen);
        }
    }

    if (connexion.crossTamise()) {
        nombre_traversees_tamise[pen] ++;
    }
}

void GameScore::addStation(const Station &station, const PenColor &pen) {
    int zone = station.getZone();
    if (!nombre_stations_par_zone[pen][zone]) {
        nombre_zones_visitees[pen] ++;
    }
    nombre_stations_par_zone[pen][zone]++;
    if (station.isTourist()) {
        nombre_stations_touristiques[pen]++;
        nombre_stations_touristiques_total++;
    }
    BITTOONE(stations_visitees[pen], station.getIntId());
}

int GameScore::calculateScoreFinal() {

    score_final = 0;

    for (int i = 0; i < PENCOLORNUMBER; ++i) {
        score_final += (points_couleur[i] = calculateScorePen((PenColor)i));
    }

    score_final += (score_tourist = calculateScoreTourist());

    //todo objectifs

    for (int & i : nombre_stations_crossed) {
        i = 0;
    }

    for (int i = 0; i < monde->getListeStations().size(); ++i) {
        int nombre_stations = 0;
        for (int j = 0; j < PENCOLORNUMBER; ++j) {
            nombre_stations += (GETBIT(stations_visitees[j], i) ? 1 : 0);
        }
        nombre_stations_crossed[nombre_stations] ++;
    }

    for (int i = 0; i < PENCOLORNUMBER + 1; ++i) {
        score_final += nombre_stations_crossed[i] * SCORECROSSINGS[i];
    }

    return score_final;
}

int GameScore::calculateScorePen(const PenColor &pen) {
    max_visites[pen] = 0;
    for (int i = 0; i < NOMBREZONES; ++i) {
        max_visites[pen] = max(max_visites[pen], nombre_stations_par_zone[pen][i]);
    }
    return (nombre_zones_visitees[pen] * max_visites[pen]) + (nombre_traversees_tamise[pen] * SCORETAMISE);
}

int GameScore::calculateScoreTourist() const {
    return TOURISTSCORE[nombre_stations_touristiques_total];
}

GameScore::operator string() const {
    ostringstream oss;
    oss << "Game Score : " << score_final << endl;
    oss << "   score touristes : " << score_tourist << endl;
    for (int i = 0; i < PENCOLORNUMBER; ++i) {
        oss << "     " << PenColorParseur::getNameFromType((PenColor)i) << " : score = " << points_couleur[i];
        oss << " nombre zones " << nombre_zones_visitees[i] << " X max visites " << max_visites[i];
        oss << " + nombre tamises : " << nombre_traversees_tamise[i] << " nombre touristes " << nombre_stations_touristiques[i];
        oss << endl;
    }

    oss << "   Correspondances : ";
    for (int i = 2; i < PENCOLORNUMBER + 1; ++i) {
        oss << " X" << i << " : " << nombre_stations_crossed[i];
    }
    return oss.str();
}

