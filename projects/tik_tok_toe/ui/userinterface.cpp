#include <cstring>
#include "userinterface.h"

UserInterface::UserInterface()
{

}

UserInterface::UserInterface(int height, int width)
{
}

UserInterface::~UserInterface()
{
    delete m_board;
}

void UserInterface::run()
{
    displayMenu();
}

void UserInterface::registerCallbackfn()
{
    m_gameplay->registerCallback(&UserInterface::onActionValid, this, ON_ACTION_VALID);
    m_gameplay->registerCallback(&UserInterface::onActionFail, this, ON_ACTION_FAILED);
    m_gameplay->registerCallback(&UserInterface::onActionNextTurn, this, ON_ACTION_NEXT_TURN);
    m_gameplay->registerCallback(&UserInterface::onActionPlayerWin, this, ON_ACTION_PLAYER_WIN);
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
    ePlayerTurn turn;
    memcpy(&turn, data, sizeof(ePlayerTurn));
    UserInterface* ptr;
    ptr = reinterpret_cast<UserInterface*>(puser);
    ptr->enterMove(turn);
}

void UserInterface::onActionPlayerWin(void *puser, void *data)
{
    ePlayerTurn turn;
    memcpy(&turn, data, sizeof(ePlayerTurn));
    UserInterface* ptr;
    ptr = reinterpret_cast<UserInterface*>(puser);
    cout << "Player " << turn << " win!\n";
}

void UserInterface::displayMenu()
{
    int option;
    cout << "[1] Multiplayer     [2] Play with bot     [3] Quit\n";
    cin >> option;
    switch(option) {
    case 1:
        launchGame(true);
        break;
    case 2:
        launchGame();
        break;
    case 3:
        break;
    }
}

void UserInterface::launchGame(bool isMultiplayer)
{
    int height, width;
    cout << "Enter number of row: ";
    cin >> height;
    cout << "Enter number of column: ";
    cin >> width;
    system("clear");
    m_board = new board(height, width);
    m_gameplay = new gameplay(height, width, isMultiplayer);
    registerCallbackfn();
    enterMove(PLAYER_1_TURN);
}

void UserInterface::draw(Coordinate_t &point)
{
    fflush(stdin);
    system("clear");
    m_board->displayBoard(point);
}

void UserInterface::enterMove(ePlayerTurn turn)
{
    if(turn == PLAYER_BOT_TURN) {
        //wrong senario
        return;
    }
    Coordinate_t point;
    cout << "Player " << (turn == PLAYER_1_TURN ? "1 " : "2 ")
         << "enter the move \n";
    cout << "row: ";
    cin >> point.row;
    cout << "col: ";
    cin >> point.col;
    point.playerTurn = turn;
    m_gameplay->playerMove(point);
}
