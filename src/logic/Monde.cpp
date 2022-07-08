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

Monde::~Monde() = default;
