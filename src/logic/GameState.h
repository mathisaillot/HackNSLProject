//
// Created by Mathis Saillot on 08/07/2022.
//

#ifndef HACKNSLPROJECT_GAMESTATE_H
#define HACKNSLPROJECT_GAMESTATE_H

#define MAXTURNPERROUND 10
#define MASKBONUS 0b1111111100000000
#define MASKMOVE 0b0000000011111111
#define NBITSFORMOVE 8

#include <PenColor.h>
#include <cstdlib>

typedef uint32_t * GameState;

constexpr int GAMESTATESIZE = MAXTURNPERROUND * PENCOLORNUMBER;

inline void copyGameState(GameState dst, GameState src) {
    memcpy(dst, src, (sizeof(uint32_t) * GAMESTATESIZE));
}

inline GameState newGameState() {
    return (new uint32_t[GAMESTATESIZE]);
}

inline bool checkMove(GameState state, int move_number) {
    return (state[move_number]);
}

inline bool checkBonus(GameState state, int move_number) {
    return (state[move_number] & MASKBONUS);
}

inline uint32_t getIDmove(GameState state, int move_number) {
    return ((~state[move_number]) & MASKMOVE);
}

inline uint32_t getIDbonus(GameState state, int move_number) {
    return ((~state[move_number]) & MASKBONUS) >> NBITSFORMOVE;
}

inline uint32_t getCodeFromID(int id_connexion, int id_bonus = MASKMOVE) {
    return ~(id_connexion | (id_bonus << NBITSFORMOVE));
}



#endif //HACKNSLPROJECT_GAMESTATE_H
