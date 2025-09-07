#pragma once

#include "Player.h"
#include "Board.h"
#include "Pipe.h"

class Manager
{
public:
	Manager(Pipe&);
	~Manager();
	int playMove(string move);
	void playGame();

private:
	Player* _player1;
	Player* _player2;
	Player* _currPlayer;
	Player* _otherPlayer;
	Board* _brd;
	Pipe _pipe;

	bool isValidMove(int) const;
	void changeTurn();
};

