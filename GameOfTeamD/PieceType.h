#pragma once
#include <Siv3D.hpp>

///<summary>
/// ピースの色または種類
///</summary>
enum class PieceType
{
	None, Red, Blue, Yellow, Green, Purple, Black
};

namespace Piece
{
	///<summary>
	/// ピースの種類から色に変換する
	///</summary>
	///<param name="p">元になるピースの種類</param>
	Color ColorParse(PieceType p);
}