#include "Field.h"
#include <Siv3D.hpp>

Field::Field(int32 field_height, int32 puzzle_width, int32 player_width, std::map<PlayerType, bool> is_mirrors)
{
	m_field_height = field_height;
	m_puzzle_width = puzzle_width;
	m_player_width = player_width;

	// パズルのフィールドを初期化
	for (auto p : { PlayerType::One, PlayerType::Two })
	{
		m_puzzles[p].resize(Size(puzzle_width, field_height));
		m_is_mirror[p] = is_mirrors[p];
		m_colors[p].resize(Size(puzzle_width, field_height), PieceType::None);
	}

	for (auto & et : m_event_timer)
	{
		et.addEvent(L"ClearPiece", 200ms);
		et.pause();
	}
}

Field::Field(const Field & other)
	: Field::Field(other.m_player_width, other.m_puzzle_width, other.m_player_width,
		other.m_is_mirror)
{ }

void Field::operator=(const Field & other)
{
	m_player_width = other.m_player_width;
	m_puzzle_width = other.m_puzzle_width;
	m_field_height = other.m_field_height;
	for (auto p : { PlayerType::One, PlayerType::Two })
	{
		m_puzzles[p] = other.m_puzzles.at(p);
		m_colors[p] = other.m_colors.at(p);
	}
}

void Field::Update(Player * players)
{
	m_window = Window::Size();

	// ピースのつながりを判定
	clearPieces(players);

	// ピースが消えていたらその分マスを詰める
	for (auto & et : m_event_timer)
	{
		if (et.onTriggered(L"ClearPiece"))
		{
			updateFieldState();
			et.reset();
			et.pause();
		}

		et.update();
	}
	
}

bool Field::SetBlock(PlayerType p, Block block)
{
	auto & colors = m_colors.at(p);
	int b_origin = block.GetHeight();

	// ブロックを奥詰めで追加する
	for (int i = 0; i < block.GetSize().y; i++)
	{
		// ブロックがフィールド内にあるか
		// i列目のパズルの幅を計算する
		int count = 0;
		for (int j = 0; j < m_puzzle_width; j++)
		{
			if (colors[i + b_origin][j] == PieceType::None)
			{
				break;
			}
			count++;
		}

		if (m_puzzle_width - count >= block.GetSize().x)
		{
			auto pieces = block.GetPieces(i);
			
			if (m_is_mirror.at(p))
			{
				std::reverse(pieces.begin(), pieces.end());
			}

			for (int j = 0; j < pieces.size(); j++)
			{
				colors[i + b_origin][j + count] = pieces[j];
			}
		}
		else
		{
			return false;
		}
	}

	return true;
}

void Field::Draw() const
{
	// 枠線を描画
	Color f_color = Palette::Darkgreen;
	Color p_color = Palette::Hotpink;
	Color l_color = Palette::Lightgrey;
	Size size = Size(MyGame::Zk, MyGame::Zk);

	// パズルフィールドを描画
	for (int w = 0; w < m_puzzle_width; w++)
	{
		for (int h = 0; h < m_field_height; h++)
		{
			Point pos = Point(MyGame::Zk * w, MyGame::Zk * h);
			
			for (auto p : { PlayerType::One, PlayerType::Two })
			{
				int tmp = (m_is_mirror.at(p) ? m_puzzle_width - 1 - w : w);
				auto puzzle = m_puzzles.at(p)[h][tmp];
				auto piece_type = m_colors.at(p)[h][tmp];
				
				puzzle.set(PuzzleOrigin(p) + pos, size);

				puzzle.draw(Piece::ColorParse(piece_type));
				puzzle.drawFrame();
			}
		}
	}

	for (auto p : { PlayerType::One, PlayerType::Two })
	{

		// スコア表示部とフィールドの境界線
		Line(LeftBorder(p), RightBorder(p)).draw(3.0, f_color);
		
		// プレイヤーフィールドの境界線
		Line(PlayerTopBorder(p), PlayerTopBorder(p) + Point(0, Height())).draw(2.0, p_color);

		// パズルが移動してくるフィールドの補助線
		for (int h = 1; h < m_field_height; h++)
		{
			Line(SpaceOrigin(p) + Point(0, h * MyGame::Zk), SpaceOrigin(p) + Point(SpaceWidth(), h * MyGame::Zk)).draw(1, l_color);
		}
	}

}

