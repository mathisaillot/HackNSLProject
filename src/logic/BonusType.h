//
// Created by Mathis Saillot on 07/07/2022.
//

#ifndef HACKNSLPROJECT_BONUSTYPE_H
#define HACKNSLPROJECT_BONUSTYPE_H

#include <OutilsEnum.h>

ENUMBUILDER(BonusType,
            BONUS_JOKER = 0 VIRGULE \
            BONUS_DERIVATION = 1  VIRGULE \
            BONUS_DOUBLE = 2 VIRGULE \
            BONUS_REPLAY = 3 VIRGULE \
            NOBONUS = 4 VIRGULE \
            BONUSTYPENUMBER = 5,
            BONUSTYPENUMBER
            )


#endif //HACKNSLPROJECT_BONUSTYPE_H
