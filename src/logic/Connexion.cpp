//
// Created by Mathis Saillot on 30/06/2022.
//

#include "Connexion.h"

Connexion::Connexion(const Value &json_data, vector<Station> &stations) {
    id_ = json_data["id"].asInt();
    concat_id_ = json_data["concat_id"].asString();
    tamise_ = json_data["tamise"].asBool();
    auto & json_stations_ids = json_data["stations_id"];

    for (int i = 0; i < 2; ++i) {
        stations_id[i] = json_stations_ids[i].asInt();
        stations.at(stations_id[i]).addConnexion(id_);
    }

    auto & json_crossings = json_data["crossing"];
    ArrayIndex size = json_crossings.size();

    for (ArrayIndex i = 0; i < size; ++i) {
        crossings.push_back(json_crossings[i].asInt());
    }

}
