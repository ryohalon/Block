#pragma once
#include <set>
#include <map>

#define GamePad MyGamePad::Get()


class MyGamePad
{
public:

	enum ButtonID
	{
		RECT,
		CROSS,
		CIRCLE,
		TRIANGLE,
		L1,
		R1,
		L2,
		R2,
		SELECT,
		START,
		L3,
		R3,
		PS
	};

	enum AxisID
	{
		LEFT_AXIS_LEFT_RIGHT = 0,
		LEFT_AXIS_UP_DUWN = 1,
		RIGHT_AXIS_LEFT_RIGHT = 2,
		RIGHT_AXIS_UP_DOWN = 3,
		CROSS_AXIS_LEFT_RIGHT = 4,
		CROSS_AXIS_UP_DOWN = 5
	};

private:

	std::set<int> push_axis_buttons;
	std::set<int> press_axis_buttons;
	std::set<int> pull_axis_buttons;
	std::map<int, float> axis;

public:

	MyGamePad();
	~MyGamePad();

	void SetPushAxisButtons(const int &button_ID);
	void SetPressAxisButtons(const int &button_ID);
	void SetPullAxisButtons(const int &button_ID);
	void SetAxisValue(const int &axis_ID, const float &value);

	float GetAxisValue(const int &axis_ID);
	bool IsPushAxisButton(const int &axis_button_ID);
	bool IsPressAxisButton(const int &axis_button_ID);
	bool IsPullAxisButton(const int &axis_button_ID);

	static MyGamePad& Get()
	{
		static MyGamePad gamepad;

		return gamepad;
	}
	
	void FlushInput();
	void ShutDown();

	void GamePadSetup();
	void Setup();
	void Update();
};



void onButtonDown(struct Gamepad_device * device, unsigned int buttonID, double timestamp, void * context);
void onButtonUp(struct Gamepad_device * device, unsigned int buttonID, double timestamp, void * context);
void onAxisMoved(struct Gamepad_device * device, unsigned int axisID, float value, float lastValue, double timestamp, void * context);
void onDeviceAttached(struct Gamepad_device * device, void * context);
void onDeviceRemoved(struct Gamepad_device * device, void * context);