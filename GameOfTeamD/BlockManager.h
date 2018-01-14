#pragma once
#include <Siv3D.hpp>
#include <algorithm>
#include "Block.h"
#include "PlayerLib.h"
#include "Field.h"

class BlockManager
{
public:
	BlockManager(int32 zk);
	~BlockManager();

public:
	void CreateBlock(PlayerType p, int height, Block block, const Field & field);
	void Update(const Field & field);
	void DrawBlocks() const;

private:
	std::map<PlayerType, Array<Block>> m_blocks;
	int32 m_zk;
	int32 m_window_width;
};

