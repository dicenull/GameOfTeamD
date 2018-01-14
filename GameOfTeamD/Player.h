#pragma once
#include "Character.h"
#include "Action.h"
#include "Field.h"

class Player :
	public Character<Circle>
{
public:
	Player(PlayerType p, Point pos);
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

	PlayerType GetPlayerType();

private:
	int m_score;
	PlayerType m_player_type;
};

