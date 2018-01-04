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
	m_puzzles.resize(puzzle_width, std::vector<Rect>(field_height));

}

void Field::Draw()
{
	// パズルフィールドを描画
	for (int w = 0; w < m_puzzle_width; w++)
	{
		for (int h = 0; h < m_field_height; h++)
		{
			auto puzzle = m_puzzles[w][h];

			puzzle.set(Point(m_zk * w, m_zk * h), Size(m_zk, m_zk));
			puzzle.drawFrame();
		}
	}
}

Field::~Field()
{
}
