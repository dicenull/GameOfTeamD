#pragma once
#include <Siv3D.hpp>

enum class PieceType
{
	None, Red, Blue, Yellow, Green, Purple, Black
};

namespace Piece
{
	Color ColorParse(PieceType p);
}