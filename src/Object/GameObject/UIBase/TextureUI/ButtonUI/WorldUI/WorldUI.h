#pragma once
#include "../ButtonUI.h"
#include "../../../../../../Utility/Manager/TimeManager/TimeManager.h"



class WorldUI : public ButtonUI
{
public:

	WorldUI() :
		rotate_speed(ci::Vec3f::zero()),
		normal_size(0.0f),
		on_mouse_size(0.0f)
	{}
	~WorldUI() {}

	void Setup() override {}
	void Setup(const ci::JsonTree &params) override
	{
		rotate_speed = GetVec3f(params["rotate_speed"]);
		normal_size = params.getValueForKey<float>("normal_size");
		on_mouse_size = params.getValueForKey<float>("on_mouse_size");
		transform.scale = ci::Vec3f::one() * normal_size;
	}
	void Update() override
	{
		transform.angle += rotate_speed * TimeManager::Get().GetDeltaTime();
	}
	void Draw() override
	{
		ci::gl::pushModelView();

		UpdateMatrix();
		glMultMatrixf(matrix);
		ci::gl::color(color);
		(*texture).enableAndBind();
		ci::gl::drawCube(ci::Vec3f::zero(), ci::Vec3f::one());
		(*texture).unbind();

		ci::gl::popModelView();
	}

private:

	ci::Vec3f rotate_speed;
	float normal_size;
	float on_mouse_size;
	bool is_on_mouse;
};