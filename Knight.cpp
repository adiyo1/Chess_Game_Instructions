// Knight.cpp
#include "Knight.h"
#include "Player.h"
#include "Board.h"
#include <cstdlib> // std::abs

Knight::Knight(Player* pl, int row, int col, Board* brd)
    : Piece(pl, (pl && pl->isWhite()) ? 'N' : 'n', row, col, brd)
{
}

bool Knight::isLegalMove(int row, int col) const
{
    int dr = std::abs(row - this->_row);
    int dc = std::abs(col - this->_col);

    // תנועת פרש: L — שניים בכיוון אחד ואחד בניצב לו
    return (dr == 2 && dc == 1) || (dr == 1 && dc == 2);
}
