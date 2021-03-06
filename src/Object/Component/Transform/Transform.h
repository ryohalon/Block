#pragma once
#include "cinder/Vector.h"



class Transform
{
public:

	Transform() :
		pos(ci::Vec3f::zero()),
		angle(ci::Vec3f::zero()),
		scale(ci::Vec3f::one())
	{

	}
	Transform(const ci::Vec3f &pos,
		const ci::Vec3f &angle,
		const ci::Vec3f &scale) :
		pos(pos),
		angle(angle),
		scale(scale)
	{

	}
	~Transform() {}

	// 座標
	ci::Vec3f pos;
	// 回転
	ci::Vec3f angle;
	// 大きさ
	ci::Vec3f scale;
};