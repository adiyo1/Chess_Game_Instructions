#pragma once

#include "Piece.h"

class NullPiece : public Piece
{
public:
	NullPiece(int, int);

	virtual bool isLegalMove(int, int) const;
private:
};