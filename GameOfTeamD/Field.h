#pragma once

#include <Siv3D.hpp>
#include <map>
#include "Block.h"
#include "PlayerLib.h"
#include "Action.h"
#include "PieceType.h"

class Block;

class Field
{
public:
	///<summary>
	/// コンストラクタ
	///</summary>
	///<param name="field_heigt">フィールドの高さ[zk]</param>
	///<param name="puzzle_width">パズルフィールドの幅[zk]</param>
	///<param name="player_width">プレイヤーフィールドの幅[zk]</param>
	///<param name="is_mirrors">各プレイヤーのフィールドを反転するか</param>
	Field(int32 field_height = 8, int32 puzzle_width = 10, int32 player_width = 3,
		std::map<PlayerType, bool> is_mirrors = { {PlayerType::One, false}, {PlayerType::Two, true } });

	///<summary>
	/// コンストラクタ
	///</summary>
	Field(const Field& other);
	void operator=(const Field& other);

	///<summary>
	/// デストラクタ
	///</summary>
	~Field();

public:
	std::map<PlayerType, Array<std::pair<Block, int>>> BlackBlocks;

public:
	///<summary>
	/// フィールドを描画する
	///</summary>
	void Draw() const;

	///<summary>
	/// フィールドの状態を更新する
	///</summary>
	void Update();

	///<summary>
	/// フィールドにブロックを追加する
	///</summary>
	void SetBlock(PlayerType p, Block block);

	///<summary>
	/// フィールドの高さを取得する
	///</summary>
	int32 Height() const;

	int32 HeightCount() const;

	///<summary>
	/// パズルフィールドとプレイヤーフィールドの幅を合わせた大きさを取得する
	///</summary>
	int32 Width() const;

	///<summary>
	/// パズルフィールドの幅を取得する
	///</summary>
	int32 PuzzleWidth() const;

	///<summary>
	/// プレイヤーフィールドの幅を取得する
	///</summary>
	int32 PlayerWidth() const;

	///<summary>
	/// ブロックが移動するフィールドの幅を取得する
	///</summary>
	int32 SpaceWidth() const;

	///<summary>
	/// パズルフィールドの左上の座標
	///</summary>
	///<param name="p">どのプレイヤーがいるフィールドか</param>
	Point PuzzleOrigin(PlayerType p) const;
	///<summary>
	/// プレイヤーフィールドの左上の座標
	///</summary>
	///<param name="p">どのプレイヤーがいるフィールドか</param>
	Point PlayerOrigin(PlayerType p) const;
	///<summary>
	/// ブロックが移動するフィールドの左上の座標
	///</summary>
	///<param name="p">どのプレイヤーがいるフィールドか</param>
	Point SpaceOrigin(PlayerType p) const;

	///<summary>
	/// パズルフィールドの右下の座標
	///</summary>
	///<param name="p">どのプレイヤーがいるフィールドか</param>
	Point PuzzleEndPos(PlayerType p) const;
	///<summary>
	/// プレイヤーフィールドの右下の座標
	///</summary>
	///<param name="p">どのプレイヤーがいるフィールドか</param>
	Point PlayerEndPos(PlayerType p) const;
	///<summary>
	/// ブロックが移動するフィールドの右下の座標
	///</summary>
	///<param name="p">どのプレイヤーがいるフィールドか</param>
	Point SpaceEndPos(PlayerType p) const;

	///<summary>
	/// フィールドのスコアボードとの境界である左下の座標
	///</summary>
	///<param name="p">どのプレイヤーがいるフィールドか</param>
	Point LeftBorder(PlayerType p) const;

	///<summary>
	/// フィールドのスコアボードとの境界である右下の座標
	///</summary>
	///<param name="p">どのプレイヤーがいるフィールドか</param>
	Point RightBorder(PlayerType p) const;

	///<summary>
	/// プレイヤーフィールドのSpaceフィールドの境界の上の座標
	///</summary>
	///<param name="p">どのプレイヤーがいるフィールドか</param>
	Point PlayerTopBorder(PlayerType p) const;