Field::~Field()
{
}

int32 Field::Height() const
{
	return m_field_height * MyGame::Zk;
}

int32 Field::HeightCount() const
{
	return m_field_height;
}

int32 Field::Width() const
{
	return (m_puzzle_width + m_player_width) * MyGame::Zk;
}

int32 Field::PuzzleWidth() const
{
	return m_puzzle_width * MyGame::Zk;
}

int32 Field::PlayerWidth() const
{
	return m_player_width * MyGame::Zk;
}

int32 Field::SpaceWidth() const
{
	return m_window.x - Width();
}


///<summary>
///パズルフィールドの左上の座標
///</summary>
Point Field::PuzzleOrigin(PlayerType p) const
{
	switch (p)
	{
	case PlayerType::One:
		if (m_is_mirror.at(p))
		{
			return Point(m_window.x - PuzzleWidth(), 0);
		}
		else
		{
			return Point(0, 0);
		}
	case PlayerType::Two:
		if (m_is_mirror.at(p))
		{
			return Point(m_window.x - PuzzleWidth(), m_window.y - Height());
		}
		else
		{
			return Point(0, m_window.y - Height());
		}
	default:
		return Point();
	}
}

///<summary>
///プレイヤーフィールドの左上の座標
///</summary>
Point Field::PlayerOrigin(PlayerType p) const
{
	switch (p)
	{
	case PlayerType::One:
		if (m_is_mirror.at(p))
		{
			return Point(m_window.x - Width(), 0);
		}
		else
		{
			return Point(PuzzleWidth(), 0);
		}
	case PlayerType::Two:
		if (m_is_mirror.at(p))
		{
			return Point(m_window.x - Width(), m_window.y - Height());
		}
		else
		{
			return Point(PuzzleWidth(), m_window.y - Height());
		}
	default:
		return Point();
	}
}

///<summary>
///宇宙フィールドの左上の座標
///</summary>
Point Field::SpaceOrigin(PlayerType p) const
{
	switch (p)
	{
	case PlayerType::One:
		if (m_is_mirror.at(p))
		{
			return Point(0, 0);
		}
		else
		{
			return Point(Width(), 0);
		}
	case PlayerType::Two:
		if (m_is_mirror.at(p))
		{
			return Point(0, m_window.y - Height());
		}
		else
		{
			return Point(Width(), m_window.y - Height());
		}
	default:
		return Point();
	}
}

///<summary>
///パズルフィールドの右下の座標
///</summary>
Point Field::PuzzleEndPos(PlayerType p) const
{
	switch (p)
	{
	case PlayerType::One:
		if (m_is_mirror.at(p))
		{
			return Point(m_window.x, Height());
		}
		else
		{
			return Point(PuzzleWidth(), Height());
		}
	case PlayerType::Two:
		if (m_is_mirror.at(p))
		{
			return Point(m_window.x, m_window.y);
		}
		else
		{
			return Point(PuzzleWidth(), m_window.y);
		}
	default:
		return Point();
	}
}

///<summary>
///プレイヤーフィールドの右下の座標
///</summary>
Point Field::PlayerEndPos(PlayerType p) const
{
	switch (p)
	{
	case PlayerType::One:
		if (m_is_mirror.at(p))
		{
			return Point(m_window.x - PuzzleWidth(), Height());
		}
		else
		{
			return Point(Width(), Height());
		}
	case PlayerType::Two:
		if (m_is_mirror.at(p))
		{
			return Point(m_window.x - PuzzleWidth(), m_window.y);
		}
		else
		{
			return Point(Width(), m_window.y);
		}
	default:
		return Point();
	}
}

