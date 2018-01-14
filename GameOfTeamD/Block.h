#pragma once

#include <Siv3D.hpp>
#include "Player.h"
#include "Action.h"

class Block
{
public:
	///<summary>
	/// デフォルトコンストラクタ
	///</summary>
	Block();

	///<summary>
	/// ピースを元にブロックを作成する
	///</summary>
	///<param name="pieces">Length*Lengthの二次元配列のピース</param>
	Block(Grid<Color> pieces);

	///<summary>
	/// デストラクタ
	///</summary>
	~Block();

	///<summary>
	/// ブロックの一辺の長さの最大値
	///</summary>
	static int MaxLength();

public:
	///<summary>
	/// ブロックの色を取得する
	///</summary>
	Grid<Color> GetColor() const;

	///<summary>
	/// ブロックを右に90度回転する
	///</summary>
	void TurnRight();

	///<summary>
	/// ブロックを左に90度回転する
	///</summary>
	void TurnLeft();

	///<summary>
	/// ブロックの左上の座標を設定する
	///</summary>
	void SetPos(const Point &pos);

	///<summary>
	/// ブロックの左下の座標を取得する
	///</summary>
	Point GetBottomLeft();

	///<summary>
	/// ブロックをフィールドに応じて動かす
	///</summary>
	///<param name="p">動かす方向[Action::Left, Action::Right]のみ</param>
	void Move(Action action);

	///<summary>
	/// zkを指定してブロックを描画する
	///</summary>
	///<param name="zk">一マス当たりの大きさ</param>
	void Draw(int32 zk) const;

private:
	///<summary>
	/// ブロックの一辺の最大値
	///</summary>
	static const int length = 2;

	///<summary>
	/// ブロックの色データ
	///</summary>
	Grid<Color> m_pieces{ length, length };

	///<summary>
	/// ブロックの左上の座標
	///</summary>
	Point m_pos;
};
