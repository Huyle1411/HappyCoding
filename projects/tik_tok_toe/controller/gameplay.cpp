#include <iostream>
using namespace std;
#include "gameplay.h"
using namespace std;

gameplay::gameplay()
{

}

gameplay::gameplay(int height, int width) : m_height(height), m_width(width)
{
    m_listcb = vector<CallbackItem_t*>(ON_CALLBACK_MAX, NULL);
    m_gridNumber = vector<vector<int>>(m_height, vector<int>(m_width, 0));
    m_isMultiPlayer = false;
}

gameplay::~gameplay()
{

}

int gameplay::registerCallback(fnCallback func, void *puser, eCallback type)
{
    CallbackItem_t *cbItem = new CallbackItem();
    cbItem->func = func;
    cbItem->puser = puser;
    int ret = 0;
    if (m_listcb[type] != NULL) {
        //Already register
        ret = -1;
    } else {
        m_listcb[type] = cbItem;
    }
    return ret;
}

int gameplay::notify(eCallback type, void *data)
{
    int ret = 0;
    CallbackItem_t *item = m_listcb[type];
    if (item == NULL) {
        // callback type is not registered
        ret = -1;
    } else
        item->func(item->puser, data);

    return ret;
}
int gameplay::playerMove(Coordinate_t point)
{
    if(checkValidMove(point) == false) {
        notify(ON_ACTION_FAILED, &point);
        return -1;
    }
    m_gridNumber[point.x][point.y] = point.playerTurn;
    notify(ON_ACTION_VALID, &point);
    //check win

    //next move
    nextMove(point);
    return 0;
}

int gameplay::nextMove(Coordinate_t point)
{
    if(point.playerTurn == PLAYER_TURN_NONE) {
        //game is not start
        return -1;
    }
    if(point.playerTurn == PLAYER_1_TURN)
        point.playerTurn = (m_isMultiPlayer ? PLAYER_2_TURN : PLAYER_BOT_TURN);
    else
        point.playerTurn = PLAYER_1_TURN;

    if(point.playerTurn != PLAYER_BOT_TURN)
        notify(ON_ACTION_NEXT_MOVE, &point);
    return 0;
}

bool gameplay::checkValidMove(Coordinate_t point)
{
    if(point.x < LOWER_BOUND || point.y < LOWER_BOUND
            || point.x >= m_height || point.y >= m_width)
        return false;
    if(m_gridNumber[point.x][point.y] != 0)
        return false;
    return true;
}
