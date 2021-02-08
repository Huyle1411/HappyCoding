#include <cstring>
#include "userinterface.h"

UserInterface::UserInterface()
{

}

UserInterface::UserInterface(int height, int width)
{
    m_board = new board(height, width);
    m_gameplay = new gameplay(height, width);
    registerCallbackfn();
}

UserInterface::~UserInterface()
{
    delete m_board;
}

void UserInterface::registerCallbackfn()
{
    m_gameplay->registerCallback(&UserInterface::onActionValid, this, ON_ACTION_VALID);
    m_gameplay->registerCallback(&UserInterface::onActionFail, this, ON_ACTION_FAILED);
    m_gameplay->registerCallback(&UserInterface::onActionNextTurn, this, ON_ACTION_NEXT_MOVE);
}

void UserInterface::onActionValid(void *puser, void *data)
{
    Coordinate_t point;
    memcpy(&point, data, sizeof(Coordinate_t));
    UserInterface* ptr;
    ptr = reinterpret_cast<UserInterface*>(puser);
    ptr->draw(point);
}

void UserInterface::onActionFail(void *puser, void *data)
{

}

void UserInterface::onActionNextTurn(void *puser, void *data)
{

}

void UserInterface::draw(Coordinate_t &point)
{
    fflush(stdin);
    system("clear");
    m_board->displayBoard(point);
}

void UserInterface::enterMove()
{
    if(m_playerTurn == PLAYER_BOT_TURN) {
        //wrong senario
        return;
    }
    Coordinate_t point;
    cout << "Player " << (m_playerTurn == PLAYER_1_TURN ? "1 " : "2 ")
         << "enter the move \n";
    cout << "x: ";
    cin >> point.x;
    cout << "y: ";
    cin >> point.y;
    point.playerTurn = m_playerTurn;
    m_gameplay->playerMove(point);
}
