//
// Created by Mathis Saillot on 08/07/2022.
//

#ifndef HACKNSLPROJECT_GAMESTATE_H
#define HACKNSLPROJECT_GAMESTATE_H

#define MAXTURNPERROUND 10
#define MASKBONUS 0b1111111100000000
#define MASKMOVE 0b0000000011111111
#define IDMOVEPASS 0b0000000011111110
#define NBITSFORMOVE 8

#include <PenColor.h>
#include <cstdlib>

typedef uint16_t * GameState;

constexpr int GAMESTATESIZE = MAXTURNPERROUND * PENCOLORNUMBER;

inline void copyGameState(GameState dst, GameState src) {
    memcpy(dst, src, (sizeof(uint16_t) * GAMESTATESIZE));
}

inline GameState newGameState() {
    return (new uint16_t[GAMESTATESIZE]);
}

inline bool checkMove(GameState state, int move_number) {
    return (state[move_number]);
}

inline bool checkBonus(GameState state, int move_number) {
    return (state[move_number] & MASKBONUS);
}

inline bool checkPass(GameState state, int move_number) {
    return (state[move_number] == 1);
}

inline uint16_t getIDmove(GameState state, int move_number) {
    return ((~state[move_number]) & MASKMOVE);
}

inline uint16_t getIDbonus(GameState state, int move_number) {
    return ((~state[move_number]) & MASKBONUS) >> NBITSFORMOVE;
}

inline uint16_t getCodeFromID(int id_connexion, int id_bonus = MASKMOVE) {
    return ~(id_connexion | (id_bonus << NBITSFORMOVE));
}



#endif //HACKNSLPROJECT_GAMESTATE_H
