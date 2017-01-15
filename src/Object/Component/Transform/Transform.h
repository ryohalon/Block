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

	// ç¿ïW
	ci::Vec3f pos;
	// âÒì]
	ci::Vec3f angle;
	// ëÂÇ´Ç≥
	ci::Vec3f scale;
};