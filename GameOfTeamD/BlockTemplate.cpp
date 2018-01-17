#include "BlockTemplate.h"

using Level = MyGame::GameLevel;

const Block BlockTemplate::RandomBlock(Level level)
{
	return 
	{Grid<PieceType>(2,2,
	{
		RandomPiece(level, false), RandomPiece(level, false),
		RandomPiece(level), RandomPiece(level)
	})};
}

PieceType BlockTemplate::RandomPiece(Level level, bool use_none)
{
	Array<PieceType> list;
	switch (level)
	{
	case Level::Easy:
		list = { PieceType::Red, PieceType::Blue, PieceType::Green };
		break;
	case Level::Normal:
		list = { PieceType::Red, PieceType::Blue, PieceType::Green, PieceType::Yellow };
		break;
	case Level::Hard:
		list = { PieceType::Red, PieceType::Blue, PieceType::Green, PieceType::Yellow, PieceType::Purple };
		break;
	}

	if (use_none)
	{
		list.push_back(PieceType::None);
	}

	return RandomSelect(list);
}