#include "board.h"

board::board()
{
    std::cout << "Construct board class \n";
}

board::board(int boardHeight, int boardWidth)
    : m_height(boardHeight), m_width(boardWidth)
{
    init();
}

void board::displayBoard(Coordinate_t &point)
{
    char c = (point.playerTurn == PLAYER_1_TURN ? 'X' : 'O');
    m_gridUI[1 + point.row * 2][3 + point.col * 5] = c;
    draw();
}

void board::init()
{
    m_gridUI.clear();
    m_gridNumber = vector<vector<int>>(m_height, vector<int>(m_width, 0));
    int total = m_width * 5 + 2;
    OUTLINE = string(total, '|') + '\n';
    for (int i = 0; i < m_width; ++i)
        INLINE += "|===|";
    INLINE = "|" + INLINE + "|" + '\n';

    m_gridUI.push_back(OUTLINE);
    for (int i = 0; i < m_height; ++i) {
        string lineToPlay = "|" + square() + "|" + '\n';
        m_gridUI.push_back(lineToPlay);

        // not draw inline for last row
        if (i != m_height - 1)
            m_gridUI.push_back(INLINE);
    }
    m_gridUI.push_back(OUTLINE);
    draw();
}

string board::square()
{
    string ret;
    //    ret = "| " + " " + " |";
    string singleSquare = "|   |";
    for (int i = 0; i < m_width; ++i)
        ret += singleSquare;
    return ret;
}

/*
 * |||||||||||||||||
 * ||   || X ||   ||
 * ||===||===||===||
 * || X || O || X ||
 * ||===||===||===||
 * ||   || X ||   ||
 * |||||||||||||||||
 */

void board::draw()
{
    for(string str : m_gridUI)
        cout << str;
}
