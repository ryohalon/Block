#pragma once
#include "../TextureUI.h"
#include "../../../../../Utility/Input/Mouse/Mouse.h"


class ButtonUI : public TextureUI
{
public:

	ButtonUI() :
		origin_size(ci::Vec2f::zero()),
		flexible_value(0.0f),
		take_time(0.5f),
		clicked_func(nullptr)
	{}
	virtual  ~ButtonUI() {}

	void SetClickedFunc(const std::function<void()> &clicked_func_) { clicked_func = clicked_func_; }
	void SetFlexibleValue(const float &flaxible_value_) { flexible_value = flaxible_value_; }
	void SetOriginSize(const ci::Vec2f &origin_size_) { origin_size = origin_size_; }
	void SetTakeTime(const float &take_time_) { take_time = take_time_; }

	virtual void Setup() override {}
	virtual void Setup(const ci::JsonTree &params) override
	{
		ci::Vec2f pos = GetVec2f(params["pos"]);
		origin_size = GetVec2f(params["size"]);
		texture_name = params.getValueForKey<std::string>("texture_name");
		color = GetColorAf(params["color"]);
		flexible_value = params.getValueForKey<float>("flexible_value");
		take_time = params.getValueForKey<float>("take_time");

		transform.pos =
			ci::Vec3f(pos.x, pos.y, 0.0f);
		transform.scale =
			ci::Vec3f(origin_size.x, origin_size.y, 1.0f);

	}
	virtual void Update() override
	{
		if (!is_active)
			return;

		if (!EasingManager::Get().IsEaseEnd(&(transform.scale.x)))
			return;

		if (Mouse::Get().IsPushButton(ci::app::MouseEvent::LEFT_DOWN))
		{
			if (IsCollisionMouse(Mouse::Get().GetMousePosition()))
				Clicked();
		}
	}

	virtual void Draw() override
	{
		if (!is_active)
			return;

		ci::gl::pushModelView();
		ci::gl::translate(ci::Vec3f::zAxis() * transform.pos);
		ci::gl::color(color);
		TextureManager::Get().GetTexture(texture_name).enableAndBind();
		DrawtexCoord(transform.pos.xy(),
			transform.scale.xy());
		TextureManager::Get().GetTexture(texture_name).unbind();
		ci::gl::popModelView();
	}

protected:

	void Clicked()
	{
		if (clicked_func != nullptr)
			clicked_func();

		EasingManager::Get().Register(&(transform.scale.x),
			EasingManager::EasingType::CUBICOUT,
			0, take_time / 2.0f,
			transform.scale.x, transform.scale.x + flexible_value);

		EasingManager::Get().Register(&(transform.scale.y),
			EasingManager::EasingType::CUBICOUT,
			0, take_time / 2.0f,
			transform.scale.y, transform.scale.y + flexible_value).SetEndFunc([this]
		{
			EasingManager::Get().Register(&(transform.scale.x),
				EasingManager::EasingType::CUBICOUT,
				0.0f, take_time / 2.0f,
				transform.scale.x, origin_size.x);

			EasingManager::Get().Register(&(transform.scale.y),
				EasingManager::EasingType::CUBICOUT,
				0.0f, take_time / 2.0f,
				transform.scale.y, origin_size.y);
		});

		SoundManager::Get().GetSound("Select").Play();
	}

	ci::Vec2f origin_size;
	float flexible_value;
	float take_time;
	std::function<void()> clicked_func;
};