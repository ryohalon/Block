#pragma once
#include "../GameObject.h"



class CubeBase : public GameObject
{
public:

	CubeBase() :
		color(ci::ColorA::white())
	{}
	virtual ~CubeBase() {}

	void SetColor(const ci::ColorA &color_) { color = color_; }

	virtual void Setup() override
	{
		UpdateMatrix();
	}
	virtual void Update() override {}
	virtual void Draw() override
	{
		ci::gl::pushModelView();

		glMultMatrixf(matrix);

		ci::gl::color(color);
		ci::gl::drawCube(ci::Vec3f::zero(), ci::Vec3f::one());

		ci::gl::popModelView();
	}

protected:

	ci::ColorA color;
};