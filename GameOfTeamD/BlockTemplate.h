#pragma once
#include <Siv3D.hpp>
#include "Block.h"
#include "GameLib.h"

using Level = MyGame::GameLevel;

struct BlockTemplate
{
public:
	static const Block RandomBlock(Level level);
	static PieceType RandomPiece(Level level, bool use_none = true);
};