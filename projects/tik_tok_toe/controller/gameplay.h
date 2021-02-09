#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <vector>
using namespace std;
#include "../common/myTypeDef.h"

const int LOWER_BOUND = 0;

typedef void (*fnCallback)(void *puser, void *data);

typedef struct CallbackItem
{
    fnCallback func;
    void *puser;

    CallbackItem()
    {
        func = NULL;
        puser = NULL;
    }

} CallbackItem_t;

class gameplay
{
public:
    gameplay();
    ~gameplay();

    void setupConfig(int boardHeight, int boardWidth, bool isMulti, int ruleWin);
    int registerCallback(fnCallback func, void *puser, eCallback type);
    int notify(eCallback type, void *data);

    int playerMove(Coordinate_t point);

private:
    bool checkValidMove(Coordinate_t point);
    int nextMove(ePlayerTurn turn);
    void checkWin(Coordinate_t point);

private:
    vector<CallbackItem_t *> m_listcb;
    vector<vector<int>> m_gridNumber;
    int m_height;
    int m_width;
    bool m_isMultiPlayer;
    int m_rule;
};

#endif // GAMEPLAY_H
