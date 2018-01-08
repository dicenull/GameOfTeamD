#include "BlockManager.h"



BlockManager::BlockManager(int32 zk)
{
	m_p1_blocks.clear();
	m_p2_blocks.clear();
	m_zk = zk;
	m_window_width = Window::Width();
}

BlockManager::~BlockManager()
{
}

void BlockManager::CreateBlock(Players p, int height, Block block)
{
	switch (p)
	{
	case Players::One:
		block.SetPos(Point(m_window_width - m_zk, height * m_zk));
		m_p1_blocks.push_back(block);
		break;
	case Players::Two:
		block.SetPos(Point(m_zk, height * m_zk));
		m_p2_blocks.push_back(block);
		break;
	}
}

void BlockManager::Update()
{
	for (Block& block : m_p1_blocks)
	{
		block.Move(One);
	}

	for (Block& block : m_p2_blocks)
	{
		block.Move(Two);
	}
}

void BlockManager::DrawBlocks() const
{
	for (auto block : m_p1_blocks)
	{
		block.Draw(m_zk);
	}

	for (auto block : m_p2_blocks)
	{
		block.Draw(m_zk);
	}
}
