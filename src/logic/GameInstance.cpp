//
// Created by Mathis Saillot on 06/07/2022.
//

#include "GameInstance.h"

#define DECKJSON "deck"
#define BONUSJSON "bonus"

GameInstance::GameInstance(const Value &json) {

    for (int i = 0; i < PENCOLORNUMBER; ++i) {
        auto pen = (PenColor)i;
        auto pen_json = json[PenColorParseur::getNameFromType(pen)];
        Card::parseDeck(deck[i], pen_json[DECKJSON]);
        bonus[pen] = BonusTypeParseur::getTypeFromString(pen_json[BONUSJSON].asString());
    }

}
