#include "Block.h"

#include <stdexcept>

Block::Block()
{
	m_pieces.fill(PieceType::None);
	m_pos = Point();
}

Block::Block(Grid<PieceType> pieces)
{
	if (pieces.size() != m_pieces.size())
		throw std::invalid_argument("ÉsÅ[ÉXêîÇ™àÍívÇµÇƒÇ¢Ç‹ÇπÇÒ");

	m_pieces.swap(pieces);
	m_pos = Point();
}

Block::~Block()
{
	m_pieces.clear();
}

int Block::MaxLength()
{
	return length;
}

Grid<Color> Block::GetColor() const
{
	Grid<Color> colors{ Size(length, length) };
	
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			PieceType p = m_pieces[j][i];
			
			colors[j][i] = Piece::ColorParse(p);
		}
	}

	return colors;
}

Array<Rect> Block::GetPieces(int32 zk) const
{
	Array<Rect> pieces;

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if (m_pieces[j][i] != PieceType::None)
			{
				pieces.push_back(Rect(Point(m_pos.x + j * zk, m_pos.y + i * zk), Size(zk, zk)));
			}
		}
	}

	return pieces;
}

void Block::TurnRight()
{
	Grid<PieceType> tmp(length, length);

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
	Grid<PieceType> tmp(length, length);

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

Point Block::GetBottomLeft()
{
	return Point(m_pos.x, m_pos.y + (length - 1));
}

void Block::Move(Action action)
{
	switch (action)
	{
	case Action::Left:
		m_pos.moveBy(Point::Left);
		break;
	case Action::Right:
		m_pos.moveBy(Point::Right);
		break;
	default:
		break;
	}
}

void Block::Draw(int32 zk) const
{
	Rect r;
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			r = Rect(Point(m_pos.x + i * zk, m_pos.y + j * zk), zk, zk);
			if (m_pieces[i][j] != PieceType::None)
			{
				r.draw(Piece::ColorParse(m_pieces[i][j]));
				r.drawFrame();
			}
		}
	}
}

