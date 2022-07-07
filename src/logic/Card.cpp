//
// Created by Mathis Saillot on 06/07/2022.
//

#include "Card.h"

const string Card::deviation_name = "deviation";
const string Card::color_name[2] = {"under", "over"};

void Card::parseDeck(vector<Card> &deck, Value &json) {
    auto size = json.size();

    bool deviation = false;
    for (ArrayIndex i = 0; i < size; ++i) {
        string card_name = json[i].asString();
        if (card_name == deviation_name) {
            deviation = true;
        } else {

            int color = card_name.substr(0,color_name[0].size()) != color_name[0];
            StationType type = StationTypeParseur::getTypeFromString(
                    card_name.substr(color_name[color].size() + 1));

            deck.emplace_back(type, deviation, color);

            deviation = false;
        }
    }
}

Card::operator string() const {
    return "Carte " + StationTypeParseur::getNameFromType(type) + " " + (deviation ? deviation_name + " " : "") +
    color_name[color];
}
