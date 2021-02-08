#ifndef MYTYPEDEF_H
#define MYTYPEDEF_H

enum eCallback
{
    ON_ACTION_VALID = 0,
    ON_ACTION_FAILED,
    ON_ACTION_NEXT_MOVE,
    ON_CALLBACK_MAX
};

enum ePlayerTurn
{
    PLAYER_TURN_NONE = 0,
    PLAYER_1_TURN,
    PLAYER_2_TURN,
    PLAYER_BOT_TURN
};

struct Coordinate_t
{
    int x;
    int y;
    ePlayerTurn playerTurn;
};

#endif // MYTYPEDEF_H