	///<summary>
	/// プレイヤーフィールドの中点
	///</summary>
	///<param name="p">どのプレイヤーがいるフィールドか</param>
	Point PlayerCenter(PlayerType p) const;

	///<summary>
	/// ブロックが移動するフィールドの端、左上の座標
	///</summary>
	///<param name="p">どのプレイヤーがいるフィールドか</param>
	Point BlockStartPos(PlayerType p) const;

	///<summary>
	/// フィールドを反転するか設定する
	///</summary>
	///<param name="p">どのプレイヤーがいるフィールドか</param>
	///<param name="is_mirror">反転するか</param>
	void SetMirror(PlayerType p, bool is_mirror);

	///<summary>
	/// プレイヤーのフィールドが反転しているか取得する
	///</summary>
	bool GetMirror(PlayerType p) const;

	///<summary>
	/// ブロックが進むべき方向を取得する
	///</summary>
	///<param name="p">どのプレイヤーがいるフィールドか</param>
	Action FieldDirection(PlayerType p) const;

	///<summary>
	/// パズルフィールド内にposがあるか
	///</summary>
	///<param name="p">どのプレイヤーがいるフィールドか</param>
	///<param name="pos>判定する座標</param>
	bool IsInPuzzleField(PlayerType p, Point pos) const;

	///<summary>
	/// プレイヤーフィールド内にposがあるか
	///</summary>
	///<param name="p">どのプレイヤーがいるフィールドか</param>
	///<param name="pos>判定する座標</param>
	bool IsInPlayerField(PlayerType p, Point pos) const;

	///<summary>
	/// ブロックが移動するフィールド内にposがあるか
	///</summary>
	///<param name="p">どのプレイヤーがいるフィールドか</param>
	///<param name="pos>判定する座標</param>
	bool IsInSpaceField(PlayerType p, Point pos) const;

	///<summary>
	/// フィールド内にposがあるか
	///</summary>
	///<param name="p">どのプレイヤーがいるフィールドか</param>
	///<param name="pos>判定する座標</param>
	bool IsInField(PlayerType p, Point pos) const;

	///<summary>
	/// パズルフィールド内にshapeがあるか
	///</summary>
	///<param name="p">どのプレイヤーがいるフィールドか</param>
	///<param name="pos>判定する図形</param>
	template <class Type>
		bool IsInPlayerField(PlayerType p, Type shape) const;

	///<summary>
	/// ブロックが移動する領域にその図形があるか判定する
	///</summary>
	template<class Type>
		bool IsInBlockField(PlayerType p, Type shape) const;

private:
	///<summary>
	/// 画面の大きさのデータ
	///</summary>
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

	///<summary>
	/// プレイヤーのパズル図形
	///</summary>
	std::map<PlayerType, Grid<Rect>> m_puzzles;

	///<summary>
	/// プレイヤーのパズル色
	///</summary>
	std::map<PlayerType, Grid<PieceType>> m_colors;

	///<summary>
	/// 各プレイヤーのフィールドが反転しているか管理する
	///</summary>
	std::map<PlayerType, bool> m_is_mirror;

	EventTimer m_event_timer[2];

private:
		///<summary>
		/// posから繋がっている同じ色のピース数を取得する
		///</summary>
		Array<Point> connectedPieceCount(PlayerType p, Point pos);

		///<summary>
		/// 4つ以上つながっているピースを判定し、消す
		///</summary>
		void clearPieces();

		void updateFieldState();

		void createBlackBlock(PlayerType p, Array<Point> points);
};

template<class Type>
bool Field::IsInPlayerField(PlayerType p, Type shape) const
{
	return Rect(PlayerOrigin(p), Size(PlayerWidth(), Height())).contains(shape);
}

template<class Type>
bool Field::IsInBlockField(PlayerType p, Type shape) const
{
	Point origin;
	if (m_is_mirror.at(p))
	{
		origin = SpaceOrigin(p);
	}
	else
	{
		origin = PlayerOrigin(p);
	}

	return Rect(origin, Size(PlayerWidth() + SpaceWidth(), Height())).contains(shape);
}