///<summary>
///宇宙フィールドの右下の座標
///</summary>
Point Field::SpaceEndPos(PlayerType p) const
{
	switch (p)
	{
	case PlayerType::One:
		if (m_is_mirror.at(p))
		{
			return Point(m_window.x - Width(), Height());
		}
		else
		{
			return Point(m_window.x, Height());
		}
	case PlayerType::Two:
		if (m_is_mirror.at(p))
		{
			return Point(m_window.x - Width(), m_window.y);
		}
		else
		{
			return Point(m_window.x, m_window.y);
		}
	default:
		return Point();
	}
}

Point Field::LeftBorder(PlayerType p) const
{
	switch (p)
	{
	case PlayerType::One:
		return Point(0, Height());
	case PlayerType::Two:
		return Point(0, m_window.y - Height());
	default:
		return Point();
	}
}

Point Field::RightBorder(PlayerType p) const
{
	switch (p)
	{
	case PlayerType::One:
		return Point(m_window.x, Height());
	case PlayerType::Two:
		return Point(m_window.x, m_window.y - Height());
	default:
		return Point();
	}
}

Point Field::PlayerTopBorder(PlayerType p) const
{
	switch (p)
	{
	case PlayerType::One:
		if (m_is_mirror.at(p))
		{
			return Point(m_window.x - Width(), 0);
		}
		else
		{
			return Point(Width(), 0 );
		}
	case PlayerType::Two:
		if (m_is_mirror.at(p))
		{
			return Point(m_window.x - Width(), m_window.y - Height());
		}
		else
		{
			return Point(Width(), m_window.y - Height());
		}
	}
}

Point Field::PlayerCenter(PlayerType p) const
{
	return PlayerOrigin(p) + Point(PlayerWidth() / 2, Height() / 2);
}

Point Field::BlockStartPos(PlayerType p) const
{
	if (m_is_mirror.at(p))
	{
		return SpaceOrigin(p);
	}
	else
	{
		return SpaceEndPos(p) - Point(0, Height());
	}
}


void Field::SetMirror(PlayerType p, bool is_mirror)
{
	m_is_mirror[p] = is_mirror;
}

bool Field::GetMirror(PlayerType p) const
{
	return m_is_mirror.at(p);
}

Action Field::FieldDirection(PlayerType p) const
{
	if (m_is_mirror.at(p))
	{
		return Action::Right;
	}
	else
	{
		return Action::Left;
	}
}

bool Field::IsInPuzzleField(PlayerType p, Point pos) const
{
	return (PuzzleOrigin(p).x <= pos.x && pos.x <= PuzzleEndPos(p).x)
		&& (PuzzleOrigin(p).y <= pos.y && pos.y <= PuzzleEndPos(p).y);
}

bool Field::IsInPlayerField(PlayerType p, Point pos) const 
{
	return (PlayerOrigin(p).x <= pos.x && pos.x <= PlayerEndPos(p).x)
		&& (PlayerOrigin(p).y <= pos.y && pos.y <= PlayerEndPos(p).y);
}

bool Field::IsInSpaceField(PlayerType p, Point pos)const
{
	return (SpaceOrigin(p).x <= pos.x && pos.x <= SpaceEndPos(p).x)
		&& (SpaceOrigin(p).y <= pos.y && pos.y <= SpaceEndPos(p).y);
}

bool Field::IsInField(PlayerType p, Point pos) const
{
	return IsInPuzzleField(p, pos) || IsInPlayerField(p, pos) || IsInSpaceField(p, pos);
}

