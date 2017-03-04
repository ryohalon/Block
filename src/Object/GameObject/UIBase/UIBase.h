#pragma once
#include "../GameObject.h"


class UIBase : public GameObject
{
public:

	UIBase() {}
	UIBase(const Transform &transform) :
		GameObject(transform)
	{}
	virtual ~UIBase() {}

	virtual void Setup() {}
	virtual void Setup(const ci::JsonTree &params) {}
	virtual void Update() {}
	virtual void Draw() {};

	virtual bool IsCollisionMouse(const ci::Vec2f &mouse_pos)
	{
		if (mouse_pos.x < transform.pos.x || mouse_pos.x > transform.pos.x + transform.scale.x)
			return false;
		if (mouse_pos.y < transform.pos.y || mouse_pos.y > transform.pos.y + transform.scale.y)
			return false;

		return true;
	}

private:

	ci::Vec2f anchor;
};