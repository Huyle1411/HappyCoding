#include <cstring>
#include <cctype>
#include "userinterface.h"

UserInterface::UserInterface()
{
    m_board = new board();
    m_gameplay = new gameplay();
    m_isRunning = true;
}

UserInterface::~UserInterface()
{

}

void UserInterface::run()
{
    //default win by 3 consecutive
    system("clear");
    m_settingRule = 3;
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
    cout << "[1] Multiplayer     [2] Play with bot     [3] Setting     [4]Quit\n";
    cin >> option;
    switch(option) {
    case 1:
        launchGame(true);
        break;
    case 2:
        launchGame();
        break;
    case 3:
        cout << "Number of consecutive marks to win: ";
        int rule;
        cin >> rule;
        m_settingRule = rule;
        break;
    case 4:
        release();
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
    m_board->init(height, width);
    m_gameplay->setupConfig(height, width, isMultiplayer, m_settingRule);
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

void UserInterface::release()
{
    delete m_board;
    delete m_gameplay;
    m_isRunning = false;
}

bool UserInterface::isRunning() const
{
    return m_isRunning;
}
