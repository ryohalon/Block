#pragma once
#include "../ButtonUI.h"
#include "../../../../../../Utility/Manager/TimeManager/TimeManager.h"



class StageUI : public ButtonUI
{
public:

	StageUI() :
		stage_num(1),
		rotate_speed(ci::Vec3f::zero()),
		normal_size(0.0f),
		on_mouse_size(0.0f),
		is_on_mouse(false)
	{}
	~StageUI() {}

	int GetStageNum() const { return stage_num; }
	void SetStageNum(const int &stage_num_) { stage_num = stage_num_; }

	void Setup() override 
	{
		rotate_speed = ci::Vec3f(10, 10, 10);
		normal_size = 100.0f;
		on_mouse_size = 300.0f;
		transform.scale = ci::Vec3f::one() * normal_size;
	}
	void Setup(const ci::JsonTree &params) override
	{
		rotate_speed = GetVec3f(params["rotate_speed"]);
		normal_size = params.getValueForKey<float>("normal_size");
		on_mouse_size = params.getValueForKey<float>("on_mouse_size");
		texture_name = params.getValueForKey<std::string>("texture_name");
		transform.scale = ci::Vec3f::one() * normal_size;
	}
	void Update() override
	{
		if (!is_on_mouse)
			transform.angle += rotate_speed * TimeManager::Get().GetDeltaTime();

	}
	void Draw() override
	{
		ci::gl::pushModelView();

		UpdateMatrix();
		glMultMatrixf(matrix);
		//ci::gl::color(color);
		TextureManager::Get().GetTexture(texture_name).enableAndBind();
		ci::gl::drawCube(ci::Vec3f::zero(), ci::Vec3f::one());
		TextureManager::Get().GetTexture(texture_name).unbind();

		ci::gl::popModelView();
	}

private:

	int stage_num;
	ci::Vec3f rotate_speed;
	float normal_size;
	float on_mouse_size;
	bool is_on_mouse;
};