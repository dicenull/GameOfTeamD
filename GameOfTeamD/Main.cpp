
# include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Field.h"
#include "Player.h"
#include "Block.h"
#include "BlockManager.h"
#include "Action.h"

struct CommonData
{
	Field field{};
	Stopwatch timer;
	Font main_font{ 25 };
	Font small_font{ 15 };
	// プレイヤーフィールドの中心にプレイヤーの位置を設定する
	Player players[2] = 
	{ 
		{PlayerType::One, field.PlayerCenter(PlayerType::One)}, 
		{PlayerType::Two, field.PlayerCenter(PlayerType::Two)} 
	};

	BlockManager b_manager{};
	Level level = Level::Easy;
};

using MyApp = SceneManager<String, CommonData>;

class Title : public MyApp::Scene
{
public:
	void init() override
	{
		Size size = m_data->main_font(L" Normal ").region().size;
		menu_boxes[L"Level"] = { Window::Center() + Point(-size.x / 2, size.y * 2), size, 10 };
		menu_boxes[L"Start"] = { Window::Center() + Point(-size.x / 2, 0), size, 10 };
	}

	void update() override 
	{
		if (menu_boxes[L"Level"].leftClicked)
		{
			m_data->level = static_cast<Level>((static_cast<int>(m_data->level) + 1) % levels.size());
		}

		if (menu_boxes[L"Start"].leftClicked || Input::KeyEnter.clicked)
		{
			changeScene(L"Game");
		}
	}

	void draw() const override
	{
		m_data->main_font(L"お宅の庭敷き詰めます").drawCenter(Window::Center() - Point(0, Window::Center().y / 3));
		for (auto menu : menu_boxes)
		{
			menu.second.draw();
		}
		m_data->main_font(levels[static_cast<int>(m_data->level)]).drawAt(menu_boxes.at(L"Level").center, Palette::Black);
		m_data->main_font(L"Start").drawAt(menu_boxes.at(L"Start").center, Palette::Blue);
	}

private:
	Array<String> levels = { L"Easy", L"Normal", L"Hard" };
	std::map<String, RoundRect> menu_boxes;
};

class Game : public MyApp::Scene
{
public:
	void init() override
	{
		m_data->timer.restart();

		m_data->field = Field();
		m_data->b_manager = BlockManager();
		m_data->players[0] = { PlayerType::One, m_data->field.PlayerCenter(PlayerType::One) };
		m_data->players[1] = { PlayerType::Two, m_data->field.PlayerCenter(PlayerType::Two) };

		// プレイヤーの大きさを設定
		for (auto& p : m_data->players)
		{
			p.Shape.r = MyGame::Zk / 2 - 2;
		}
	}

	void update() override
	{
		// フィールドの向きを反転し、プレイヤーの位置を戻す
		if (Input::KeyF.clicked)
		{
			m_data->field.SetMirror(PlayerType::One, true);
			m_data->field.SetMirror(PlayerType::Two, false);

			m_data->players[0].SetPos(m_data->field.PlayerCenter(PlayerType::One));
			m_data->players[1].SetPos(m_data->field.PlayerCenter(PlayerType::Two));
		}
		if (Input::KeyR.clicked)
		{
			m_data->field.SetMirror(PlayerType::One, false);
			m_data->field.SetMirror(PlayerType::Two, true);

			m_data->players[0].SetPos(m_data->field.PlayerCenter(PlayerType::One));
			m_data->players[1].SetPos(m_data->field.PlayerCenter(PlayerType::Two));
		}

		// プレイヤー1の操作
		if (Input::KeyRight.pressed || Gamepad(0).button(4).pressed) m_data->players[0].Move(Action::Right, m_data->field);
		if (Input::KeyUp.pressed || Gamepad(0).button(3).pressed) m_data->players[0].Move(Action::Up, m_data->field);
		if (Input::KeyLeft.pressed || Gamepad(0).button(1).pressed) m_data->players[0].Move(Action::Left, m_data->field);
		if (Input::KeyDown.pressed || Gamepad(0).button(2).pressed) m_data->players[0].Move(Action::Down, m_data->field);

		// プレイヤー2の操作
		if (Input::KeyD.pressed) m_data->players[1].Move(Action::Right, m_data->field);
		if (Input::KeyW.pressed) m_data->players[1].Move(Action::Up, m_data->field);
		if (Input::KeyA.pressed) m_data->players[1].Move(Action::Left, m_data->field);
		if (Input::KeyS.pressed) m_data->players[1].Move(Action::Down, m_data->field);

		// 一定時間ごとにブロックの速度を早くする
		m_data->b_manager.SetBlocksSpeed(m_data->timer.s() / m_speed_up_count + 1);

		// ブロックを動かす
		if (m_data->b_manager.Update(m_data->field, m_data->players, m_data->level))
		{
			m_data->timer.pause();
			changeScene(L"Result");
		}
		m_data->field.Update(m_data->players);
	}

	void draw() const override
	{
		// タイムを描画
		m_data->main_font(L"Time : ", m_data->timer.s(), L"[s]").drawCenter(Window::Center());
		// プレイヤー1のスコアを描画
		m_data->main_font(m_data->players[0].Score()).drawCenter(Point(Window::Center().x / 5.0, Window::Center().y));
		// プレイヤー2のスコアを描画
		m_data->main_font(m_data->players[1].Score()).drawCenter(Point(Window::Size().x - Window::Size().x / 5.0, Window::Center().y));

		m_data->b_manager.DrawBlocks();

		// プレイヤーを描画
		m_data->players[0].Shape.draw();
		m_data->players[1].Shape.draw();

		m_data->field.Draw();
	}

private:
	int m_speed_up_count = 60;
};

class Result : public MyApp::Scene
{
public :
	void update() override
	{
		if (Input::KeyEnter.clicked)
		{
			changeScene(L"Title");
		}
	}

	void draw() const override
	{
		String win_str;
		if (m_data->players[0].IsWinner())
		{
			win_str = L"Player 1";
		}
		else
		{
			win_str = L"Player 2";
		}

		m_data->main_font(win_str, L"の勝ち！").drawCenter(Window::Center());

		// タイムを描画
		m_data->small_font(L"Time : ", m_data->timer.s(), L"[s]").drawCenter(Window::Center() + Point(0, 50));
		// プレイヤー1のスコアを描画
		m_data->main_font(m_data->players[0].Score()).drawCenter(Point(Window::Center().x / 5.0, Window::Center().y));
		// プレイヤー2のスコアを描画
		m_data->main_font(m_data->players[1].Score()).drawCenter(Point(Window::Size().x - Window::Size().x / 5.0, Window::Center().y));

		m_data->field.Draw();
	}
};

void Main()
{	
	MyApp manager;

	// シーンの追加
	manager.add<Title>(L"Title");
	manager.add<Game>(L"Game");
	manager.add<Result>(L"Result");

	// UI用フォントの登録
	FontAsset::Register(L"UI_Small", 14, L"Meiryo UI", FontStyle::Regular);
	FontAsset::Register(L"UI", 18, L"Meiryo UI", FontStyle::Regular);
	FontAsset::Register(L"UI_Large", 28, L"Meiryo UI", FontStyle::Bold);

	while (System::Update())
	{
		manager.updateAndDraw();
	}
}
