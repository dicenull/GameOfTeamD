#include "PieceType.h"

Color Piece::ColorParse(PieceType p)
{
	switch (p)
	{
	case PieceType::Red:
		return Palette::Red;
	case PieceType::Blue:
		return Palette::Blue;
	case PieceType::Yellow:
		return Palette::Yellow;
	case PieceType::Green:
		return Palette::Green;
	case PieceType::Purple:
		return Palette::Purple;
	case PieceType::Black:
		return Palette::Black;


	case PieceType::None:
		return Palette::Lightgrey;
	}

	return Color(11, 22, 33);
}