
# include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Field.h"
#include "Player.h"

struct CommonData
{
	Field field{ Window::Size() };
	Stopwatch timer;
	Font font{ 25 };
	Player players[2];
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
	}

	void update() override
	{
	}

	void draw() const override
	{
		m_data->field.Draw();

		// タイムを描画
		m_data->font(L"Time : ", m_data->timer.s(), L"[s]").drawCenter(Window::Center());
		// プレイヤー1のスコアを描画
		m_data->font(m_data->players[0].Point()).drawCenter(Point(Window::Center().x / 5.0, Window::Center().y));
		// プレイヤー2のスコアを描画
		m_data->font(m_data->players[1].Point()).drawCenter(Point(Window::Size().x - Window::Size().x / 5.0, Window::Center().y));
	}
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
