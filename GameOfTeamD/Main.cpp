
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
	Font font{ 25 };
	// プレイヤーフィールドの中心にプレイヤーの位置を設定する
	Player players[2] = 
	{ 
		{PlayerType::One, field.PlayerCenter(PlayerType::One)}, 
		{PlayerType::Two, field.PlayerCenter(PlayerType::Two)} 
	};

	BlockManager b_manager{};
};

using MyApp = SceneManager<String, CommonData>;

class Title : public MyApp::Scene
{
public:

	void update() override 
	{
		if (Input::AnyKeyClicked())
		{
			changeScene(L"Game");
		}
	}

	void draw() const override
	{
		m_data->font(L"お宅の庭敷き詰めます").drawCenter(Window::Center());
	}
};

class Game : public MyApp::Scene
{
public:
	void init() override
	{
		m_data->timer.start();

		// プレイヤーの大きさを設定
		for (auto& p : m_data->players)
		{
			p.Shape.r = MyGame::Zk / 2 - 1;
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

		// ブロックを動かす
		m_data->b_manager.Update(m_data->field, m_data->players);
		m_data->field.Update();
	}

	void draw() const override
	{
		m_data->field.Draw();

		// タイムを描画
		m_data->font(L"Time : ", m_data->timer.s(), L"[s]").drawCenter(Window::Center());
		// プレイヤー1のスコアを描画
		m_data->font(m_data->players[0].Score()).drawCenter(Point(Window::Center().x / 5.0, Window::Center().y));
		// プレイヤー2のスコアを描画
		m_data->font(m_data->players[1].Score()).drawCenter(Point(Window::Size().x - Window::Size().x / 5.0, Window::Center().y));

		m_data->b_manager.DrawBlocks();

		// プレイヤーを描画
		m_data->players[0].Shape.draw();
		m_data->players[1].Shape.draw();
	}
private:
	int m_i = 0;
};

class Result : public MyApp::Scene
{
public :
	void init() override
	{

	}

	void update() override
	{

	}

	void draw() const override
	{

	}
};

void Main()
{	
	MyApp manager;

	manager.add<Title>(L"Title");
	manager.add<Game>(L"Game");

	while (System::Update())
	{
		manager.updateAndDraw();
	}
}
