//
// Created by Mathis Saillot on 06/07/2022.
//

#ifndef HACKNSLPROJECT_GAMEINSTANCE_H
#define HACKNSLPROJECT_GAMEINSTANCE_H

#include <PenColor.h>
#include <Card.h>

class GameInstance {

protected:
    vector<Card> deck[PENNUMBER];
    //todo bonus et objectifs
public:
    GameInstance(const Value & json);

    inline const vector<Card> & getDeck(const PenColor & pen) const {
        return deck[pen];
    }

};


#endif //HACKNSLPROJECT_GAMEINSTANCE_H
