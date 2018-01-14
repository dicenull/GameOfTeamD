#include "Field.h"
#include <Siv3D.hpp>

Field::Field(int32 field_height, int32 puzzle_width, int32 player_width, int32 zk_size, std::map<PlayerType, bool> is_mirrors)
{
	m_field_height = field_height;
	m_puzzle_width = puzzle_width;
	m_player_width = player_width;
	m_zk = zk_size;

	// パズルのフィールドを初期化
	m_p1_puzzles.resize(Size(puzzle_width, field_height));
	m_p2_puzzles.resize(Size(puzzle_width, field_height));

	m_is_mirror[PlayerType::One] = is_mirrors[PlayerType::One];
	m_is_mirror[PlayerType::Two] = is_mirrors[PlayerType::Two];

}

Field::Field(const Field & other)
	: Field::Field(other.m_player_width, other.m_puzzle_width, other.m_player_width, other.m_zk,
		other.m_is_mirror)
{ }

void Field::operator=(const Field & other)
{
	m_player_width = other.m_player_width;
	m_puzzle_width = other.m_puzzle_width;
	m_field_height = other.m_field_height;
	m_p1_puzzles = other.m_p1_puzzles;
	m_p2_puzzles = other.m_p2_puzzles;
	m_zk = other.m_zk;
}

void Field::Update()
{
	m_window = Window::Size();
}

void Field::SetBlock(PlayerType p, Block block)
{
	Grid<Rect> puzzles = ((p == PlayerType::One) ? m_p1_puzzles : m_p2_puzzles);

	// ブロックを奥詰めで追加する
	Println(L"Set Block");
}

void Field::Draw() const
{
	// 枠線を描画
	Color f_color = Palette::Darkgreen;
	Color p_color = Palette::Hotpink;
	Color l_color = Palette::Lightgrey;
	Size size = Size(m_zk, m_zk);

	for (auto p : { PlayerType::One, PlayerType::Two })
	{

		// スコア表示部とフィールドの境界線
		Line(LeftBorder(p), RightBorder(p)).draw(3.0, f_color);
		
		// プレイヤーフィールドの境界線
		Line(PlayerTopBorder(p), PlayerTopBorder(p) + Point(0, Height())).draw(2.0, p_color);

		// パズルが移動してくるフィールドの補助線
		for (int h = 1; h < m_field_height; h++)
		{
			Line(SpaceOrigin(p) + Point(0, h * m_zk), SpaceOrigin(p) + Point(SpaceWidth(), h * m_zk)).draw(1, l_color);
		}
	}

	// パズルフィールドを描画
	for (int w = 0; w < m_puzzle_width; w++)
	{
		for (int h = 0; h < m_field_height; h++)
		{
			auto p1_puzzle = m_p1_puzzles[h][w];
			auto p2_puzzle = m_p2_puzzles[h][w];
			Point pos = Point(m_zk * w, m_zk * h);

			p1_puzzle.set(PuzzleOrigin(PlayerType::One) + pos, size);
			p2_puzzle.set(PuzzleOrigin(PlayerType::Two) + pos, size);

			p1_puzzle.drawFrame();
			p2_puzzle.drawFrame();
		}
	}
}

Field::~Field()
{
}

int32 Field::Height() const
{
	return m_field_height * m_zk;
}

int32 Field::Width() const
{
	return (m_puzzle_width + m_player_width) * m_zk;
}

int32 Field::PuzzleWidth() const
{
	return m_puzzle_width * m_zk;
}

int32 Field::PlayerWidth() const
{
	return m_player_width * m_zk;
}

int32 Field::SpaceWidth() const
{
	return m_window.x - Width();
}

int32 Field::Zk() const
{
	return m_zk;
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
