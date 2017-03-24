#pragma once
#include "../TextureUI.h"
#include "../../../../../Utility/Input/Mouse/Mouse.h"


class ButtonUI : public TextureUI
{
public:

	ButtonUI() :
		origin_size(ci::Vec2f::zero()),
		flexible_value(0.0f),
		is_clicked(false),
		is_easing(false)
	{}
	virtual  ~ButtonUI() {}

	bool GetIsClicked() const { return is_clicked; }
	void SetIsClicked(const bool &is_clicked_) { is_clicked = is_clicked_; }

	virtual void Setup() override {}
	virtual void Setup(const ci::JsonTree &params) override
	{
		ci::Vec2f pos = GetVec2f(params["pos"]);
		origin_size = GetVec2f(params["size"]);
		texture_name = params.getValueForKey<std::string>("texture_name");
		ci::Vec4f color_ = GetVec4f(params["color"]);
		flexible_value = params.getValueForKey<float>("flexible_value");

		transform.pos =
			ci::Vec3f(pos.x, pos.y, 0.0f);
		transform.scale =
			ci::Vec3f(origin_size.x, origin_size.y, 1.0f);
		color = ci::ColorAf(color_.x, color_.y, color_.z, color_.w);
	}
	virtual void Update() override
	{
		if (!is_easing && Mouse::Get().IsPushButton(ci::app::MouseEvent::LEFT_DOWN))
		{
			if (IsCollisionMouse(Mouse::Get().GetMousePosition()))
				Clicked();
		}
	}

protected:

	void Clicked()
	{
		is_easing = true;
		EasingManager::Get().Register(&(transform.scale.x),
			EasingManager::EasingType::CUBICOUT,
			0, 0.25f,
			transform.scale.x, transform.scale.x + flexible_value);

		EasingManager::Get().Register(&(transform.scale.y),
			EasingManager::EasingType::CUBICOUT,
			0, 0.25f,
			transform.scale.y, transform.scale.y + flexible_value).SetEndFunc([&]
		{

			EasingManager::Get().Register(&(transform.scale.x),
				EasingManager::EasingType::CUBICOUT,
				0.0f, 0.25f,
				transform.scale.x, origin_size.x);

			EasingManager::Get().Register(&(transform.scale.y),
				EasingManager::EasingType::CUBICOUT,
				0.0f, 0.25f,
				transform.scale.y, origin_size.y).SetEndFunc([&]
			{
				is_clicked = !is_clicked;
				is_easing = false;
			});
		});
	}

	ci::Vec2f origin_size;
	float flexible_value;
	bool is_clicked;
	bool is_easing;
};