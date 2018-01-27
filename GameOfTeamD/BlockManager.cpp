#include "BlockManager.h"



BlockManager::BlockManager()
{
	m_blocks[PlayerType::One].clear();
	m_blocks[PlayerType::Two].clear();

	m_bb_sw[PlayerType::One] = Stopwatch(true);
	m_bb_sw[PlayerType::Two] = Stopwatch(true);
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

bool BlockManager::Update(Field & field, Player * players, Level level)
{
	for (PlayerType p : {PlayerType::One, PlayerType::Two})
	{
		for (int i = 0; i < m_blocks[p].size(); i++)
		{
			Block & block = m_blocks[p][i];

			// ブロックがフィールド内にあるか判定する
			bool isin_field = false;
			for (auto piece : block.GetAllPieces())
			{
				if (field.IsInBlockField(p, piece))
				{
					isin_field = true;
					break;
				}
			}

			if (isin_field)
			{
				// プレイヤーがブロックを取得
				if (block.Intersects(players[static_cast<int>(p)].Shape))
				{
					// フィールドにブロックを奥詰めで入れる
					bool is_set = field.SetBlock(p, block);

					// 移動してきたブロックは消去する
					m_blocks[p].erase(m_blocks[p].begin() + i);

					// フィールドを更新
					field.ClearPieces(players);

					if (!is_set)
					{
						if (!field.IsClear(p))
						{
							// ブロックがフィールド外に出た場合GameOver
							if (p == PlayerType::One)
							{
								players[static_cast<int>(PlayerType::Two)].SetWinner();
							}
							else
							{
								players[static_cast<int>(PlayerType::One)].SetWinner();
							}

							return true;
						}
					}
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
	if (m_block_sw.ms() >= 750)
	{
		PlayerType p = RandomSelect({ PlayerType::One, PlayerType::Two });
		Block block = RandomSelect({ BlockTemplate::RandomBlock(level) });
		int max_v = field.HeightCount() - block.GetSize().y;
		int height = Random<int>(0, max_v);

		block.SetSpeed(m_blocks_speed);

		CreateBlock(p, height, block, field);
		m_block_sw.restart();
	}
	
	// 黒ブロックを生成する
	for (auto p : { PlayerType::One, PlayerType::Two })
	{
		// 1000msごとに生成する
		if (! field.BlackBlocks[p].empty() && m_bb_sw[p].ms() > 1000)
		{
			auto b_block = field.BlackBlocks[p].front();
			b_block.first.SetSpeed(m_blocks_speed);
			CreateBlock(p, b_block.second, b_block.first, field);

			// 初めの要素を削除
			field.BlackBlocks[p].erase(field.BlackBlocks[p].begin());
			m_bb_sw[p].restart();
		}
	}

	return false;
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

void BlockManager::SetBlocksSpeed(int speed)
{
	if (speed > 0)
	{
		m_blocks_speed = speed;
	}
}
