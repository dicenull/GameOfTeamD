#pragma once

#include <Siv3D.hpp>
#include <vector>

class Field
{
public:
	Field(Size size, int32 field_height = 8, int32 puzzle_width = 10, int32 player_width = 3, int32 zk_size = 25);
	Field(const Field& other);
	void operator=(const Field& other);
	~Field();

public:
	void Draw() const;


private:
	/// <summary>
	/// ウィンドウのサイズ
	/// </summary>
	Size m_window_size;

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

	std::vector<std::vector<Rect>> m_p1_puzzles;
	std::vector<std::vector<Rect>> m_p2_puzzles;
};

