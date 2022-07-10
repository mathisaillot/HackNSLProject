//
// Created by Mathis Saillot on 06/07/2022.
//

#ifndef HACKNSLPROJECT_CARD_H
#define HACKNSLPROJECT_CARD_H

#include <StationType.h>
#include <JsonLoader.hpp>
#include <AbstractVisitor.h>

using namespace Json;

class Card {

protected:
    StationType type;
    bool deviation;
    int color;
    static const string deviation_name, color_name[2];
public:

    virtual ~Card();

    Card(StationType type, bool deviation, int color) : type(type), deviation(deviation), color(color) {}

    inline StationType getType() const {
        return type;
    }

    inline bool isDeviation() const {
        return deviation;
    }

    inline bool isRed() const {
        return color;
    }

    explicit operator string() const;

    friend ostream &operator<<(ostream &os, const Card &card) {
        return os << (string) card;
    }

    static void parseDeck(vector<Card> & deck, Value & json);

    DECLAREVISITMETHOD(Card)

};


#endif //HACKNSLPROJECT_CARD_H
