#include "Field.h"

#include <Siv3D.hpp>
#include <vector>

Field::Field(Size size, int32 field_height, int32 puzzle_width, int32 player_width, int32 zk_size)
{
	m_window_size = size;
	m_field_height = field_height;
	m_puzzle_width = puzzle_width;
	m_player_width = player_width;
	m_zk = zk_size;

	// パズルのフィールドを初期化
	m_p1_puzzles.resize(puzzle_width, std::vector<Rect>(field_height));
	m_p2_puzzles.resize(puzzle_width, std::vector<Rect>(field_height));

}

Field::Field(const Field & other)
{
	m_window_size = other.m_window_size;
	m_player_width = other.m_player_width;
	m_puzzle_width = other.m_puzzle_width;
	m_field_height = other.m_field_height;
	m_p1_puzzles = other.m_p1_puzzles;
	m_p2_puzzles = other.m_p2_puzzles;
	m_zk = other.m_zk;
}

void Field::operator=(const Field & other)
{
	m_window_size = other.m_window_size;
	m_player_width = other.m_player_width;
	m_puzzle_width = other.m_puzzle_width;
	m_field_height = other.m_field_height;
	m_p1_puzzles = other.m_p1_puzzles;
	m_p2_puzzles = other.m_p2_puzzles;
	m_zk = other.m_zk;
}

void Field::Draw() const
{
	// 枠線を描画
	int32 f2_width = m_window_size.x - Width();
	Color f_color = Palette::Darkgreen;
	Color p_color = Palette::Hotpink;

	// スコア表示部とフィールドの境界線
	Line(0, Height(), m_window_size.x, Height()).draw(3.0, f_color);
	Line(0, m_window_size.y - Height(), m_window_size.x, m_window_size.y - Height()).draw(3.0, f_color);

	// プレイヤーフィールドの境界線
	Line(Width(), 0, Width(), Height()).draw(2.0, p_color);
	Line(f2_width, m_window_size.y - Height(), f2_width, m_window_size.y).draw(2.0, p_color);

	// パズルフィールドを描画
	for (int w = 0; w < m_puzzle_width; w++)
	{
		for (int h = 0; h < m_field_height; h++)
		{
			auto p1_puzzle = m_p1_puzzles[w][h];
			auto p2_puzzle = m_p2_puzzles[w][h];

			p1_puzzle.set(Point(m_zk * w, m_zk * h), Size(m_zk, m_zk));
			p2_puzzle.set(Point(m_window_size.x - m_zk * (w + 1), m_window_size.y - m_zk * (h + 1)), Size(m_zk, m_zk));

			p1_puzzle.drawFrame();
			p2_puzzle.drawFrame();
		}
	}
}

Field::~Field()
{
}

inline int32 Field::Height() const
{
	return m_field_height * m_zk;
}

inline int32 Field::Width() const
{
	return (m_puzzle_width + m_player_width) * m_zk;
}

inline int32 Field::PuzzleWidth() const
{
	return m_puzzle_width * m_zk;
}

inline int32 Field::PlayerWidth() const
{
	return m_player_width * m_zk;
}

inline int32 Field::Zk() const
{
	return m_zk;
}

bool Field::IsInPuzzleField(Players p, Point pos) const
{
	switch (p)
	{
	case Players::One:
		return (0 <= pos.x && pos.x <= PuzzleWidth()) && (0 <= pos.y && pos.y <= Height());
	case Players::Two:
		return (m_window_size.x - PuzzleWidth() <= pos.x && pos.x <= m_window_size.x)
			&& (m_window_size.y - Height() <= pos.y && pos.y <= m_window_size.y);
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
		return (m_window_size.x - Field::Width() <= pos.x && pos.x <= m_window_size.x - PuzzleWidth()) 
			&& (m_window_size.y - Height() <= pos.y && pos.y <= m_window_size.y);
	default:
		return false;
	}
}

bool Field::IsInOtherField(Players p, Point pos)const
{
	switch (p)
	{
	case Players::One:
		return (Width() <= pos.x && pos.x <= m_window_size.x) 
			&& (0 <= pos.y && pos.y <= Field::Height());
	case Players::Two:
		return (0 <= pos.x && pos.x <= m_window_size.x - Width())
			&& (m_window_size.y - Height() <= pos.y && pos.y <= m_window_size.y);
	default:
		return false;
	}
}
