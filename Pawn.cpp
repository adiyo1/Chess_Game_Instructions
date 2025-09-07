// Pawn.cpp
#include "Pawn.h"
#include "Player.h"
#include "Board.h"
#include <cstdlib> // std::abs

Pawn::Pawn(Player* pl, int row, int col, Board* brd)
    : Piece(pl, (pl&& pl->isWhite()) ? 'P' : 'p', row, col, brd)
{
}

bool Pawn::isLegalMove(int row, int col) const
{
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) return false;

    const int sr = this->getRow();
    const int sc = this->getCol();
    const int dr = row;
    const int dc = col;

    const int drow = dr - sr;
    const int dcol = dc - sc;

    if (drow == 0 && dcol == 0) return false; // cannot stay in place

    // movement direction: white moves up (-1), black moves down (+1)
    const bool white = this->getPlayer() && this->getPlayer()->isWhite();
    const int dir = white ? -1 : 1;

    Piece** grid = _brd->getBoard();
    Piece* dst = grid[dr * BOARD_SIZE + dc];
    const bool dstEmpty = (dst == nullptr) || (dst->getPlayer() == nullptr);

    // 1) one step forward — must be empty
    if (dcol == 0 && drow == dir) {
        return dstEmpty;
    }

    // 2) two steps forward — only from start row; both squares must be empty
    if (dcol == 0 && drow == 2 * dir) {
        const int startRow = white ? 6 : 1;
        if (sr != startRow) return false;

        const int midr = sr + dir;
        Piece* mid = grid[midr * BOARD_SIZE + sc];
        const bool midEmpty = (mid == nullptr) || (mid->getPlayer() == nullptr);

        return midEmpty && dstEmpty;
    }

    // 3) diagonal capture — one step forward diagonally, target must be enemy
    if (drow == dir && std::abs(dcol) == 1) {
        return (dst != nullptr) && (dst->getPlayer() != nullptr) &&
            (dst->getPlayer() != this->getPlayer());
    }

    return false;
}
