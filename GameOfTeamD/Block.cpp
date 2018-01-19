#include "Block.h"

#include <stdexcept>

Block::Block()
{
	m_pieces.fill(PieceType::None);
	m_pos = Point();
	m_is_black = false;
}

Block::Block(Grid<PieceType> pieces)
{
	m_pieces.resize(pieces.size());
	m_pieces.swap(pieces);
	m_pos = Point();

	m_is_black = true;
	for (auto piece : m_pieces)
	{
		if (piece != PieceType::None && piece != PieceType::Black)
		{
			m_is_black = false;
			break;
		}
	}
}

Block::~Block()
{
	m_pieces.clear();
}

Grid<Color> Block::GetColor() const
{
	Grid<Color> colors{ m_pieces.size() };
	
	for (int i = 0; i < m_pieces.size().x; i++)
	{
		for (int j = 0; j < m_pieces.size().y; j++)
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

	for (int i = 0; i < m_pieces.size().x; i++)
	{
		for (int j = 0; j < m_pieces.size().y; j++)
		{
			if (m_pieces[j][i] != PieceType::None)
			{
				pieces.push_back(Rect(Point(m_pos.x + i * zk, m_pos.y + j * zk), Size(zk, zk)));
			}
		}
	}

	return pieces;
}

Array<PieceType> Block::GetPieces(int height) const
{
	Array<PieceType> pieces;

	for (int i = 0; i < m_pieces.size().x; i++)
	{
		if (m_pieces[height][i] != PieceType::None)
		{
			pieces.push_back(m_pieces[height][i]);
		}
	}

	return pieces;
}

void Block::TurnRight()
{
	Grid<PieceType> tmp(m_pieces.size());

	for (int i = 0; i < m_pieces.size().x; i++)
	{
		for (int j = 0; j < m_pieces.size().y; j++)
		{
			tmp[m_pieces.size().x - 1 - j][i] = m_pieces[i][j];
		}
	}

	m_pieces.swap(tmp);
}

void Block::TurnLeft()
{
	Grid<PieceType> tmp(m_pieces.size());

	for (int i = 0; i < m_pieces.size().x; i++)
	{
		for (int j = 0; j < m_pieces.size().y; j++)
		{
			tmp[j][m_pieces.size().y - 1 - i] = m_pieces[i][j];
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
	return m_pieces.size();
}

void Block::Move(Action action)
{
	int speed = 1;
	if (m_is_black)
	{
		speed = 2;
	}

	switch (action)
	{
	case Action::Left:
		m_pos.moveBy(Point::Left * speed);
		break;
	case Action::Right:
		m_pos.moveBy(Point::Right * speed);
		break;
	default:
		break;
	}
}

void Block::Draw(Point origin) const
{
	Rect r;
	int zk = MyGame::Zk;
	for (int i = 0; i < m_pieces.size().x; i++)
	{
		for (int j = 0; j < m_pieces.size().y; j++)
		{
			r = Rect(origin + Point(m_pos.x + i * zk, m_pos.y + j * zk), zk, zk);
			if (m_pieces[j][i] != PieceType::None)
			{
				r.draw(Piece::ColorParse(m_pieces[j][i]));
				r.drawFrame();
			}
		}
	}
}

