#pragma once
#include <Siv3D.hpp>
#include "Block.h"

namespace BlockTemplate
{
	const Block LBlock{ Grid<PieceType>(2,2, { PieceType::None, PieceType::Red, PieceType::Blue, PieceType::Green } ) };


}

