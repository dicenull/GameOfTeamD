#pragma once
#include "Field.h"
#include "PlayerLib.h"
#include "Character.h"
#include "Action.h"

class Field;

class Player :
	public Character<Circle>
{
public:
	///<summary>
	/// コンストラクタ
	///</summary>
	///<param name="p">番号</param>
	///<param name="pos">初期座標</param>
	Player(PlayerType p, Point pos);

	///<summary>
	/// デストラクタ
	///</summary>
	virtual ~Player();

public:
	///<summary>
	///プレイヤーの場所を取得する
	///</summary>
	Point Pos();

	///<summary>
	/// プレイヤーの場所を設定する
	///</summary>
	void SetPos(Point pos);

	///<summary>
	/// プレイヤーを動かす
	///</summary>
	///<param name="action">動作させる行動の向き</param>
	///<param name="field">プレイヤーのいるフィールド</param>
	void Move(Action action, const Field & field);

	///<summary>
	///プレイヤーの得点
	///</summary>
	int Score();

	///<summary>
	/// プレイヤー番号を取得する
	///</summary>
	PlayerType GetPlayerType();

private:
	///<summary>
	/// スコアのデータ
	///</summary>
	int m_score;

	///<summary>
	/// 番号のデータ
	///</summary>
	PlayerType m_player_type;
};

