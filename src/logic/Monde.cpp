//
// Created by Mathis Saillot on 30/06/2022.
//

#include "Monde.h"
#include "GameScore.h"
#include <OutilsFichiers.h>
#include <JsonLoader.hpp>
#include <fstream>

#define JSONDATABASE "NSLdata.json"

using namespace Json;

Monde::Monde() {

    /// Chargement fichier Json
    ifstream ifs;
    ifs.open(getCheminDossierFils(getCheminDossierData(), JSONDATABASE));
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj);

    /// Parcours JSON
    auto &station_array = obj["stations"];
    ArrayIndex size = station_array.size();

    for (ArrayIndex i = 0; i < size; ++i) {
        liste_stations.emplace_back(station_array[i]);
    }

    auto &json_connexions = obj["connections"];
    size = json_connexions.size();

    for (ArrayIndex i = 0; i < size; ++i) {
        liste_connexions.emplace_back(json_connexions[i], liste_stations);
    }

    auto &json_stations_depart = obj["stations_depart"];
    size = json_stations_depart.size();

    for (ArrayIndex i = 0; i < size; ++i) {
        stations_depart[PenColorParseur::getTypeFromString(json_stations_depart[i]["color"].asString())] =
                json_stations_depart[i]["id"].asInt();
    }

}

int Monde::calculateAllPossibleMoves(GameState state, PenColor pen, vector<uint16_t> &list_moves) const {
    assert(instance != nullptr);
    auto station_number = liste_stations.size();
    assert(station_number < 64);
    auto connexion_number = liste_connexions.size();

    assert(connexion_number < 64 * (CONNEXIONBITSIZE));

    uint64_t connexion_used[CONNEXIONBITSIZE] = {};

    //cout << "calculateMoves" << endl;

    int next_move = MAXTURNPERROUND;
    //On doit trouver la liste des connexions déjà utilisées
    for (int i = 0; i < PENCOLORNUMBER; ++i) {

        int moves = calculateAllConnexions(state, (PenColor) i, connexion_used);
        //cout << "connexions " << i << endl;

        if (i == (int) pen) {
            next_move = moves;
        }
    }

    //cout << "next " << next_move << endl;

    //Manche finie
    if (next_move >= instance->getDeck(pen).size()) return -1;

    //Recherche des stations de depart possibles
    uint64_t stations_premiere_visite = 0, station_seconde_visite = 0;
    vector<int> stations_possibles;

    auto carte = instance->getDeck(pen)[next_move];

    //cout << "getCarte" << endl;

    bool bonus_used = false;
    auto & bonus = instance->getBonus(pen);

    auto F = [&](Move id_connexion) {
        auto connexion = liste_connexions[id_connexion];
        for (int j = 0; j < 2; ++j) {
            if (GETBIT(stations_premiere_visite, connexion.getStationsId()[j])) {
                //cout << "seconde visite " << connexion.getStationsId()[j] << endl;
                BITTOONE(station_seconde_visite, connexion.getStationsId()[j]);
            } else {
                //cout << "premiere visite " << connexion.getStationsId()[j] << endl;
                BITTOONE(stations_premiere_visite, connexion.getStationsId()[j]);
                stations_possibles.push_back(connexion.getStationsId()[j]);
            }
        }
    };

    for (int i = 0, move_number = pen * MAXTURNPERROUND; i < next_move; ++i, ++move_number) {

        extractConnexionsFromMove(state[move_number], pen, F);

        if (checkBonus(state, move_number)) {
            bonus_used = true;
        }


    }

    if (stations_possibles.empty()) {
        BITTOONE(stations_premiere_visite, stations_depart[pen]);
        stations_possibles.push_back(stations_depart[pen]);
        //cout << "station depart empty" << endl;
    }

    //cout << "stations possibles" << endl;

    bool bonus_deviation = (bonus == BONUS_DERIVATION) && !bonus_used;
    bool bonus_joker = (bonus == BONUS_JOKER) && !bonus_used;
    bool bonus_double = (bonus == BONUS_DOUBLE) && !bonus_used;
    bool bonus_replay = (bonus == BONUS_REPLAY) && !bonus_used;


    for (int id_station: stations_possibles) {
        if (carte.isDeviation() || !GETBIT(station_seconde_visite, id_station) || bonus_deviation) {
            //départ possible
            bool using_bonus = !(carte.isDeviation() || !GETBIT(station_seconde_visite, id_station));
            int id_bonus = 0;
            for (int id_connexion: liste_stations[id_station].getListeConnexions()) {
                auto connexion = liste_connexions[id_connexion];
                int opposite_id = (connexion.getStationsId()[0] == id_station ?
                                   connexion.getStationsId()[1] : connexion.getStationsId()[0]
                );
                auto opposite_station = liste_stations[opposite_id];

                //check station is free
                if (GETBIT(stations_premiere_visite, opposite_id)) continue;

                //check station is compatible with card
                if (opposite_station.getType() != JOKER && carte.getType() != JOKER &&
                    opposite_station.getType() != carte.getType()) {
                    if (bonus_joker) {
                        using_bonus = true;
                    } else
                        continue;
                }

                //check connexion is free
                if (GETFIELDBIT(connexion_used, id_connexion)) continue;

                //check crossings
                bool flag = false;
                for (int id_crossings: connexion.getCrossings()) {
                    if (GETFIELDBIT(connexion_used, id_crossings)) {
                        flag = true;
                        break;
                    }
                }
                if (flag) continue;

                //C'est tout bon on peut générer un move
                if (using_bonus) {
                    list_moves.push_back(getCodeFromID(id_connexion, id_bonus));

                } else {
                    list_moves.push_back(getCodeFromID(id_connexion));

                }

                //todo bonus replay

                if (bonus_double) {
                    list_moves.push_back(getCodeFromID(id_connexion, opposite_id));

                    if (stations_possibles.size() == 1) {
                        list_moves.push_back(getCodeFromID(id_connexion, id_station));
                    }
                }

            }
        }
    }


    //cout << "move pass" << endl;

    list_moves.push_back(getCodeFromID(IDMOVEPASS));

    return next_move + pen * MAXTURNPERROUND;
}

