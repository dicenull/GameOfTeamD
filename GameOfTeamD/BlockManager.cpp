#include "BlockManager.h"



BlockManager::BlockManager(int32 zk)
{
	m_blocks[PlayerType::One].clear();
	m_blocks[PlayerType::Two].clear();
	m_zk = zk;
	m_window_width = Window::Width();
}

BlockManager::~BlockManager()
{
}

void BlockManager::CreateBlock(PlayerType p, int height, Block block, const Field & field)
{
	block.SetPos(field.BlockStartPos(p) + Point(-m_zk * Block::MaxLength(), height * m_zk));
	m_blocks[p].push_back(block);
}

void BlockManager::Update(const Field & field)
{
	for (PlayerType p : {PlayerType::One, PlayerType::Two})
	{
		for (int i = 0; i < m_blocks[p].size(); i++)
		{
			Block & block = m_blocks[p][i];

			bool isin_field = true;

			for (auto piece : block.GetPieces(field.Zk()))
			{
				if (!field.IsInBlockField(p, piece))
				{
					isin_field = false;
					break;
				}
			}

			if (isin_field)
			{
				block.Move(field.FieldDirection(p));
			}
			else
			{
				m_blocks[p].erase(m_blocks[p].begin() + i);
			}
		}
	}
}

void BlockManager::DrawBlocks() const
{
	for (auto block : m_blocks.at(PlayerType::One))
	{
		block.Draw(m_zk);
	}

	for (auto block : m_blocks.at(PlayerType::Two))
	{
		block.Draw(m_zk);
	}
}
