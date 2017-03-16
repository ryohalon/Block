#pragma once
#include "../GameObject.h"
#include "../../../Utility/Manager/EasingManager/EasingManager.h"


class UIBase : public GameObject
{
public:

	UIBase() :
		default_pos(ci::Vec2f::zero()),
		default_size(ci::Vec2f::zero()),
		color(ci::ColorAf::white())
	{}
	UIBase(const Transform &transform) :
		GameObject(transform)
	{}
	virtual ~UIBase() {}

	virtual void Resize(const float &window_ratio)
	{
		transform.pos = ci::Vec3f(
			default_pos.x * window_ratio,
			default_pos.y * window_ratio,
			transform.pos.z);

		transform.scale = ci::Vec3f(
			default_size.x * window_ratio,
			default_size.y * window_ratio,
			transform.pos.z);
	}
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

	ci::Vec2f default_pos;
	ci::Vec2f default_size;
	ci::ColorAf color;
};