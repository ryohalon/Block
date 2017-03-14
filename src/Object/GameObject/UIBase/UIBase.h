#pragma once
#include "../GameObject.h"


class UIBase : public GameObject
{
public:

	UIBase() :
		color(ci::ColorAf::white())
	{}
	UIBase(const Transform &transform) :
		GameObject(transform)
	{}
	virtual ~UIBase() {}

	virtual void Setup() override {}
	virtual void Setup(const ci::JsonTree &params) override {}
	virtual void Update() override {}
	virtual void Draw() override {}

	virtual bool IsCollisionMouse(const ci::Vec2i &mouse_pos)
	{
		if (mouse_pos.x < transform.pos.x || mouse_pos.x > transform.pos.x + transform.scale.x)
			return false;
		if (mouse_pos.y < transform.pos.y || mouse_pos.y > transform.pos.y + transform.scale.y)
			return false;

		return true;
	}

protected:

	ci::ColorAf color;
};