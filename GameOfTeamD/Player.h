#pragma once
#include "Character.h"
class Player :
	public Character<Circle>
{
public:
	Player();
	virtual ~Player();
};

