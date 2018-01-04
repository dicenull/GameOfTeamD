#pragma once
#include "Character.h"
class Player :
	public Character<Circle>
{
public:
	Player();
	virtual ~Player();

public:
	int Point();

private:
	int m_point;
};

