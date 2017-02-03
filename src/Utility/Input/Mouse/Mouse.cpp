#include "Mouse.h"



Mouse::Mouse()
{
	mouse_status = std::make_unique<MouseStatus>();
	mouse_status->mouse_pos = ci::Vec2i::zero();
}

Mouse::~Mouse()
{

}

ci::Vec2i Mouse::GetMousePosition()
{
	return mouse_status->mouse_pos;
}

float Mouse::GetMouseWheelValue()
{
	return mouse_status->wheel_value;
}

void Mouse::UpdateMousePosition(const ci::app::MouseEvent &mouse_event)
{
	mouse_status->mouse_pos = mouse_event.getPos();
}

void Mouse::UpdateMouseWheelValue(const ci::app::MouseEvent &mouse_event)
{
	mouse_status->wheel_value = mouse_event.getWheelIncrement();
}

void Mouse::PushButton(const ci::app::MouseEvent &mouse_event)
{
	if (mouse_event.isLeftDown())
	{
		mouse_status->push_mouse_button.insert(ci::app::MouseEvent::LEFT_DOWN);
		mouse_status->press_mouse_button.insert(ci::app::MouseEvent::LEFT_DOWN);
	}

	if (mouse_event.isMiddleDown())
	{
		mouse_status->push_mouse_button.insert(ci::app::MouseEvent::MIDDLE_DOWN);
		mouse_status->press_mouse_button.insert(ci::app::MouseEvent::MIDDLE_DOWN);
	}

	if (mouse_event.isRightDown())
	{
		mouse_status->push_mouse_button.insert(ci::app::MouseEvent::RIGHT_DOWN);
		mouse_status->press_mouse_button.insert(ci::app::MouseEvent::RIGHT_DOWN);
	}
}

void Mouse::PullButton(const ci::app::MouseEvent &mouse_event)
{
	if (mouse_event.isLeft())
	{
		mouse_status->press_mouse_button.erase(ci::app::MouseEvent::LEFT_DOWN);
		mouse_status->pull_mouse_button.insert(ci::app::MouseEvent::LEFT_DOWN);
	}

	if (mouse_event.isMiddle())
	{
		mouse_status->press_mouse_button.erase(ci::app::MouseEvent::MIDDLE_DOWN);
		mouse_status->pull_mouse_button.insert(ci::app::MouseEvent::MIDDLE_DOWN);
	}

	if (mouse_event.isRight())
	{
		mouse_status->press_mouse_button.erase(ci::app::MouseEvent::RIGHT_DOWN);
		mouse_status->pull_mouse_button.insert(ci::app::MouseEvent::RIGHT_DOWN);
	}
}

void Mouse::FlushInput()
{
	mouse_status->push_mouse_button.clear();
	mouse_status->pull_mouse_button.clear();

	mouse_status->wheel_value = 0.0f;
}

bool Mouse::IsPushButton()
{
	return mouse_status->push_mouse_button.size() != 0;
}

bool Mouse::IsPushButton(const int &button)
{
	return mouse_status->push_mouse_button.find(button) != mouse_status->push_mouse_button.cend();
}

bool Mouse::IsPressButton()
{
	return mouse_status->press_mouse_button.size() != 0;
}

bool Mouse::IsPressButton(const int &button)
{
	return mouse_status->press_mouse_button.find(button) != mouse_status->press_mouse_button.cend();
}

bool Mouse::IsPullButton()
{
	return mouse_status->pull_mouse_button.size() != 0;
}

bool Mouse::IsPullButton(const int &button)
{
	return mouse_status->pull_mouse_button.find(button) != mouse_status->pull_mouse_button.cend();
}
