#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "../common/myTypeDef.h"

class board
{
public:
    board();

    board(int boardHeight, int boardWidth);
    void displayBoard(Coordinate_t &point);
    void draw();

private:
    void init();
    string square();

private:
    int m_height;
    int m_width;
    vector<string> m_gridUI;
    vector<vector<int>> m_gridNumber;
    string OUTLINE;
    string INLINE;
};

#endif // BOARD_H
