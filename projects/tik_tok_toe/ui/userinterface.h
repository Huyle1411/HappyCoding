#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "board.h"
#include "../controller/gameplay.h"
#include "../controller/myTypeDef.h"

class UserInterface
{
public:
    UserInterface();
    UserInterface(int height, int width);
    ~UserInterface();

    void registerCallbackfn();
    static void onActionValid(void *puser, void *data);
    static void onActionFail(void *puser, void *data);
    static void onActionNextTurn(void *puser, void *data);


    void draw(Coordinate_t &point);
    void enterMove();

private:
    board *m_board;
    gameplay *m_gameplay;
    ePlayerTurn m_playerTurn;
};

#endif // USERINTERFACE_H
