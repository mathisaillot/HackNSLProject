//
// Created by Mathis Saillot on 06/07/2022.
//

#ifndef HACKNSLPROJECT_GAMEINSTANCE_H
#define HACKNSLPROJECT_GAMEINSTANCE_H

#include <PenColor.h>
#include <Card.h>
#include <BonusType.h>

class GameInstance {

protected:
    vector<Card> deck[PENCOLORNUMBER];
    BonusType bonus[PENCOLORNUMBER];
    //todo bonus et objectifs
public:
    explicit GameInstance(const Value & json);

    inline const vector<Card> & getDeck(const PenColor & pen) const {
        return deck[pen];
    }

    inline const BonusType & getBonus(const PenColor & pen) const {
        return bonus[pen];
    }

    inline explicit operator string() const {
        ostringstream oss;
        oss <<  "GameInstance : [" << endl;
        string tab = "          ";
        for (int i = 0; i < PENCOLORNUMBER; ++i) {
            auto pen = (PenColor)i;
            oss << PenColorParseur::getNameFromType(pen) << " : deck {";
            for (auto & card: deck[pen]) {
                oss << endl << tab << card;
            }
            oss << endl << tab  << "}" << endl
                << tab << "bonus : " << BonusTypeParseur::getNameFromType(bonus[pen]);
            oss << endl;
        }
        oss << "]";
        return oss.str();
    }

    friend ostream &operator<<(ostream &os, const GameInstance &instance) {
        return os << (string) instance;
    }

};


#endif //HACKNSLPROJECT_GAMEINSTANCE_H