Array<Point> Field::connectedPieceCount(PlayerType p, Point pos)
{
	Array<Point> points;
	points.push_back(pos);
	auto & colors = m_colors[p];
	auto color = colors[pos.y][pos.x];

	m_is_not_check[pos.y][pos.x] = false;

	colors[pos.y][pos.x] = PieceType::None;

	if (pos.x + 1 < m_puzzle_width && colors[pos.y][pos.x + 1] == color && m_is_not_check[pos.y][pos.x + 1])
	{
		for (auto _p : connectedPieceCount(p, Point(pos.x + 1, pos.y)))
		{
			points.push_back(_p);
		}
	}
	if (pos.y + 1 < m_field_height && colors[pos.y + 1][pos.x] == color && m_is_not_check[pos.y + 1][pos.x])
	{
		for (auto _p : connectedPieceCount(p, Point(pos.x, pos.y + 1)))
		{
			points.push_back(_p);
		}
	}
	if (pos.x - 1 >= 0 && colors[pos.y][pos.x - 1] == color && m_is_not_check[pos.y][pos.x - 1])
	{
		for (auto _p : connectedPieceCount(p, Point(pos.x - 1, pos.y)))
		{
			points.push_back(_p);
		}
	}
	if (pos.y - 1 >= 0 && colors[pos.y - 1][pos.x] == color && m_is_not_check[pos.y - 1][pos.x])
	{
		for (auto _p : connectedPieceCount(p, Point(pos.x, pos.y - 1)))
		{
			points.push_back(_p);
		}
	}

	colors[pos.y][pos.x] = color;

	return points;
}

void Field::clearPieces(Player * players)
{
	bool is_clear[2] = { false, false };
	for (auto p : { PlayerType::One, PlayerType::Two })
	{
		auto & colors = m_colors.at(p);
		m_is_not_check = { Size(m_puzzle_width, m_field_height), true };
		for (int i = 0; i < m_puzzle_width; i++)
		{
			for (int j = 0; j < m_field_height; j++)
			{
				if (colors[j][i] != PieceType::None && colors[j][i] != PieceType::Black)
				{
					auto points = connectedPieceCount(p, Point(i, j));

					// 四つ以上つながったピースを消す
					if (points.size() >= 4)
					{
						// ピースを消したポイントを加算
						players[static_cast<int>(p)].AddScore();

						for (auto pos : points)
						{
							colors[pos.y][pos.x] = PieceType::None;
						}

						// 相手に送る黒ブロックを生成する
						createBlackBlock(p, points);

						is_clear[static_cast<int>(p)] = true;
					}
				}
			}
		}
	}

	// 空いた隙間を時間をおいて詰める
	for (int i = 0; i < 2; i++)
	{
		if (is_clear[i])
		{
			m_event_timer[i].start();
		}
	}
}

void Field::updateFieldState()
{
	for (auto p : { PlayerType::One, PlayerType::Two })
	{
		auto & colors = m_colors.at(p);
		for (int h = 0; h < m_field_height; h++)
		{
			for (int w = 0; w < m_puzzle_width; w++)
			{
				if (colors[h][w] == PieceType::None)
				{
					// 1マス列を詰める
					bool is_color = false;
					for (int i = w + 1; i < m_puzzle_width; i++)
					{
						colors[h][i - 1] = colors[h][i];

						if (colors[h][i] != PieceType::None)
						{
							is_color = true;
						}
					}
					colors[h][m_puzzle_width - 1] = PieceType::None;

					// 奥に色があったら同じ場所から再走査
					if (is_color)
					{
						w--;
					}
				}
			}
		}
	}
}

void Field::createBlackBlock(PlayerType p, Array<Point> points)
{
	Point min{ m_puzzle_width - 1, m_field_height - 1 }, max{ 0,0 };

	for (auto p : points)
	{
		if (p.x < min.x)
		{
			min.x = p.x;
		}

		if (p.x > max.x)
		{
			max.x = p.x;
		}

		if (p.y < min.y)
		{
			min.y = p.y;
		}

		if (p.y > max.y)
		{
			max.y = p.y;
		}
	}

	int w = max.x - min.x + 1, h = max.y - min.y + 1;
	Grid<PieceType> pieces{ Size(w, h), PieceType::None };

	for (auto p : points)
	{
		pieces[p.y - min.y][p.x - min.x] = PieceType::Black;
	}

	// 相手のプレイヤーのリストに黒ブロックを追加する
	if (p == PlayerType::One)
	{
		p = PlayerType::Two;
	}
	else
	{
		p = PlayerType::One;
	}

	BlackBlocks[p].push_back({ Block{pieces}, min.y });
}
