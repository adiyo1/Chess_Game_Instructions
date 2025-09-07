#include "Piece.h"
#include <string>
#include <iostream>

using namespace std;

Piece::Piece(Player* pl, char sign, int row, int col, Board* board) :
			_player(pl), _row(row), _col(col), _brd(board), _startRow(row), _startCol(col)
{
	if (pl != NULL && pl->isWhite())
	{
		_sign = toupper(sign);
	}
	else
	{
		_sign = tolower(sign);
	}
}

Piece::~Piece()
{

}

char Piece::getSign() const
{
	return _sign;
}

Player* Piece::getPlayer() const
{
	return _player;
}

void Piece::setPosition(int row, int col) 
{
	_row = row;
	_col = col;
}
bool Piece::isWayFree(int dstRow, int dstCol) const
{
	Piece** matBoard = _brd->getBoard();
	Piece* currPiece = NULL;
	int  i,j;
	// move on the col only
	if (_row == dstRow)
	{
		int startCol = _col < dstCol ? _col : dstCol;
		int endCol = _col < dstCol ? dstCol : _col;

		for (j = startCol + 1; j < endCol ; ++j)
		{
			currPiece = *(matBoard  + _row * BOARD_SIZE + j);

			// if there is player that own the piece
			if (currPiece->getPlayer() != NULL)
			{
				return false;
			}
		}

		return true;
	}
	
	// move on the rows only
	if (_col == dstCol) 
	{
		int startRow = _row < dstRow ? _row : dstRow;
		int endRow = _row < dstRow ? dstRow : _row;

		for (i = startRow + 1; i < endRow; ++i)
		{
			currPiece = *(matBoard + i * BOARD_SIZE + _col);

			// if there is player that own the piece
			if (currPiece->getPlayer() != NULL)
			{
				return false;
			}
		}

		return true;
	}


	// check diagonal move
	int startRow = dstRow < _row ? dstRow : _row;
	int endRow = dstRow < _row ? _row : dstRow;
	int startCol;

	int num = 1;
	if (_row < dstRow)

	{
		startCol = _col;
		if (_col > dstCol)
		{
			num = -1;
		}
	}
	else 
	{
		startCol = dstCol;
		if (_col < dstCol)
		{
			num = -1;
		}
	}

	for (i = startRow + 1, j = startCol+num; i < endRow ; ++i)
	{
		currPiece = *(matBoard + i * 8 + j);

		// check if the board in the place contains null piece
		if (currPiece->getPlayer() != NULL)
		{
			return false;
		}
		j += num;
	}

	return true;
}

