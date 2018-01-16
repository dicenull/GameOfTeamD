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

void Field::Update()
{
	m_window = Window::Size();
}

void Field::SetBlock(PlayerType p, Block block)
{
	auto & colors = m_colors.at(p);
	int b_origin = block.GetHeight();

	// ブロックを奥詰めで追加する
	for (int i = 0; i < block.MaxLength(); i++)
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

		if (m_puzzle_width - count >= block.MaxLength())
		{
			auto pieces = block.GetPieces(i);
			for (int j = 0; j < pieces.size(); j++)
			{
				colors[i + b_origin][j + count] = pieces[j];
			}
		}
		else
		{
			// GameOver
			// とりあえずログ表示
			if (p == PlayerType::One)
			{
				Println(L"Winner : Player 2");
			}
			else
			{
				Println(L"Winner : Player 1");
			}
		}
	}
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

				if (piece_type != PieceType::None)
				{
					puzzle.draw(Piece::ColorParse(piece_type));
				}
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
