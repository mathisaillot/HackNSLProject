//
// Created by Mathis Saillot on 30/06/2022.
//

#include "Monde.h"
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
    auto & station_array = obj["stations"];
    ArrayIndex size = station_array.size();

    for (ArrayIndex i = 0; i < size; ++i) {
        liste_stations.emplace_back(station_array[i]);
    }

    auto & json_connexions = obj["connections"];
    size = json_connexions.size();

    for (ArrayIndex i = 0; i < size; ++i) {
        liste_connexions.emplace_back(json_connexions[i], liste_stations);
    }

    auto & json_stations_depart = obj["stations_depart"];
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

    int next_move = MAXTURNPERROUND;
    //On doit trouver la liste des connexions déjà utilisées
    for (int i = 0; i < PENCOLORNUMBER; ++i) {
        int moves = calculateAllConnexions(state, (PenColor)i, connexion_used);

        if (i == (int)pen) {
            next_move = moves;
        }
    }

    //Manche finie
    if (next_move >= instance->getDeck(pen).size()) return -1;

    //Recherche des stations de depart possibles
    uint64_t stations_premiere_visite = 0, station_seconde_visite = 0;
    vector<int> stations_possibles;

    auto carte = instance->getDeck(pen)[next_move];

    if (next_move == 0)  {
        BITTOONE(stations_premiere_visite, stations_depart[pen]);
        stations_possibles.push_back(stations_depart[pen]);
    } else {
        for (int i = 0, move_number = pen * MAXTURNPERROUND; i < next_move; ++i, ++move_number) {
            //todo bonus
            uint16_t id_connexion = getIDmove(state, move_number);
            auto connexion = liste_connexions[id_connexion];
            for (int j = 0; j < 2; ++j) {
                if (GETBIT(stations_premiere_visite, connexion.getStationsId()[j])) {
                    BITTOONE(station_seconde_visite, connexion.getStationsId()[j]);
                } else {
                    BITTOONE(stations_premiere_visite, connexion.getStationsId()[j]);
                    stations_possibles.push_back(connexion.getStationsId()[j]);
                }
            }

        }
    }

    for (int id_station : stations_possibles) {
        //todo bonus
        if (carte.isDeviation() || !GETBIT(station_seconde_visite, id_station)) {
            //départ possible
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
                    opposite_station.getType() != carte.getType()) continue;

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
                list_moves.push_back(getCodeFromID(id_connexion));

            }
        }
    }


    list_moves.push_back(getCodeFromID(IDMOVEPASS));

    return next_move + pen * MAXTURNPERROUND;
}

int Monde::calculateAllConnexions(GameState state, PenColor pen, uint64_t *connexion_bit_field) const {

    for (int j = 0, move_number = pen * MAXTURNPERROUND; j < MAXTURNPERROUND; ++j, ++move_number) {
        if (checkMove(state, move_number)) {
            if (!checkPass(state,move_number)) {
                uint16_t id_connexion = getIDmove(state, move_number);
                //cout << id_connexion << " " << ((id_connexion) >> SHIFTRIGHT) << " " << (1 << ((id_connexion) & MASK64BIT)) << endl;

                FIELDBITTOONE(connexion_bit_field, id_connexion);
                //todo BONUS
            }
        } else {
            return j;
        }
    }
    return MAXTURNPERROUND;
}


Monde::~Monde() = default;
