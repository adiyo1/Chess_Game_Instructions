#include "Board.h"
#include "NullPiece.h"
#include <iostream>


Board::Board(Player* p1, Player* p2)
{
    // Initialize last move tracking
    _lastSrcRow = -1;
    _lastSrcCol = -1;
    _lastDstRow = -1;
    _lastDstCol = -1;
    _lastPiece = nullptr;
    
    // Initialize board with pieces
    
    // Fill empty squares with NullPiece
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            _brd[i][j] = new NullPiece(i,j);
        }
    }
    
    
}

Board::~Board()
{
    // Clean up all pieces on the board
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            delete _brd[i][j];
        }
    }
}

void Board::print() const
{
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            cout << _brd[i][j]->getSign();
        }
        cout << endl;
    }
}

void Board::getString(char res[]) const
{
    int index = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            res[index++] = _brd[i][j]->getSign();
        }
    }
    res[index] = '\0'; // Null terminate the string
}

bool Board::isPieceOfPlayer(int row, int col, Player* pl) const
{
    // Check bounds
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return false;
    }
    
    // Check if piece belongs to player
    return _brd[row][col]->getPlayer() == pl;
}

bool Board::tryMove(int srcRow, int srcCol, int dstRow, int dstCol) const
{
    // Check bounds
    if (srcRow < 0 || srcRow >= BOARD_SIZE || srcCol < 0 || srcCol >= BOARD_SIZE ||
        dstRow < 0 || dstRow >= BOARD_SIZE || dstCol < 0 || dstCol >= BOARD_SIZE) {
        return false;
    }
    
    // Get source piece
    Piece* srcPiece = _brd[srcRow][srcCol];
    
    // Check if source has a real piece (not NullPiece)
    if (srcPiece->getSign() == '#') { // Assuming NullPiece returns ' '
        return false;
    }
    
    // Check if the piece can move to destination
    return srcPiece->isLegalMove(dstRow, dstCol);
}

Piece** Board::getBoard() const
{
    // Return pointer to the board array
    return (Piece**)_brd;
}

void Board::Move(int srcRow, int srcCol, int dstRow, int dstCol)
{
    // Store last move for undo functionality
    _lastSrcRow = srcRow;
    _lastSrcCol = srcCol;
    _lastDstRow = dstRow;
    _lastDstCol = dstCol;
    _lastPiece = _brd[dstRow][dstCol]; // Store piece that will be captured
    
    // Perform the move
    _brd[dstRow][dstCol] = _brd[srcRow][srcCol];
    _brd[srcRow][srcRow] = new NullPiece(srcRow,srcRow);
}

void Board::undoLastMove()
{
    if (_lastSrcRow == -1) {
        return; // No move to undo
    }
    
    // Restore the board state
    delete _brd[_lastSrcRow][_lastSrcCol]; // Delete the NullPiece
    _brd[_lastSrcRow][_lastSrcCol] = _brd[_lastDstRow][_lastDstCol]; // Move piece back
    _brd[_lastDstRow][_lastDstCol] = _lastPiece; // Restore captured piece
    
    // Reset last move tracking
    _lastSrcRow = -1;
    _lastSrcCol = -1;
    _lastDstRow = -1;
    _lastDstCol = -1;
    _lastPiece = nullptr;
}