int Monde::calculateAllConnexions(GameState state, PenColor pen, uint64_t *connexion_bit_field) const {

    for (int j = 0, move_number = pen * MAXTURNPERROUND; j < MAXTURNPERROUND; ++j, ++move_number) {
        if (!addMoveToBitField(state[move_number], pen, connexion_bit_field)) {
            return j;
        }
    }
    return MAXTURNPERROUND;
}

void
Monde::convertListMovesToBitField(const vector<Move> &list_moves, PenColor pen, uint64_t *connexion_bit_field) const {
    for (const Move &move: list_moves) {
        addMoveToBitField(move, pen, connexion_bit_field);
    }
}

bool Monde::addMoveToBitField(const uint16_t &move, PenColor pen, uint64_t *connexion_bit_field) const {
    auto F = [&](int connexion_id) -> void { FIELDBITTOONE(connexion_bit_field, connexion_id); };
    return extractConnexionsFromMove(move, pen, F);
}

GameScore *Monde::calculateScore(GameState state) const {
    auto score = new GameScore(this);

    for (int i = 0; i < PENCOLORNUMBER; ++i) {
        auto pen = (PenColor) i;
        auto &bonus = instance->getBonus(pen);
        auto F = [&](int connexion_id) {
            score->addConnexion(liste_connexions[connexion_id], pen);
        };
        for (int j = 0, move_number = pen * MAXTURNPERROUND; j < MAXTURNPERROUND; ++j, ++move_number) {

            extractConnexionsFromMove(state[move_number], pen, F);

            if (bonus == BONUS_DOUBLE && checkBonus(state, move_number)) {

                uint16_t id_station_bonus = getIDbonus(state, move_number);
                score->addStation(liste_stations[id_station_bonus], pen);

            }
        }
    }
    score->calculateScoreFinal();
    return score;
}

template<typename FONCTEUR>
bool Monde::extractConnexionsFromMove(const uint16_t &move, PenColor pen, FONCTEUR f) const {
    if (checkMove(move)) {
        if (!checkPass(move)) {
            uint16_t id_connexion = getIDmove(move);
            ////cout << id_connexion << " " << ((id_connexion) >> SHIFTRIGHT) << " " << (1 << ((id_connexion) & MASK64BIT)) << endl;

            f(id_connexion);

            if (checkBonus(move)) {
                auto &bonus = instance->getBonus(pen);

                if (bonus == BONUS_REPLAY) {
                    uint16_t id_connexion_bonus = getIDbonus(move);
                    f(id_connexion_bonus);
                }

            }
        }
        return true;
    }
    return false;
}


Monde::~Monde() = default;
