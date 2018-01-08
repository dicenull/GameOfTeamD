#pragma once

#include <Siv3D.hpp>
#include "PlayerLib.h"

class Block
{
public:
	Block();
	Block(Grid<Color> pieces);
	~Block();

public:
	Grid<Color> GetColor() const;
	static int Max();
	void TurnRight();
	void TurnLeft();
	void SetPos(const Point &pos);

	void Move(Players p);

	void Draw(int32 zk) const;

private:
	static const int length = 2;
	Grid<Color> m_pieces{ length, length };
	Point m_pos;
};

