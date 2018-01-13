
# include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Field.h"
#include "Player.h"
#include "Block.h"
#include "BlockManager.h"

struct CommonData
{
	Field field;
	Stopwatch timer;
	Font font{ 25 };
	// プレイヤーフィールドの中心にプレイヤーの位置を設定する
	Player players[2] = { {field.PlayerCenter(Players::One)}, {field.PlayerCenter(Players::Two)} };

	BlockManager b_manager{ field.Zk() };
	Block b1{ Grid<Color>(2, 2, Array<Color>({ Palette::White, Palette::Red, Palette::Blue, Palette::Green })) };
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

		for (auto& p : m_data->players)
		{
			p.Shape.r = m_data->field.Zk() / 2;
		}
	}

	void update() override
	{
		if (Input::KeyB.clicked)
		{
			m_data->b_manager.CreateBlock(Players::One, m_i, m_data->b1, m_data->field);

			m_i = (m_i < m_data->field.Height() / m_data->field.Zk() - 2) ? m_i + 1 : 0;
		}

		if (Input::KeyF.clicked)
		{
			m_data->field.SetMirror(Players::One, true);
			m_data->field.SetMirror(Players::Two, false);
		}
		if (Input::KeyR.clicked)
		{
			m_data->field.SetMirror(Players::One, false);
			m_data->field.SetMirror(Players::Two, true);
		}

		m_data->b_manager.Update(m_data->field);
		m_data->field.Update();
	}

	void draw() const override
	{
		m_data->b1.Draw(m_data->field.Zk());

		m_data->field.Draw();

		// タイムを描画
		m_data->font(L"Time : ", m_data->timer.s(), L"[s]").drawCenter(Window::Center());
		// プレイヤー1のスコアを描画
		m_data->font(m_data->players[0].Score()).drawCenter(Point(Window::Center().x / 5.0, Window::Center().y));
		// プレイヤー2のスコアを描画
		m_data->font(m_data->players[1].Score()).drawCenter(Point(Window::Size().x - Window::Size().x / 5.0, Window::Center().y));

		m_data->b_manager.DrawBlocks();

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
