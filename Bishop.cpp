// Bishop.cpp
#include "Bishop.h"
#include "Player.h"
#include "Board.h"
#include <cstdlib> // std::abs

Bishop::Bishop(Player* pl, int row, int col, Board* brd)
    : Piece(pl, (pl && pl->isWhite()) ? 'B' : 'b', row, col, brd)
{
}

bool Bishop::isLegalMove(int row, int col) const
{
    int sr = this->_row;
    int sc = this->_col;
    int dr = row;
    int dc = col;

    int drow = dr - sr;
    int dcol = dc - sc;

    // לא נשארים במקום, וחייב להיות מהלך אלכסוני (|Δr| == |Δc|)
    if (drow == 0 && dcol == 0) return false;
    if (std::abs(drow) != std::abs(dcol)) return false;

    // בדיקת חסימות בדרך (לא כולל יעד)
    int stepR = (drow > 0) ? 1 : -1;
    int stepC = (dcol > 0) ? 1 : -1;

    int r = sr + stepR;
    int c = sc + stepC;

    Piece** grid = _brd->getBoard(); // מערך שטוח בגודל 64

    while (r != dr && c != dc)
    {
        Piece* p = grid[r * BOARD_SIZE + c];
        // אם המשבצת לא ריקה (NullPiece מחזיר getPlayer()==nullptr)
        if (p && p->getPlayer() != nullptr)
            return false; // חסום

        r += stepR;
        c += stepC;
    }

    // היעד עצמו ייבדק ב-Board::tryMove (האם יש כלי שלי וכו')
    return true;
}
