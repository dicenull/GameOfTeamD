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

void BlockManager::CreateBlock(Players p, int height, Block block, const Field & field)
{
	switch (p)
	{
	case Players::One:
		block.SetPos(Point(m_window_width - m_zk * Block::Length(), height * m_zk));
		m_p1_blocks.push_back(block);
		break;
	case Players::Two:
		block.SetPos(Point(m_zk * Block::Length(), height * m_zk + field.Height()));
		m_p2_blocks.push_back(block);
		break;
	}
}

void BlockManager::Update(const Field & field)
{
	for (int i = 0;i < m_p1_blocks.size();i++)
	{
		Block& block = m_p1_blocks[i];

		if (field.IsInField(Players::One, block.GetBottomLeft()))
		{
			block.Move(Players::One);
		}
		else
		{
			m_p1_blocks.erase(m_p1_blocks.begin() + i);
		}
	}

	for (int i = 0; i < m_p2_blocks.size(); i++)
	{
		Block& block = m_p2_blocks[i];

		if (field.IsInField(Players::Two, block.GetBottomLeft()))
		{
			block.Move(Players::Two);
		}
		else
		{
			m_p2_blocks.erase(m_p2_blocks.begin() + i);
		}
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
