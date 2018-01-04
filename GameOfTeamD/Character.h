#pragma once

#include <Siv3D.hpp>

template <class Type>
class Character
{
public:
	Character();
	Character(double speed);
	virtual ~Character();

public:
	Type Shape;

private:
	double m_speed;
};

template <class Type>
Character<Type>::Character()
{
	Shape = Type();
}

template<class Type>
Character<Type>::Character(double speed)
	: Character<Type>::Character()
{
	m_speed = speed;
}

template<class Type>
Character<Type>::~Character()
{}
