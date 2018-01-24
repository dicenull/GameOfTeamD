#pragma once
#include <Siv3D.hpp>

class DashedLine
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="start">始点</param>
	/// <param name="end">終点</param>
	/// <param name="count">破線の回数</param>
	/// <param name="origin">線を消し始める場所</param>
	DashedLine(Point start, Point end, int count, Point origin);
	~DashedLine();

	void Draw(Color color) const;

private:
	Point m_start, m_end, m_origin;
	int m_count;
};

