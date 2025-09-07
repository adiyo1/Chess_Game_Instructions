#include "Player.h"


Player::Player(bool isWhite) : Player(isWhite, isWhite ? false : true)
{
}

Player::Player(bool isWhite, bool isUp) 
{
	_isWhite = isWhite;
	_myKing = NULL;
	_isGoingUp = isUp;
}
Player::~Player()
{
}

bool Player::isWhite() const
{
	return _isWhite;
}

void Player::setKing(King* myKing)
{
	_myKing = myKing;
}

King* Player::getKing() const
{
	return _myKing;
}

bool Player::isGoingUp() const
{
	return _isGoingUp;
}
