// Queen.cpp
#include "Queen.h"
#include "Player.h"
#include "Board.h"
#include <cstdlib> // std::abs

Queen::Queen(Player* pl, int row, int col, Board* brd)
    : Piece(pl, (pl && pl->isWhite()) ? 'Q' : 'q', row, col, brd)
{
}

bool Queen::isLegalMove(int row, int col) const
{
    const int sr = this->_row;
    const int sc = this->_col;
    const int dr = row;
    const int dc = col;

    int drow = dr - sr;
    int dcol = dc - sc;

    if (drow == 0 && dcol == 0) return false; // לא נשארים במקום

    Piece** grid = _brd->getBoard();

    // כמו צריח: אותה שורה או אותה עמודה
    if (drow == 0 || dcol == 0)
    {
        if (drow == 0) { // אופקי
            int stepC = (dcol > 0) ? 1 : -1;
            for (int c = sc + stepC; c != dc; c += stepC) {
                Piece* p = grid[sr * BOARD_SIZE + c];
                if (p && p->getPlayer() != nullptr) return false; // חסום
            }
            return true;
        } else { // אנכי
            int stepR = (drow > 0) ? 1 : -1;
            for (int r = sr + stepR; r != dr; r += stepR) {
                Piece* p = grid[r * BOARD_SIZE + sc];
                if (p && p->getPlayer() != nullptr) return false; // חסום
            }
            return true;
        }
    }

    // כמו רץ: אלכסון (|Δr| == |Δc|)
    if (std::abs(drow) == std::abs(dcol))
    {
        int stepR = (drow > 0) ? 1 : -1;
        int stepC = (dcol > 0) ? 1 : -1;

        int r = sr + stepR;
        int c = sc + stepC;
        while (r != dr && c != dc) {
            Piece* p = grid[r * BOARD_SIZE + c];
            if (p && p->getPlayer() != nullptr) return false; // חסום
            r += stepR;
            c += stepC;
        }
        return true;
    }

    // לא תואם לא צריח ולא רץ
    return false;
}
