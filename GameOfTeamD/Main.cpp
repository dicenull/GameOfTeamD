
# include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Field.h"

struct CommonData
{
	Field field{ Window::Size() };
	Stopwatch timer;
	Font font{ 30 };
	int point[2];
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
		m_data->font(L"Time : ", m_data->timer.s(), L"[s]").drawCenter(Window::Center());
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
