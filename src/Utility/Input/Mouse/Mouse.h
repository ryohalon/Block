#pragma once
#include <set>
#include <memory>
#include <cinder/Vector.h>

namespace cinder {
	namespace app {
		class MouseEvent;
	}
}
namespace ci = cinder;


class Mouse
{
public:

	Mouse();
	~Mouse();

	static Mouse& Get()
	{
		static Mouse mouse;

		return mouse;
	}

	//マウスの座標の取得
	ci::Vec2i GetMousePosition();
	// マウスのホイール入力の取得
	float GetMouseWheelValue();

	//入力情報の削除
	void FlushInput();

	void UpdateMousePosition(const ci::app::MouseEvent &mouse_event);
	void UpdateMouseWheelValue(const ci::app::MouseEvent &mouse_event);
	void PushButton(const ci::app::MouseEvent &mouse_event);
	void PullButton(const ci::app::MouseEvent &mouse_event);

	bool IsPushButton();
	bool IsPushButton(const int &button);
	bool IsPressButton();
	bool IsPressButton(const int &button);
	bool IsPullButton();
	bool IsPullButton(const int &button);

private:

	struct MouseStatus
	{
		std::set<int> push_mouse_button;
		std::set<int> press_mouse_button;
		std::set<int> pull_mouse_button;
		ci::Vec2i mouse_pos;
		float wheel_value;
	};

	std::unique_ptr<MouseStatus> mouse_status;

};