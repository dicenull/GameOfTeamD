#include "Block.h"

#include <stdexcept>

Block::Block()
{
	m_pieces.fill(Palette::White);
}

Block::Block(Grid<Color> pieces)
{
	if (pieces.size() != m_pieces.size())
		throw std::invalid_argument("ƒs[ƒX”‚ªˆê’v‚µ‚Ä‚¢‚Ü‚¹‚ñ");

	m_pieces.swap(pieces);
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

void Block::Flip()
{
}

void Block::Draw(int w, int h, int32 zk) const
{
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			Rect(Point((w + i) * zk, (h + j) * zk), zk, zk).draw(m_pieces[i][j]);
		}
	}
}

