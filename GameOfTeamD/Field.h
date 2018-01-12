#pragma once

#include <Siv3D.hpp>
#include "PlayerLib.h"

class Field
{
public:
	Field(int32 field_height = 8, int32 puzzle_width = 10, int32 player_width = 3, int32 zk_size = 25,
		std::map<Players, bool> is_mirrors = { {Players::One, false}, {Players::Two, true } });
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
	int32 Zk() const;

	Point PuzzleOrigin(Players p) const;
	Point PlayerOrigin(Players p) const;
	Point SpaceOrigin(Players p) const;

	Point PuzzleEndPos(Players p) const;
	Point PlayerEndPos(Players p) const;
	Point SpaceEndPos(Players p) const;

	Point FieldBottomLeft(Players p) const;
	Point FieldBottomRight(Players p) const;

	void SetMirror(Players p, bool is_mirror);

	bool IsInPuzzleField(Players p, Point pos) const;
	bool IsInPlayerField(Players p, Point pos) const;
	bool IsInSpaceField(Players p, Point pos) const;
	bool IsInField(Players p, Point pos) const;

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

	std::map<Players, bool> m_is_mirror;
};

