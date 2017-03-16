#pragma once
#include "../TextureUI.h"
#include "../../../../../Utility/Input/Mouse/Mouse.h"


class ButtonUI : public TextureUI
{
public:

	ButtonUI() :
		origin_scale(ci::Vec3f::one()),
		is_clicked(false),
		is_ease_end(false)
	{}
	virtual  ~ButtonUI() {}

	bool GetIsClicked() const { return is_clicked; }
	bool GetIsEaseEnd() const { return is_ease_end; }

	virtual void Setup() override {}
	virtual void Setup(const ci::JsonTree &params) override {}
	virtual void Update() override
	{
		if (!is_clicked && Mouse::Get().IsPushButton(ci::app::MouseEvent::LEFT_DOWN))
		{
			if (IsCollisionMouse(Mouse::Get().GetMousePosition()))
				Clicked();
		}
	}
	virtual void Draw() override {}

protected:

	void Clicked()
	{
		is_clicked = true;
		EasingManager::Get().Register(&is_ease_end, &(transform.scale.x), EasingManager::EasingType::CUBICOUT, 0, 0.25f, transform.scale.x, transform.scale.x + 10.0f);
		EasingManager::Get().Register(&is_ease_end, &(transform.scale.y), EasingManager::EasingType::CUBICOUT, 0, 0.25f, transform.scale.y, transform.scale.y + 10.0f);
		EasingManager::Get().Register(&is_ease_end, &(transform.scale.z), EasingManager::EasingType::CUBICOUT, 0, 0.25f, transform.scale.z, transform.scale.z + 10.0f);
		EasingManager::Get().Register(&is_ease_end, &(transform.scale.x), EasingManager::EasingType::CUBICOUT, 0.25f, 0.5f, transform.scale.x, origin_scale.x);
		EasingManager::Get().Register(&is_ease_end, &(transform.scale.y), EasingManager::EasingType::CUBICOUT, 0.25f, 0.5f, transform.scale.y, origin_scale.y);
		EasingManager::Get().Register(&is_ease_end, &(transform.scale.z), EasingManager::EasingType::CUBICOUT, 0.25f, 0.5f, transform.scale.z, origin_scale.z);
	}

	ci::Vec3f origin_scale;
	bool is_clicked;
	bool is_ease_end;
};