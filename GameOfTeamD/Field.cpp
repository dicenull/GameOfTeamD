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
	int32 f_height = m_field_height * m_zk;
	int32 f1_width = (m_puzzle_width + m_player_width) * m_zk;
	int32 f2_width = m_window_size.x - f1_width;
	Color f_color = Palette::Darkgreen;
	Color p_color = Palette::Hotpink;

	// スコア表示部とフィールドの境界線
	Line(0, f_height, m_window_size.x, f_height).draw(3.0, f_color);
	Line(0, m_window_size.y - f_height, m_window_size.x, m_window_size.y - f_height).draw(3.0, f_color);

	// プレイヤーフィールドの境界線
	Line(f1_width, 0, f1_width, f_height).draw(2.0, p_color);
	Line(f2_width, m_window_size.y - f_height, f2_width, m_window_size.y).draw(2.0, p_color);

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
