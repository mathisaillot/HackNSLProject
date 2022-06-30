//
// Created by Mathis Saillot on 30/06/2022.
//

#include "Station.h"

const string &Station::getId() const {
    return id_;
}

const string &Station::getConcatId() const {
    return concat_id;
}

int Station::getIntId() const {
    return int_id;
}

int Station::getZone() const {
    return zone_;
}

int Station::getRow() const {
    return row_;
}

int Station::getCol() const {
    return col_;
}

bool Station::isTourist() const {
    return tourist_;
}

StationType Station::getType() const {
    return type_;
}

/**
 * Génère une station à partir de sa représentation Json
 * @param json_input
 */
Station::Station(const Value &json_input) {
    id_ = json_input["id"].asString();
    concat_id = json_input["concat_id"].asString();
    zone_ = json_input["zone"].asInt();
    col_ = json_input["col"].asInt();
    row_ = json_input["row"].asInt();
    tourist_ = json_input["tourist"].asBool();
    type_ = StationTypeParseur::getTypeFromString(json_input["type"].asString());
    int_id = stoi(id_);
}

string Station::toString(const Station &station) {
    ostringstream os;

    os << "Station [" << (station.tourist_ ? "Site Touristique" : "") << " type : " << StationTypeParseur::getNameFromType(station.type_) <<
        ", id : " << station.id_ << ", zone : " << station.zone_ << ", col : "  << station.col_ << ", row : " << station.row_ << "]";

    return os.str();
}

Station::operator string() const {
    return Station::toString(*this);
}

void Station::addConnexion(int connexion_id) {
    liste_connexions.push_back(connexion_id);
}


