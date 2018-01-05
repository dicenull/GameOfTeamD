#pragma once

#include <Siv3D.hpp>

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
	void Flip();

	void Draw(int w, int h, int32 zk) const;

private:
	static const int length = 2;
	Grid<Color> m_pieces{ length, length };
};

