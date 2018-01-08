#pragma once
#include <Siv3D.hpp>
#include "Block.h"
#include "PlayerLib.h"
#include "Field.h"

class BlockManager
{
public:
	BlockManager(int32 zk);
	~BlockManager();

public:
	void CreateBlock(Players p, int height, Block block);
	void Update();
	void DrawBlocks() const;

private:
	Array<Block> m_p1_blocks;
	Array<Block> m_p2_blocks;
	int32 m_zk;
	int32 m_window_width;
};

