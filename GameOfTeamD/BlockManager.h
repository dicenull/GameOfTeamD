#pragma once
#include <Siv3D.hpp>
#include <algorithm>
#include "Block.h"
#include "PlayerLib.h"
#include "Field.h"
#include "BlockTemplate.h"

class BlockManager
{
public:
	///<summary>
	/// コンストラクタ
	///</summary>
	BlockManager();

	///<summary>
	/// デストラクタ
	///</summary>
	~BlockManager();

public:
	///<summary>
	/// ブロックを生成し、管理する
	///</summary>
	///<param name="p">どのフィールドにブロックを生成するか</param>
	///<param name="height">ブロックを生成する高さ[zk]</param>
	///<param name="block">生成するブロック情報</param>
	///<param name="field">フィールド情報</param>
	void CreateBlock(PlayerType p, int height, Block block, const Field & field);

	///<summary>
	/// 管理しているブロックの情報を更新する
	///</summary>
	///<returns>ゲーム終了状態か</returns>
	bool Update(Field & field, Player * players, Level level);

	///<summary>
	/// 管理しているブロックを描画する
	///</summary>
	void DrawBlocks() const;

	/// <summary>
	/// 通常ブロックのスピード
	/// </summary>
	/// <param name="speed">設定するスピード</param>
	void SetBlocksSpeed(int speed);

private:
	///<summary>
	/// プレイヤーごとのブロック
	///</summary>
	std::map<PlayerType, Array<Block>> m_blocks;

	Stopwatch m_block_sw{ true };
	std::map<PlayerType, Stopwatch> m_bb_sw;

	int m_blocks_speed = 1;
};

