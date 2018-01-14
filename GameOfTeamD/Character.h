#pragma once

#include <Siv3D.hpp>

template <class Type>
class Character
{
public:
	Character(double speed = 2.0);
	virtual ~Character();

public:
	double Speed();

public:
	Type Shape;

private:
	double m_speed;
};

template<class Type>
Character<Type>::Character(double speed)
{
	Shape = Type();
	m_speed = speed;
}

template<class Type>
Character<Type>::~Character()
{}

template<class Type>
inline double Character<Type>::Speed()
{
	return m_speed;
}
