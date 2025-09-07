// Rook.cpp
#include "Rook.h"
#include "Player.h"
#include "Board.h"

Rook::Rook(Player* pl, int row, int col, Board* brd)
    : Piece(pl, (pl && pl->isWhite()) ? 'R' : 'r', row, col, brd)
{
}

bool Rook::isLegalMove(int row, int col) const
{
    // הגנות בסיסיות
    if (!_brd) return false;
    Piece** grid = _brd->getBoard();
    if (!grid) return false;

    // נניח אינדוקס 0..BOARD_SIZE-1 (אם אצלך 1..8 – התאם בהתאם)
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE)
        return false;

    const int sr = this->getRow();
    const int sc = this->getCol();
    const int dr = row;
    const int dc = col;

    const int drow = dr - sr;
    const int dcol = dc - sc;

    // לא נשארים במקום
    if (drow == 0 && dcol == 0) return false;

    // חייב לנוע בקו ישר (או אותה שורה או אותה עמודה)
    if (drow != 0 && dcol != 0) return false;

    // בודקים שאין חסימות בדרך
    if (drow == 0) {
        int stepC = (dcol > 0) ? 1 : -1;
        for (int c = sc + stepC; c != dc; c += stepC) {
            Piece* p = grid[sr * BOARD_SIZE + c];
            // אם יש שם כלי אמיתי (לא NullPiece) – חסום
            if (p && p->getPlayer() != nullptr) return false;
        }
    } else { // dcol == 0
        int stepR = (drow > 0) ? 1 : -1;
        for (int r = sr + stepR; r != dr; r += stepR) {
            Piece* p = grid[r * BOARD_SIZE + sc];
            if (p && p->getPlayer() != nullptr) return false;
        }
    }

    // בודקים את היעד: אסור לאכול כלי של אותו צבע
    Piece* dst = grid[dr * BOARD_SIZE + dc];
    if (dst && dst->getPlayer() != nullptr) {
        // לשני הכלים יש בעלים – מוודאים שהם לא מאותו צד
        if (this->getPlayer() && this->getPlayer()->isWhite() == dst->getPlayer()->isWhite())
            return false; // אותו צבע – לא חוקי
        // יריב – מותר לאכול
    }
    return true;
}