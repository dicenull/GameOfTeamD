#include "Field.h"

#include <Siv3D.hpp>

Field::Field(Size size, int32 field_height, int32 puzzle_width, int32 player_width, int32 zk_size)
{
	m_window_size = size;
	m_field_height = field_height;
	m_puzzle_width = puzzle_width;
	m_player_width = player_width;
	m_zk = zk_size;
}

Field::~Field()
{
}
