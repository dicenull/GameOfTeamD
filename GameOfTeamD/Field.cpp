#include "Field.h"
#include <Siv3D.hpp>

Field::Field(int32 field_height, int32 puzzle_width, int32 player_width, int32 zk_size, std::map<Players, bool> is_mirrors)
{
	m_field_height = field_height;
	m_puzzle_width = puzzle_width;
	m_player_width = player_width;
	m_zk = zk_size;

	// パズルのフィールドを初期化
	m_p1_puzzles.resize(Size(puzzle_width, field_height));
	m_p2_puzzles.resize(Size(puzzle_width, field_height));

	m_is_mirror[Players::One] = is_mirrors[Players::One];
	m_is_mirror[Players::Two] = is_mirrors[Players::Two];
}

Field::Field(const Field & other)
	: Field::Field(other.m_player_width, other.m_puzzle_width, other.m_player_width, other.m_zk,
		other.m_is_mirror)
{ }

void Field::operator=(const Field & other)
{
	m_player_width = other.m_player_width;
	m_puzzle_width = other.m_puzzle_width;
	m_field_height = other.m_field_height;
	m_p1_puzzles = other.m_p1_puzzles;
	m_p2_puzzles = other.m_p2_puzzles;
	m_zk = other.m_zk;
}

void Field::Update()
{
	m_window = Window::Size();
}

void Field::Draw() const
{
	// 枠線を描画
	int32 f2_width = m_window.x - Width();
	Color f_color = Palette::Darkgreen;
	Color p_color = Palette::Hotpink;
	Color l_color = Palette::Lightgrey;

	// スコア表示部とフィールドの境界線
	Line(0, Height(), m_window.x, Height()).draw(3.0, f_color);
	Line(0, m_window.y - Height(), m_window.x, m_window.y - Height()).draw(3.0, f_color);

	// プレイヤーフィールドの境界線
	Line(Width(), 0, Width(), Height()).draw(2.0, p_color);
	Line(f2_width, m_window.y - Height(), f2_width, m_window.y).draw(2.0, p_color);

	// パズルフィールドを描画
	for (int w = 0; w < m_puzzle_width; w++)
	{
		for (int h = 0; h < m_field_height; h++)
		{
			auto p1_puzzle = m_p1_puzzles[h][w];
			auto p2_puzzle = m_p2_puzzles[h][w];

			p1_puzzle.set(Point(m_zk * w, m_zk * h), Size(m_zk, m_zk));
			p2_puzzle.set(Point(m_window.x - m_zk * (w + 1), m_window.y - m_zk * (h + 1)), Size(m_zk, m_zk));

			p1_puzzle.drawFrame();
			p2_puzzle.drawFrame();
		}
	}

	// パズルが移動してくるフィールドの補助線
	for (int h = 1; h < m_field_height; h++)
	{
		Line(Vec2(PuzzleWidth(), h * m_zk), Vec2(m_window.x, h * m_zk)).draw(1, l_color);
		Line(Vec2(0, m_window.y - m_zk * h), Vec2(m_window.x - PuzzleWidth(), m_window.y - m_zk * h)).draw(1, l_color);
	}
}

Field::~Field()
{
}

int32 Field::Height() const
{
	return m_field_height * m_zk;
}

int32 Field::Width() const
{
	return (m_puzzle_width + m_player_width) * m_zk;
}

int32 Field::PuzzleWidth() const
{
	return m_puzzle_width * m_zk;
}

int32 Field::PlayerWidth() const
{
	return m_player_width * m_zk;
}

int32 Field::Zk() const
{
	return m_zk;
}

Point Field::PuzzleOrigin(Players p) const
{
	switch (p)
	{
	case Players::One:
		if (m_is_mirror.at(p))
		{
			return Point(m_window.x, 0);
		}
		else
		{
			return Point(0, 0);
		}
	case Players::Two:
		if (m_is_mirror.at(p))
		{
			return Point(m_window.x, m_window.y - Height());
		}
		else
		{
			return Point(0, m_window.y - Height());
		}
	}
}

Point Field::PlayerOrigin(Players p) const
{
	switch (p)
	{
	case Players::One:
		if (m_is_mirror.at(p))
		{
			return Point(m_window.x - PuzzleWidth(), 0);
		}
		else
		{
			return Point(PuzzleWidth(), 0);
		}
	case Players::Two:
		if (m_is_mirror.at(p))
		{
			return Point(m_window.x - PuzzleWidth(), m_window.y - Height());
		}
		else
		{
			return Point(PuzzleWidth(), m_window.y - Height());
		}
	}
}

Point Field::SpaceOrigin(Players p) const
{
	switch (p)
	{
	case Players::One:
		if (m_is_mirror.at(p))
		{
			return Point(m_window.x - Width(), 0);
		}
		else
		{
			return Point(Width(), 0);
		}
	case Players::Two:
		if (m_is_mirror.at(p))
		{
			return Point(m_window.x - Width(), m_window.y - Height());
		}
		else
		{
			return Point(Width(), m_window.y - Height());
		}
	}
}

void Field::SetMirror(Players p, bool is_mirror)
{
	m_is_mirror[p] = is_mirror;
}

bool Field::IsInPuzzleField(Players p, Point pos) const
{
	switch (p)
	{
	case Players::One:
		return (0 <= pos.x && pos.x <= PuzzleWidth()) && (0 <= pos.y && pos.y <= Height());
	case Players::Two:
		return (m_window.x - PuzzleWidth() <= pos.x && pos.x <= m_window.x)
			&& (m_window.y - Height() <= pos.y && pos.y <= m_window.y);
	default:
		return false;
	}
}

bool Field::IsInPlayerField(Players p, Point pos) const 
{
	switch (p)
	{
	case Players::One:
		return (PuzzleWidth() <= pos.x && pos.x <= Field::Width())
			&& (0 <= pos.y && pos.y <= Field::Height());
	case Players::Two:
		return (m_window.x - Field::Width() <= pos.x && pos.x <= m_window.x - PuzzleWidth()) 
			&& (m_window.y - Height() <= pos.y && pos.y <= m_window.y);
	default:
		return false;
	}
}

bool Field::IsInSpaceField(Players p, Point pos)const
{
	switch (p)
	{
	case Players::One:
		return (Width() <= pos.x && pos.x <= m_window.x) 
			&& (0 <= pos.y && pos.y <= Field::Height());
	case Players::Two:
		return (0 <= pos.x && pos.x <= m_window.x - Width())
			&& (m_window.y - Height() <= pos.y && pos.y <= m_window.y);
	default:
		return false;
	}
}

bool Field::IsInField(Players p, Point pos) const
{
	return IsInPuzzleField(p, pos) || IsInPlayerField(p, pos) || IsInSpaceField(p, pos);
}
