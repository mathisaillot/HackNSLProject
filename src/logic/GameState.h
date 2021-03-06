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

#define CONNEXIONBITSIZE 3
#define MASK64BIT 0b111111
#define SHIFTRIGHT 6
#define BITTOONE(bits, n) bits |= (uint64_t (1) << (n))
#define FIELDBITTOONE(field, n) field[((n) >> SHIFTRIGHT)] |= (uint64_t (1) << ((n) & MASK64BIT))
#define GETBIT(bits, n) ((bits) & (uint64_t (1) << (n)))
#define GETFIELDBIT(field, n) ((field[((n) >> SHIFTRIGHT)]) & (uint64_t(1) << ((n) & MASK64BIT)))

#include <PenColor.h>
#include <cstdlib>
#include <cstring>

typedef uint16_t Move;
typedef Move * GameState;

constexpr int GAMESTATESIZE = MAXTURNPERROUND * PENCOLORNUMBER;

inline void copyGameState(GameState dst, GameState src) {
    memcpy(dst, src, (sizeof(Move) * GAMESTATESIZE));
}

inline GameState newGameState() {
    auto state = (new Move[GAMESTATESIZE]);
    memset(state, 0, (sizeof(Move) * GAMESTATESIZE));
    return state;
}


inline bool checkMove(const Move & move) {
    return (move);
}

inline bool checkMove(GameState state, int move_number) {
    return checkMove(state[move_number]);
}

inline bool checkBonus(const Move & move) {
    return (move & MASKBONUS);
}

inline bool checkBonus(GameState state, int move_number) {
    return checkBonus(state[move_number]);
}

inline bool checkPass(const Move & move) {
    return (move == 1);
}

inline bool checkPass(GameState state, int move_number) {
    return checkPass(state[move_number]);
}

inline uint16_t getIDmove(const Move & move) {
    return ((~(move)) & MASKMOVE);
}

inline uint16_t getIDmove(GameState state, int move_number) {
    return getIDmove(state[move_number]);
}

inline uint16_t getIDbonus(const Move & move) {
    return (((~(move)) & MASKBONUS) >> NBITSFORMOVE);
}

inline uint16_t getIDbonus(GameState state, int move_number) {
    return getIDbonus(state[move_number]);
}

inline uint16_t getCodeFromID(int id_connexion, int id_bonus = MASKMOVE) {
    return ~((id_connexion) | ((id_bonus) << NBITSFORMOVE));
}

#endif //HACKNSLPROJECT_GAMESTATE_H
