//
// Created by Mathis Saillot on 06/07/2022.
//

#include "GameInstance.h"

GameInstance::GameInstance(const Value &json) {

    for (int i = 0; i < PENNUMBER; ++i) {
        PenColor pen = (PenColor)i;
        auto pen_json = json[PenColorParseur::getNameFromColor(pen)];
        Card::parseDeck(deck[i], pen_json);
    }

}
