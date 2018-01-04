
# include <Siv3D.hpp>
#include "Field.h"

void Main()
{	
	const Font font(20);
	Field my_field(Window::Size());
	
	while (System::Update())
	{
		my_field.Draw();
	}
}
