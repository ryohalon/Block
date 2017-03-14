#pragma once
#include "../TextureUI.h"
#include "../../../../../Utility/Input/Mouse/Mouse.h"


class ButtonUI : public TextureUI
{
public:

	ButtonUI() :
		flag(nullptr)
	{}
	ButtonUI() {}

	void SetFlag(bool &flag_) { flag = &flag_; }

	void Setup() override {}
	void Setup(const ci::JsonTree &params) override {}
	void Update() override
	{
		if (Mouse::Get().IsPushButton(ci::app::MouseEvent::LEFT_DOWN))
		{
			if (IsCollisionMouse(Mouse::Get().GetMousePosition()))
				(*flag) = !(*flag);
		}
	}

private:

	bool *flag;
};