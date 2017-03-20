#pragma once
#include "../TextureUI.h"
#include "../../../../../Utility/Input/Mouse/Mouse.h"


class ButtonUI : public TextureUI
{
public:

	ButtonUI() :
		origin_size(ci::Vec3f::zero()),
		flexible_value(0.0f),
		is_clicked(false)
	{}
	virtual  ~ButtonUI() {}

	bool GetIsClicked() const { return is_clicked; }

	virtual void Setup() override {}
	virtual void Setup(const ci::JsonTree &params) override
	{
		default_pos = GetVec2f(params["pos"]);
		default_size = GetVec2f(params["size"]);
		texture_name = params.getValueForKey<std::string>("texture_name");
		flexible_value = params.getValueForKey<float>("flexible_value");

		transform.pos = ci::Vec3f(default_pos.x,
			default_pos.y,
			0.0f);
		transform.scale = ci::Vec3f(default_size.x,
			default_size.y,
			1.0f);
	}
	virtual void Update() override
	{
		if (!is_clicked && Mouse::Get().IsPushButton(ci::app::MouseEvent::LEFT_DOWN))
		{
			if (IsCollisionMouse(Mouse::Get().GetMousePosition()))
				Clicked();
		}
	}
	virtual void Draw() override
	{
		ci::gl::pushModelView();

		ci::gl::popModelView();
	}

protected:

	void Clicked()
	{
		is_clicked = true;
		EasingManager::Get().Register(&(transform.scale.x), EasingManager::EasingType::CUBICOUT, 0, 0.25f, transform.scale.x, transform.scale.x + flexible_value);
		EasingManager::Get().Register(&(transform.scale.y), EasingManager::EasingType::CUBICOUT, 0, 0.25f, transform.scale.y, transform.scale.y + flexible_value);
		EasingManager::Get().Register(&(transform.scale.x), EasingManager::EasingType::CUBICOUT, 0.25f, 0.5f, transform.scale.x, default_size.x);
		EasingManager::Get().Register(&(transform.scale.y), EasingManager::EasingType::CUBICOUT, 0.25f, 0.5f, transform.scale.y, default_size.y);
	}

	ci::Vec3f origin_size;
	float flexible_value;
	bool is_clicked;
};