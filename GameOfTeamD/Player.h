#pragma once
#include "Character.h"
class Player :
	public Character<Circle>
{
public:
	Player(Point pos);
	virtual ~Player();

public:
	///<summary>
	///プレイヤーの場所
	///</summary>
	Point Pos();

	void SetPos(Point pos);

	///<summary>
	///プレイヤーの得点
	///</summary>
	int Score();

private:
	int m_score;
};

