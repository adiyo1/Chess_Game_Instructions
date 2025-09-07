#include "Manager.h"
#include "King.h"
#include <string.h>
#include <iostream>
#include <exception>

using namespace std;

#define VALID_MOVE 0
#define VALID_CHESS_MOVE 1
#define INVALID_NOT_YOUR_PLAYER 2
#define INVALID_DEST_NOT_FREE 3
#define INVALID_CHESS_WILL_OCCURE 4
#define INVALID_OUT_OF_BOUNDS 5
#define INVALID_ILLEGAL_MOVE 6
#define INVALID_SRC_AND_DEST_EQUAL 7
#define CHECK_MATE 8

Manager::Manager(Pipe& graphicsPipe)
{
	_player1 = new Player(true);
	_player2 = new Player(false);

	_currPlayer = NULL;
	_otherPlayer = NULL;

	_brd = new Board(_player1, _player2);
	_pipe = graphicsPipe;

}

bool Manager::isValidMove(int code) const
{
	if (code <= 1)
		return true;

	return false;
}

void Manager::changeTurn()
{
	Player* temp = _currPlayer;
	_currPlayer = _otherPlayer;
	_otherPlayer = temp;

}
int Manager::playMove(string move)
{
	int srcRow = BOARD_SIZE - (move[1] - '0');
	int srcCol = move[0] - 'a';
	int dstRow = BOARD_SIZE -  (move[3] - '0');
	int dstCol = move[2] - 'a';

	cout << "Move from: " << srcRow << ", " << srcCol << "To " << dstRow << ", " << dstCol << endl;
	
	if (srcRow < 0 || srcRow >= BOARD_SIZE ||
		srcCol < 0 || srcCol >= BOARD_SIZE ||
		dstRow < 0 || dstRow >= BOARD_SIZE ||
		dstCol < 0 || dstCol >= BOARD_SIZE)
	{
		return INVALID_OUT_OF_BOUNDS;
	}

	
	if (!_brd->isPieceOfPlayer(srcRow, srcCol, _currPlayer))
	{
		return INVALID_NOT_YOUR_PLAYER;
	}

	if (_brd->isPieceOfPlayer(dstRow, dstCol, _currPlayer))
	{
		return INVALID_DEST_NOT_FREE;
	}


	if (srcRow == dstRow && srcCol == dstCol)
	{
		return INVALID_SRC_AND_DEST_EQUAL;
	}

	if (!_brd->tryMove(srcRow, srcCol, dstRow, dstCol))
	{
		return INVALID_ILLEGAL_MOVE;
	}

	// Make the move!
	_brd->Move(srcRow, srcCol, dstRow, dstCol);

	// check for chess
	if (_currPlayer->getKing()->isChess())
	{
		_brd->print();
		// if chess undo the last move
		_brd->undoLastMove();

		return INVALID_CHESS_WILL_OCCURE;
	}



	int res;
	// after move check if it is chess
	if (_otherPlayer->getKing()->isChess())
	{
		res =  VALID_CHESS_MOVE;
	}
	else
	{
		res = VALID_MOVE;
	}

	this->changeTurn();
	return res;

} 

void Manager::playGame()
{
	_currPlayer = _player2;
	_otherPlayer = _currPlayer == _player1 ? _player2 : _player1;

	char msgToGraphics[66];

	try{
		_brd->getString(msgToGraphics);
		msgToGraphics[64] = _currPlayer->isWhite() ? '0' : '1';
		msgToGraphics[65] = 0;

		_pipe.sendMessageToGraphics(msgToGraphics);   // send the board string

		_brd->print();

		// get message from graphics
		string msgFromGraphics = _pipe.getMessageFromGraphics();

		while (msgFromGraphics != "quit")
		{
			// should handle the string the sent from graphics
			// according the protocol. Ex: e2e4           (move e2 to e4)
			int r = playMove(msgFromGraphics);
			msgToGraphics[0] = (char)(r + '0');
			msgToGraphics[1] = 0;

			// return result to graphics		
			_pipe.sendMessageToGraphics(msgToGraphics);


			_brd->print();

			// get message from graphics
			msgFromGraphics = _pipe.getMessageFromGraphics();
		}
	}
	catch (exception e)
	{
		cout << "Exception was thrown: " << e.what() << endl;
		system("pause");
	}
}

Manager::~Manager()
{
	delete _player1;
	delete _player2;
	delete _brd;
}
