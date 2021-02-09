#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "board.h"
#include "../controller/gameplay.h"
#include "../common/myTypeDef.h"

class UserInterface
{
public:
    UserInterface();
    ~UserInterface();

    void run();

    void registerCallbackfn();
    static void onActionValid(void *puser, void *data);
    static void onActionFail(void *puser, void *data);
    static void onActionNextTurn(void *puser, void *data);
    static void onActionPlayerWin(void *puser, void *data);

    void displayMenu();
    void launchGame(bool isMultiplayer = false);

    void draw(Coordinate_t &point);
    void enterMove(ePlayerTurn turn);

    bool isRunning() const;

private:
    void release();

private:
    board *m_board;
    gameplay *m_gameplay;
    int m_settingRule;
    bool m_isRunning;
};

#endif // USERINTERFACE_H
