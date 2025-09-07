// King.cpp
#include "King.h"
#include "Board.h"
#include <cstdlib>   // std::abs

King::King(Player* pl, int row, int col, Board* brd)
    : Piece(pl, (pl && pl->isWhite()) ? 'K' : 'k', row, col, brd)
{
}

bool King::isLegalMove(int row, int col) const
{
    int dr = std::abs(row - this->_row);
    int dc = std::abs(col - this->_col);

    // The king cannot stay in the same square,
    // and is allowed to move only one step in any direction
    if (dr == 0 && dc == 0) return false;
    return (dr <= 1 && dc <= 1);
}

bool King::isChess()
{
    // Check if any enemy piece is attacking the current king's square
    if (!this->getPlayer()) return false; // Safety check

    int kr = this->_row;
    int kc = this->_col;

    // Access the board pointer from Piece (protected member _brd)
    Board* brd = this->_brd;  
    // If _brd were private, we would need a getter in Piece (e.g. getBoardPtr()).

    // Flat board array: BOARD_SIZE * BOARD_SIZE squares
    Piece** flat = brd->getBoard();
    Player* me = this->getPlayer();

    for (int r = 0; r < BOARD_SIZE; ++r)
    {
        for (int c = 0; c < BOARD_SIZE; ++c)
        {
            Piece* p = flat[r * BOARD_SIZE + c];
            if (!p) continue;                      // Safety check
            Player* owner = p->getPlayer();
            if (owner == nullptr) continue;        // NullPiece (empty square)
            if (owner == me) continue;             // My own piece cannot attack me

            // Can the enemy piece move to the king's square?
            if (p->isLegalMove(kr, kc)) {
                return true; // The king is in check
            }
        }
    }
    return false; // No enemy piece attacks the king → no check
}
