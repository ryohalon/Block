#include "MyGamePad.h"
#include "cinder/app/App.h"

extern "C"
{
#include "Gamepad.h"
}

# pragma comment(lib, "winmm.lib")
#ifdef _DEBUG
# pragma comment(lib, "../lib/msw/x86/Gamepad_d.lib")
#else
# pragma comment(lib, "../lib/msw/x86/Gamepad.lib")
#endif

using namespace ci;
using namespace ci::app;

static bool verbose = false;

void MyGamePad::SetPushAxisButtons(const int &button_ID)
{
	if (press_axis_buttons.find(button_ID) != press_axis_buttons.cend())
		return;

	push_axis_buttons.insert(button_ID);
}

void MyGamePad::SetPressAxisButtons(const int &button_ID)
{
	if (press_axis_buttons.find(button_ID) != press_axis_buttons.cend())
		return;

	press_axis_buttons.insert(button_ID);
}

void MyGamePad::SetPullAxisButtons(const int &button_ID)
{
	if (pull_axis_buttons.find(button_ID) != pull_axis_buttons.cend())
		return;

	pull_axis_buttons.insert(button_ID);
	press_axis_buttons.erase(press_axis_buttons.find(button_ID));
}

void MyGamePad::SetAxisValue(const int & axis_ID, const float & value)
{
	if (axis.find(axis_ID) == axis.cend())
		return;

	if (value < 0.2f && value > -0.2f)
		axis.find(axis_ID)->second = 0.0f;
	else if (value >= 0.2f || value <= -0.2f)
		axis.find(axis_ID)->second = value;
}

float MyGamePad::GetAxisValue(const int &axis_ID)
{
	if (axis.find(axis_ID) == axis.cend())
		return 0.0f;

	return axis.find(axis_ID)->second;
}

bool MyGamePad::IsPushAxisButton(const  int & axis_button_ID)
{
	return push_axis_buttons.find(axis_button_ID) != push_axis_buttons.cend();
}

bool MyGamePad::IsPressAxisButton(const  int & axis_button_ID)
{
	return press_axis_buttons.find(axis_button_ID) != press_axis_buttons.cend();
}

bool MyGamePad::IsPullAxisButton(const  int & axis_button_ID)
{
	return pull_axis_buttons.find(axis_button_ID) != pull_axis_buttons.cend();
}

MyGamePad::MyGamePad()
{
	Setup();
}

MyGamePad::~MyGamePad()
{

}

void MyGamePad::FlushInput()
{
	if (push_axis_buttons.size() > 0)
		push_axis_buttons.clear();
	if (pull_axis_buttons.size() > 0)
		pull_axis_buttons.clear();
}

void MyGamePad::ShutDown()
{
	Gamepad_shutdown();
}

void MyGamePad::GamePadSetup()
{
	Gamepad_deviceAttachFunc(onDeviceAttached, (void *)0x1);
	Gamepad_deviceRemoveFunc(onDeviceRemoved, (void *)0x2);
	Gamepad_buttonDownFunc(onButtonDown, (void *)0x3);
	Gamepad_buttonUpFunc(onButtonUp, (void *)0x4);
	Gamepad_axisMoveFunc(onAxisMoved, (void *)0x5);
	Gamepad_init();
}

void MyGamePad::Setup()
{
	axis.insert(std::make_pair(AxisID::LEFT_AXIS_UP_DUWN, 0.0f));
	axis.insert(std::make_pair(AxisID::LEFT_AXIS_LEFT_RIGHT, 0.0f));
	axis.insert(std::make_pair(AxisID::RIGHT_AXIS_UP_DOWN, 0.0f));
	axis.insert(std::make_pair(AxisID::RIGHT_AXIS_LEFT_RIGHT, 0.0f));
	axis.insert(std::make_pair(AxisID::CROSS_AXIS_LEFT_RIGHT, 0.0f));
	axis.insert(std::make_pair(AxisID::CROSS_AXIS_UP_DOWN, 0.0f));
}

#define POLL_ITERATION_INTERVAL 30

void MyGamePad::Update()
{
	static unsigned int iterationsToNextPoll = POLL_ITERATION_INTERVAL;

	iterationsToNextPoll--;
	if (iterationsToNextPoll == 0) {
		Gamepad_detectDevices();
		iterationsToNextPoll = POLL_ITERATION_INTERVAL;
	}

	Gamepad_processEvents();
}






void onButtonDown(struct Gamepad_device * device, unsigned int buttonID, double timestamp, void * context)
{
	GamePad.SetPushAxisButtons(buttonID);
	GamePad.SetPressAxisButtons(buttonID);
}

void onButtonUp(struct Gamepad_device * device, unsigned int buttonID, double timestamp, void * context)
{
	GamePad.SetPullAxisButtons(buttonID);
}

void onAxisMoved(struct Gamepad_device * device, unsigned int axisID, float value, float lastValue, double timestamp, void * context)
{
	GamePad.SetAxisValue(axisID, value);
}

void onDeviceAttached(struct Gamepad_device * device, void * context)
{
	if (verbose)
	{
		console() << "Device ID " << device->deviceID << " attached (vendor = " << device->vendorID << "; product = " << device->productID << ") with context" << context << std::endl;
	}
}

void onDeviceRemoved(struct Gamepad_device * device, void * context)
{
	if (verbose)
	{
		console() << "Device ID " << device->deviceID << " removed with context " << context << std::endl;
	}
}