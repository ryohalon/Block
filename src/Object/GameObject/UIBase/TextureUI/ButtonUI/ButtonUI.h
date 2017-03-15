#pragma once
#include "../TextureUI.h"
#include "../../../../../Utility/Input/Mouse/Mouse.h"


class ButtonUI : public TextureUI
{
public:

	ButtonUI() :
		flag(nullptr)
	{}
	virtual  ~ButtonUI() {}

	void SetFlag(bool &flag_) { flag = &flag_; }

	virtual void Setup() override {}
	virtual void Setup(const ci::JsonTree &params) override {}
	virtual void Update() override
	{
		if (Mouse::Get().IsPushButton(ci::app::MouseEvent::LEFT_DOWN))
		{
			if (IsCollisionMouse(Mouse::Get().GetMousePosition()))
				(*flag) = !(*flag);
		}
	}
	virtual void Draw() override {}

protected:

	bool *flag;
};