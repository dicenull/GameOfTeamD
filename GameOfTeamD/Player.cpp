#include "Player.h"



Player::Player(Point pos)
{
	this->Shape.setPos(pos);
}


Player::~Player()
{ }

Point Player::Pos()
{
	return Point(this->Shape.x, this->Shape.y);
}

void Player::SetPos(Point pos)
{
	this->Shape.setPos(pos);
}

int Player::Score()
{
	return m_score;
}
