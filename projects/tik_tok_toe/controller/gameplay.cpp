#include <iostream>
#include <algorithm>
using namespace std;
#include "gameplay.h"
using namespace std;

gameplay::gameplay()
{
    m_listcb = vector<CallbackItem_t*>(ON_CALLBACK_MAX, NULL);
}

gameplay::~gameplay()
{

}

void gameplay::setupConfig(int boardHeight, int boardWidth, bool isMulti, int ruleWin)
{
    m_height = boardHeight;
    m_width = boardWidth;
    m_isMultiPlayer = isMulti;
    m_rule = ruleWin;
    m_gridNumber = vector<vector<int>>(m_height, vector<int>(m_width, 0));
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
    m_gridNumber[point.row][point.col] = point.playerTurn;
    notify(ON_ACTION_VALID, &point);
    //check win
    checkWin(point);

    return 0;
}

int gameplay::nextMove(ePlayerTurn turn)
{
    if(turn == PLAYER_TURN_NONE) {
        //game is not start
        return -1;
    }
    if(turn == PLAYER_1_TURN)
        turn = (m_isMultiPlayer ? PLAYER_2_TURN : PLAYER_BOT_TURN);
    else
        turn = PLAYER_1_TURN;

    if(turn != PLAYER_BOT_TURN)
        notify(ON_ACTION_NEXT_TURN, &turn);
    return 0;
}

void gameplay::checkWin(Coordinate_t point)
{
    int cnt = 0;
    int low, high, turn = point.playerTurn;

    // check vertical
    low = max(0, point.row - m_rule + 1);
    high = min(m_height - 1, point.row + m_rule - 1);
    if(high - low >= m_rule - 1) {
        for(int i = 0; i < m_rule && (low + i < m_height); ++i)
            cnt += (m_gridNumber[low + i][point.col] == turn);
        int cur = low + m_rule - 1;
        while(cur <= high) {
            if(cur != low + m_rule - 1)
                cnt = cnt + (m_gridNumber[cur][point.col] == turn)
                      - (m_gridNumber[cur - m_rule][point.col] == turn);
            if(cnt == m_rule) {
                notify(ON_ACTION_PLAYER_WIN, &point.playerTurn);
                return;
            }
            ++cur;
        }
    }

    // check horizon
    cnt = 0;
    low = max(0, point.col - m_rule + 1);
    high = min(m_width - 1, point.col + m_rule - 1);
    if(high - low >= m_rule - 1) {
        for(int i = 0; i < m_rule && (low + i < m_width); ++i)
            cnt += (m_gridNumber[point.row][low + i] == turn);
        int cur = low + m_rule - 1;
        while(cur <= high) {
            if(cur != low + m_rule - 1)
                cnt = cnt + (m_gridNumber[point.row][cur] == turn)
                      - (m_gridNumber[point.row][cur - m_rule] == turn);
            if(cnt == m_rule) {
                notify(ON_ACTION_PLAYER_WIN, &point.playerTurn);
                return;
            }
            ++cur;
        }
    }

    //check main diagonal
    cnt = 0;
    int moveDown = min(point.row - max(0, point.row - m_rule + 1),
                       point.col - max(0, point.col - m_rule + 1));
    int moveUp = min(min(m_height - 1, point.row + m_rule - 1) - point.row,
                     min(m_width - 1, point.col + m_rule - 1) - point.col);
    int lowRow = point.row - moveDown, lowCol = point.col - moveDown;
    int highRow = point.row + moveUp, highCol = point.col + moveUp;
    if(moveDown + moveUp >= m_rule - 1) {
        for(int i = 0; i < m_rule; ++i)
            cnt += (m_gridNumber[lowRow + i][lowCol + i] == turn);
        int curRow = lowRow + m_rule - 1, curCol = lowCol + m_rule - 1;
        while(curRow <= highRow && curCol <= highCol) {
            if(curRow != lowRow + m_rule - 1)
                cnt = cnt + (m_gridNumber[curRow][curCol] == turn)
                      - (m_gridNumber[curRow - m_rule][curCol - m_rule] == turn);
            if(cnt == m_rule) {
                notify(ON_ACTION_PLAYER_WIN, &point.playerTurn);
                return;
            }
            ++curRow;
            ++curCol;
        }
    }

    // check counter-diagonal
    cnt = 0;
    int sum = point.row + point.col;
    moveDown = min(min(m_width - 1, point.col + m_rule - 1) - point.col,
                   point.row - max(0, point.row - m_rule + 1));
    moveUp = min(min(m_height - 1, point.row + m_rule - 1) - point.row,
                 point.col - max(0, point.col - m_rule + 1));
    lowRow = point.row - moveDown, lowCol = point.col + moveDown;
    highRow = point.row + moveUp, highCol = point.col - moveUp;
    if(moveDown + moveUp >= m_rule - 1) {
        for(int i = 0; i < m_rule; ++i)
            cnt += (m_gridNumber[lowRow + i][lowCol - i] == turn);
        int curRow = lowRow + m_rule - 1, curCol = lowCol - m_rule + 1;
        while(curRow <= highRow && curCol >= highCol) {
            if(curRow != lowRow + m_rule - 1)
                cnt = cnt + (m_gridNumber[curRow][curCol] == turn)
                      - (m_gridNumber[curRow - m_rule][curCol + m_rule] == turn);
            if(cnt == m_rule) {
                notify(ON_ACTION_PLAYER_WIN, &point.playerTurn);
                return;
            }
            ++curRow;
            --curCol;
        }
    }

    nextMove(point.playerTurn);
}

bool gameplay::checkValidMove(Coordinate_t point)
{
    if(point.row < LOWER_BOUND || point.col < LOWER_BOUND
            || point.row >= m_height || point.col >= m_width)
        return false;
    if(m_gridNumber[point.row][point.col] != 0)
        return false;
    return true;
}
