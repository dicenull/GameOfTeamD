#pragma once
#include "Character.h"
#include "Action.h"
#include "Field.h"

class Player :
	public Character<Circle>
{
public:
	Player(Players p, Point pos);
	virtual ~Player();

public:
	///<summary>
	///プレイヤーの場所
	///</summary>
	Point Pos();

	void SetPos(Point pos);

	void Move(Action action, const Field & field);

	///<summary>
	///プレイヤーの得点
	///</summary>
	int Score();

private:
	int m_score;
	Players m_players;
};

