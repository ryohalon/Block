#include "MainCamera.h"
#include "../../../Utility/Input/Key/Key.h"
#include "../../../Utility/Input/Mouse/Mouse.h"
#include "../../../Utility/Manager/TimeManager/TimeManager.h"
#include "../../../Utility/Manager/EasingManager/Easing/Easing.h"
#include "../../../Utility/Utility.h"

MainCamera::MainCamera() :
	GameObject(),
	camera_persp(ci::CameraPersp(ci::app::getWindowWidth(),
		ci::app::getWindowHeight(),
		60.0f,
		0.1f,
		1000.0f)),
	interest_point(ci::Vec3f(0.0f, 0.0f, 0.0f)),
	move_speed(1.0f),
	time(0.0f),
	rotate_take_time(1.0f),
	start_rotate_angle(0.0f),
	end_rotate_angle(0.0f),
	max_rotate_angle(M_PI / 2.0f),
	is_rotating(false),
	camera_distance(10.0f)
{

}

MainCamera::~MainCamera()
{

}

void MainCamera::Setup()
{

}

void MainCamera::Setup(const ci::JsonTree & params)
{
	transform.angle = GetVec3f(params["start_angle"]);
	rotate_take_time = params.getValueForKey<float>("rotate_take_time");
	max_rotate_angle = M_PI * (params.getValueForKey<float>("max_rotate_angle") / 180.0f);
	move_speed = params.getValueForKey<float>("move_speed");
	camera_distance = params.getValueForKey<float>("camera_distance");

	camera_persp = ci::CameraPersp(ci::app::getWindowWidth(),
		ci::app::getWindowHeight(),
		params.getValueForKey<float>("fov"),
		params.getValueForKey<float>("near_plane"),
		params.getValueForKey<float>("far_plane"));

	transform.pos = camera_distance * ci::Vec3f(
		sin(transform.angle.y) * cos(transform.angle.x),
		sin(transform.angle.x),
		cos(transform.angle.y) * cos(transform.angle.x));

	camera_persp.setEyePoint(interest_point + transform.pos);
	camera_persp.setCenterOfInterestPoint(interest_point);
}

void MainCamera::Update()
{
	Move();
	/*Rotating();

	if (Key::Get().IsPushKey(ci::app::KeyEvent::KEY_q) ||
		Key::Get().IsPushKey(ci::app::KeyEvent::KEY_e))
	{
		RotateStart();
	}*/
}

void MainCamera::Draw()
{
	ci::gl::setMatrices(camera_persp);
}

void MainCamera::Move()
{
	ci::Vec3f move_vec;
	if (Key::Get().IsPressKey(ci::app::KeyEvent::KEY_a))
	{
		move_vec -= move_speed * ci::Vec3f(
			cos(transform.angle.y) * cos(transform.angle.x),
			0.0f,
			-sin(transform.angle.y) * cos(transform.angle.x));
	}
	if (Key::Get().IsPressKey(ci::app::KeyEvent::KEY_d))
	{
		move_vec += move_speed * ci::Vec3f(
			cos(transform.angle.y) * cos(transform.angle.x),
			0.0f,
			-sin(transform.angle.y) * cos(transform.angle.x));
	}
	if (Mouse::Get().IsPressButton(ci::app::MouseEvent::RIGHT_DOWN))
	{
		if (Key::Get().IsPressKey(ci::app::KeyEvent::KEY_w))
			move_vec.y += move_speed;
		if (Key::Get().IsPressKey(ci::app::KeyEvent::KEY_s))
			move_vec.y -= move_speed;
	}
	else
	{
		if (Key::Get().IsPressKey(ci::app::KeyEvent::KEY_w))
		{
			move_vec -= move_speed * ci::Vec3f(
				sin(transform.angle.y) * cos(transform.angle.x),
				0.0f,
				cos(transform.angle.y) * cos(transform.angle.x)
			);
		}
		if (Key::Get().IsPressKey(ci::app::KeyEvent::KEY_s))
		{
			move_vec += move_speed *ci::Vec3f(
				sin(transform.angle.y) * cos(transform.angle.x),
				0.0f,
				cos(transform.angle.y) * cos(transform.angle.x)
			);
		}
	}

	interest_point += move_vec;
	camera_persp.setEyePoint(interest_point + transform.pos);
	camera_persp.setCenterOfInterestPoint(interest_point);
}

void MainCamera::RotateStart()
{
	start_rotate_angle = transform.angle.y;

	if (Key::Get().IsPushKey(ci::app::KeyEvent::KEY_q))
		end_rotate_angle = transform.angle.y - max_rotate_angle;
	else if (Key::Get().IsPushKey(ci::app::KeyEvent::KEY_e))
		end_rotate_angle = transform.angle.y + max_rotate_angle;

	time = 0.0f;
	is_rotating = true;
}

void MainCamera::Rotating()
{
	if (!is_rotating)
		return;

	time = std::min(1.0f, TimeManager::Get().GetDeltaTime() / rotate_take_time + time);
	transform.angle.y = Easing::Linear(time, start_rotate_angle, end_rotate_angle);

	transform.pos = camera_distance * ci::Vec3f(
		sin(transform.angle.y) * cos(transform.angle.x),
		sin(transform.angle.x),
		cos(transform.angle.y) * cos(transform.angle.x));

	camera_persp.setEyePoint(interest_point + transform.pos);

	if (time < 1.0f)
		return;

	time = 0.0f;
	is_rotating = false;
}