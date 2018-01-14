#pragma once

#include <Siv3D.hpp>
#include "PlayerLib.h"

class Field
{
public:
	Field(int32 field_height = 8, int32 puzzle_width = 10, int32 player_width = 3, int32 zk_size = 25,
		std::map<PlayerType, bool> is_mirrors = { {PlayerType::One, false}, {PlayerType::Two, true } });
	Field(const Field& other);
	void operator=(const Field& other);
	~Field();

public:
	void Draw() const;
	void Update();

	int32 Height() const;
	int32 Width() const;
	int32 PuzzleWidth() const;
	int32 PlayerWidth() const;
	int32 SpaceWidth() const;
	int32 Zk() const;

	Point PuzzleOrigin(PlayerType p) const;
	Point PlayerOrigin(PlayerType p) const;
	Point SpaceOrigin(PlayerType p) const;

	Point PuzzleEndPos(PlayerType p) const;
	Point PlayerEndPos(PlayerType p) const;
	Point SpaceEndPos(PlayerType p) const;

	Point LeftBorder(PlayerType p) const;
	Point RightBorder(PlayerType p) const;

	Point PlayerTopBorder(PlayerType p) const;

	Point PlayerCenter(PlayerType p) const;

	void SetMirror(PlayerType p, bool is_mirror);

	bool IsInPuzzleField(PlayerType p, Point pos) const;
	bool IsInPlayerField(PlayerType p, Point pos) const;
	bool IsInSpaceField(PlayerType p, Point pos) const;
	bool IsInField(PlayerType p, Point pos) const;

	template <class Type>
		bool IsInPlayerField(PlayerType p, Type shape) const;

private:
	Point m_window = Window::Size();

	/// <summary>
	/// プレイヤー一人分のフィールドの高さ[zk]
	/// </summary>
	int32 m_field_height;

	/// <summary>
	/// プレイヤー一人分のパズルフィールドの幅[zk]
	/// </summary>
	int32 m_puzzle_width;

	/// <summary>
	/// プレイヤー一人分のプレイヤーフィールドの幅[zk]
	/// </summary>
	int32 m_player_width;

	/// <summary>
	/// 1[zk]あたりの大きさ
	/// </summary>
	int32 m_zk;

	Grid<Rect> m_p1_puzzles;
	Grid<Rect> m_p2_puzzles;
	
	std::map<PlayerType, bool> m_is_mirror;
};

template<class Type>
bool Field::IsInPlayerField(PlayerType p, Type shape) const
{
	return Rect(PlayerOrigin(p), Size(PlayerWidth(), Height())).contains(shape);
}
