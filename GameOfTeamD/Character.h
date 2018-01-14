#pragma once

#include <Siv3D.hpp>

template <class Type>
class Character
{
public:
	///<summary>
	/// コンストラクタ
	///</summary>
	///<param name="speed">キャラクタの動く速さ</param>
	Character(double speed = 2.0);

	///<summary>
	/// デストラクタ
	///</summary>
	virtual ~Character();

public:
	///<summary>
	/// スピードを取得する
	///</summary>
	double Speed();

public:
	///<summary>
	/// キャラクタの図形を取得する
	///</summary>
	Type Shape;

private:
	///<summary>
	/// 速さのデータ
	///</summary>
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
