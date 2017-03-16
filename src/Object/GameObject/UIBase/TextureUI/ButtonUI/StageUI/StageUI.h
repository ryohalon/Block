#pragma once
#include "../ButtonUI.h"
#include "../../../../../../Utility/Manager/TimeManager/TimeManager.h"



class WorldUI : public ButtonUI
{
public:

	WorldUI() :
		stage_num(1),
		rotate_speed(ci::Vec3f::zero()),
		normal_size(0.0f),
		on_mouse_size(0.0f),
		is_on_mouse(false)
	{}
	~WorldUI() {}

	int GetStageNum() const { return stage_num; }
	void SetStageNum(const int &stage_num_) { stage_num = stage_num_; }

	void Setup() override {}
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

		if (!is_clicked)
		{
			if (is_ease_end && !is_on_mouse && IsCollisionMouse(Mouse::Get().GetMousePosition()))
			{
				is_on_mouse = true;
				is_ease_end = false;
				EasingManager::Get().Register(&is_ease_end, &(transform.scale.x), EasingManager::EasingType::BACKINOUT, 0, 0.5f, transform.scale.x, on_mouse_size);
				EasingManager::Get().Register(&is_ease_end, &(transform.scale.y), EasingManager::EasingType::BACKINOUT, 0, 0.5f, transform.scale.y, on_mouse_size);
				EasingManager::Get().Register(&is_ease_end, &(transform.scale.z), EasingManager::EasingType::BACKINOUT, 0, 0.5f, transform.scale.z, on_mouse_size);
				EasingManager::Get().Register(&is_ease_end, &(transform.angle.x), EasingManager::EasingType::QUARTOUT, 0, 0.5f, transform.angle.x, 0.0f);
				EasingManager::Get().Register(&is_ease_end, &(transform.angle.y), EasingManager::EasingType::QUARTOUT, 0, 0.5f, transform.angle.y, 0.0f);
				EasingManager::Get().Register(&is_ease_end, &(transform.angle.z), EasingManager::EasingType::QUARTOUT, 0, 0.5f, transform.angle.z, 0.0f);
			}

			if (is_ease_end && is_on_mouse && !IsCollisionMouse(Mouse::Get().GetMousePosition()))
			{
				is_on_mouse = false;
				is_ease_end = false;
				EasingManager::Get().Register(&is_ease_end, &(transform.scale.x), EasingManager::EasingType::BACKINOUT, 0, 0.5f, transform.scale.x, normal_size);
				EasingManager::Get().Register(&is_ease_end, &(transform.scale.y), EasingManager::EasingType::BACKINOUT, 0, 0.5f, transform.scale.y, normal_size);
				EasingManager::Get().Register(&is_ease_end, &(transform.scale.z), EasingManager::EasingType::BACKINOUT, 0, 0.5f, transform.scale.z, normal_size);
			}
		}
		
		if (is_ease_end && is_on_mouse && !is_clicked)
		{
			if (Mouse::Get().IsPushButton(ci::app::MouseEvent::LEFT_DOWN))
				Clicked();
		}
	}
	void Draw() override
	{
		ci::gl::pushModelView();

		UpdateMatrix();
		glMultMatrixf(matrix);
		ci::gl::color(color);
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