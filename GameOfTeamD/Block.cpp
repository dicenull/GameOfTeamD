#include "Block.h"

#include <stdexcept>

Block::Block()
{
	m_pieces.fill(Palette::White);
	m_pos = Point();
}

Block::Block(Grid<Color> pieces)
{
	if (pieces.size() != m_pieces.size())
		throw std::invalid_argument("ƒs[ƒX”‚ªˆê’v‚µ‚Ä‚¢‚Ü‚¹‚ñ");

	m_pieces.swap(pieces);
	m_pos = Point();
}

Block::~Block()
{
	m_pieces.clear();
}

Grid<Color> Block::GetColor() const
{
	return m_pieces;
}

int Block::Max()
{
	return length;
}

void Block::TurnRight()
{
	Grid<Color> tmp(length, length);

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			tmp[length - 1 - j][i] = m_pieces[i][j];
		}
	}

	m_pieces.swap(tmp);
}

void Block::TurnLeft()
{
	Grid<Color> tmp(length, length);

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			tmp[j][length - 1 - i] = m_pieces[i][j];
		}
	}

	m_pieces.swap(tmp);
}

void Block::SetPos(const Point &pos)
{
	m_pos = pos;
}

void Block::Move(Players p)
{
	switch (p)
	{
	case One:
		m_pos.moveBy(Point::Left);
		break;
	case Two:
		m_pos.moveBy(Point::Right);
		break;
	default:
		break;
	}
}

void Block::Draw(int32 zk) const
{
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			Rect(Point(m_pos.x + i * zk, m_pos.y + j * zk), zk, zk).draw(m_pieces[i][j]);
		}
	}
}

