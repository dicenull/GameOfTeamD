#include "BlockManager.h"



BlockManager::BlockManager()
{
	m_blocks[PlayerType::One].clear();
	m_blocks[PlayerType::Two].clear();
}

BlockManager::~BlockManager()
{
}

void BlockManager::CreateBlock(PlayerType p, int height, Block block, const Field & field)
{
	// ブロックがフィールドに入るように作成位置をずらす
	int x = ((field.GetMirror(p)) ? 0 : -MyGame::Zk * block.GetSize().x);

	block.SetPos(height, field.BlockStartPos(p) + Point(x, height * MyGame::Zk));
	m_blocks[p].push_back(block);
}

void BlockManager::Update(Field & field, const Player * players)
{
	for (PlayerType p : {PlayerType::One, PlayerType::Two})
	{
		for (int i = 0; i < m_blocks[p].size(); i++)
		{
			Block & block = m_blocks[p][i];

			// ブロックがフィールド内にあるか判定する
			bool isin_field = true;
			for (auto piece : block.GetAllPieces())
			{
				if (!field.IsInBlockField(p, piece))
				{
					isin_field = false;
					break;
				}
			}

			if (isin_field)
			{
				// プレイヤーがブロックを取得
				if (block.Intersects(players[static_cast<int>(p)].Shape))
				{
					// フィールドにブロックを奥詰めで入れる
					field.SetBlock(p, block);
					// 移動してきたブロックは消去する
					m_blocks[p].erase(m_blocks[p].begin() + i);
				}
				else
				{
					// プレイヤーが取得せず、フィールド内にあるブロックを動かす
					block.Move(field.FieldDirection(p));
				}
			}
			else
			{
				// 範囲外のブロックを消去する
				m_blocks[p].erase(m_blocks[p].begin() + i);
			}
		}
	}

	// 新しいブロックを生成する
	if (m_sw.ms() >= 750)
	{
		PlayerType p = RandomSelect({ PlayerType::One, PlayerType::Two });
		Block block = RandomSelect({ BlockTemplate::RandomBlock(MyGame::GameLevel::Easy) });
		int max_v = field.HeightCount() - block.GetSize().y;
		int height = Random<int>(0, max_v);

		CreateBlock(p, height, block, field);
		m_sw.restart();
	}
	
	// 黒ブロックを生成する
	for (auto p : { PlayerType::One, PlayerType::Two })
	{
		for (auto b_block : field.BlackBlocks[p])
		{
			CreateBlock(p, b_block.second, b_block.first, field);
		}

		field.BlackBlocks[p].clear();
	}
}

void BlockManager::DrawBlocks() const
{
	for (auto block : m_blocks.at(PlayerType::One))
	{
		block.Draw(Point::Zero);
	}

	for (auto block : m_blocks.at(PlayerType::Two))
	{
		block.Draw(Point::Zero);
	}
}
