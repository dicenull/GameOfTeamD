#include "DashedLine.h"


DashedLine::DashedLine(Point start, Point end, int count, Point origin)
	: m_start(start), m_end(end), m_count(count), m_origin(origin)
{}



DashedLine::~DashedLine()
{
}

void DashedLine::Draw(Color color) const
{
	Line(m_start, m_origin).draw(color);

	bool flip = (m_start.x > m_end.x || m_start.y > m_end.y);

	Size inc = { Abs<int>(m_end.x - m_start.x), Abs<int>(m_end.y - m_start.y) };
	Point dash{ inc.x / (m_count * 2), inc.y / (m_count * 2) };

	if (flip)
	{
		for (Point p = m_origin - dash; p.x - dash.x >= m_end.x && p.y - dash.y >= m_end.y; p -= dash * 2)
		{
			Line(p, p - dash).draw(color);
		}
	}
	else
	{
		for (Point p = m_origin + dash; p.x + dash.x <= m_end.x && p.y + dash.y <= m_end.y; p += dash * 2)
		{
			Line(p, p + dash).draw(color);
		}
	}
}



