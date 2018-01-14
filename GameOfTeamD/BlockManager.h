#pragma once
#include <Siv3D.hpp>
#include <algorithm>
#include "Block.h"
#include "PlayerLib.h"
#include "Field.h"

class BlockManager
{
public:
	///<summary>
	/// コンストラクタ
	///</summary>
	///<param name="zk">一マス当たりの大きさ</param>
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
	void Update(Field & field, const Player * players);

	///<summary>
	/// 管理しているブロックを描画する
	///</summary>
	void DrawBlocks(const Field & field) const;

private:
	///<summary>
	/// プレイヤーごとのブロック
	///</summary>
	std::map<PlayerType, Array<Block>> m_blocks;
};

