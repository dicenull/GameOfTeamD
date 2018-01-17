#include "Block.h"

#include <stdexcept>

Block::Block()
{
	m_pieces.fill(PieceType::None);
	m_pos = Point();
}

Block::Block(Grid<PieceType> pieces)
{
	m_pieces.resize(pieces.size());
	m_pieces.swap(pieces);
	m_pos = Point();
	m_size = m_pieces.size();
}

Block::~Block()
{
	m_pieces.clear();
}

Grid<Color> Block::GetColor() const
{
	Grid<Color> colors{ m_size };
	
	for (int i = 0; i < m_size.x; i++)
	{
		for (int j = 0; j < m_size.y; j++)
		{
			PieceType p = m_pieces[j][i];
			
			colors[j][i] = Piece::ColorParse(p);
		}
	}

	return colors;
}

Array<Rect> Block::GetAllPieces() const
{
	Array<Rect> pieces;
	int zk = MyGame::Zk;

	for (int i = 0; i < m_size.x; i++)
	{
		for (int j = 0; j < m_size.y; j++)
		{
			if (m_pieces[j][i] != PieceType::None)
			{
				pieces.push_back(Rect(Point(m_pos.x + j * zk, m_pos.y + i * zk), Size(zk, zk)));
			}
		}
	}

	return pieces;
}

Array<PieceType> Block::GetPieces(int height) const
{
	Array<PieceType> pieces;

	for (int i = 0; i < m_size.x; i++)
	{
		if (m_pieces[i][height] != PieceType::None)
		{
			pieces.push_back(m_pieces[i][height]);
		}
	}

	return pieces;
}

void Block::TurnRight()
{
	Grid<PieceType> tmp(m_size);

	for (int i = 0; i < m_size.x; i++)
	{
		for (int j = 0; j < m_size.y; j++)
		{
			tmp[m_size.x - 1 - j][i] = m_pieces[i][j];
		}
	}

	m_pieces.swap(tmp);
}

void Block::TurnLeft()
{
	Grid<PieceType> tmp(m_size);

	for (int i = 0; i < m_size.x; i++)
	{
		for (int j = 0; j < m_size.y; j++)
		{
			tmp[j][m_size.y - 1 - i] = m_pieces[i][j];
		}
	}

	m_pieces.swap(tmp);
}

void Block::SetPos(int height, const Point &pos)
{
	m_pos = pos;
	m_height = height;
}

int Block::GetHeight()
{
	return m_height;
}

Size Block::GetSize()
{
	return m_size;
}

Point Block::GetBottomLeft()
{
	return Point(m_pos.x, m_pos.y + (m_size.y - 1));
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

void Block::Draw(Point origin) const
{
	Rect r;
	int zk = MyGame::Zk;
	for (int i = 0; i < m_size.x; i++)
	{
		for (int j = 0; j < m_size.y; j++)
		{
			r = Rect(origin + Point(m_pos.x + i * zk, m_pos.y + j * zk), zk, zk);
			if (m_pieces[i][j] != PieceType::None)
			{
				r.draw(Piece::ColorParse(m_pieces[i][j]));
				r.drawFrame();
			}
		}
	}
}

