#include "MainCamera.h"
#include "../../../Utility/Input/Key/Key.h"
#include "../../../Utility/Input/Mouse/Mouse.h"
#include "../../../Utility/Manager/TimeManager/TimeManager.h"
#include "../../../Utility/Manager/EasingManager/EasingManager.h"
#include "../../../Utility/Utility.h"
#include <cinder/Ray.h>
#include <cinder/app/App.h>

MainCamera::MainCamera() :
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
	max_rotate_angle(static_cast<float>(M_PI) / 2.0f),
	is_rotating(false)
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
	transform.pos = GetVec3f(params["start_pos"]);
	transform.angle = GetVec3f(params["angle"]);
	rotate_take_time = params.getValueForKey<float>("rotate_take_time");
	max_rotate_angle = static_cast<float>(M_PI) * (params.getValueForKey<float>("max_rotate_angle") / 180.0f);
	move_speed = params.getValueForKey<float>("move_speed");

	camera_persp = ci::CameraPersp(ci::app::getWindowWidth(),
		ci::app::getWindowHeight(),
		params.getValueForKey<float>("fov"),
		params.getValueForKey<float>("near_plane"),
		params.getValueForKey<float>("far_plane"));

	interest_point = 1.0f * ci::Vec3f(
		sin(transform.angle.y) * cos(transform.angle.x),
		sin(transform.angle.x),
		cos(transform.angle.y) * cos(transform.angle.x));

	camera_persp.setEyePoint(transform.pos);
	camera_persp.setCenterOfInterestPoint(transform.pos + interest_point);
}

void MainCamera::Update()
{
	Move();

	ci::app::console() << camera_persp.getEyePoint() << std::endl;
}

void MainCamera::Draw()
{
	camera_persp.setEyePoint(transform.pos);
	camera_persp.setCenterOfInterestPoint(transform.pos + interest_point);
	ci::gl::setMatrices(camera_persp);
}

ci::Ray MainCamera::CreateRayCameraToMouse()
{
	// マウス座標を(0,0)~(1,1)の範囲に正規化する
	//		マウスの座標はYの下方向がプラス
	//      表示座標はYの上方向がプラス
	//      向きが逆なので、補正します
	ci::Vec2f mouse_pos_window_ratio = ci::Vec2f(
		static_cast<float>(Mouse::Get().GetMousePosition().x) / ci::app::getWindowSize().x,
		1.0f - static_cast<float>(Mouse::Get().GetMousePosition().y) / ci::app::getWindowSize().y);

	ci::Ray ray = camera_persp.generateRay(
		mouse_pos_window_ratio.x,
		mouse_pos_window_ratio.y,
		ci::app::getWindowAspectRatio());

	return ray;
}

void MainCamera::StartMoving(const ci::Vec3f & target_pos, const float & end_distance, const float & delay_time, const float & take_time)
{
	ci::Vec3f move_start_pos = target_pos + interest_point * end_distance;

	EasingManager::Get().Register(
		&(transform.pos.x),
		EasingManager::EasingType::BACKOUT,
		delay_time, take_time,
		move_start_pos.x, transform.pos.x);
	EasingManager::Get().Register(
		&(transform.pos.y),
		EasingManager::EasingType::BACKOUT,
		delay_time, take_time,
		move_start_pos.y, transform.pos.y);
	EasingManager::Get().Register(
		&(transform.pos.z),
		EasingManager::EasingType::BACKOUT,
		delay_time, take_time,
		move_start_pos.z, transform.pos.z);	
}

void MainCamera::EndMoving(const ci::Vec3f & target_pos,
	const float &end_distance,
	const float & delay_time,
	const float & take_time)
{
	ci::Vec3f move_end_pos = target_pos + interest_point * end_distance;

	EasingManager::Get().Register(
		&(transform.pos.x),
		EasingManager::EasingType::BACKOUT,
		delay_time, take_time,
		transform.pos.x, move_end_pos.x);
	EasingManager::Get().Register(
		&(transform.pos.y),
		EasingManager::EasingType::BACKOUT,
		delay_time, take_time,
		transform.pos.y, move_end_pos.y);
	EasingManager::Get().Register(
		&(transform.pos.z),
		EasingManager::EasingType::BACKOUT,
		delay_time, take_time,
		transform.pos.z, move_end_pos.z);
}

void MainCamera::Move()
{
	ci::Vec3f move_vec;
	if (Key::Get().IsPressKey(ci::app::KeyEvent::KEY_d))
	{
		move_vec -= move_speed * ci::Vec3f(
			cos(transform.angle.y) * cos(transform.angle.x),
			0.0f,
			-sin(transform.angle.y) * cos(transform.angle.x));
	}
	if (Key::Get().IsPressKey(ci::app::KeyEvent::KEY_a))
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
		if (Key::Get().IsPressKey(ci::app::KeyEvent::KEY_s))
		{
			move_vec -= move_speed * ci::Vec3f(
				sin(transform.angle.y) * cos(transform.angle.x),
				0.0f,
				cos(transform.angle.y) * cos(transform.angle.x)
			);
		}
		if (Key::Get().IsPressKey(ci::app::KeyEvent::KEY_w))
		{
			move_vec += move_speed *ci::Vec3f(
				sin(transform.angle.y) * cos(transform.angle.x),
				0.0f,
				cos(transform.angle.y) * cos(transform.angle.x)
			);
		}
	}

	transform.pos += move_vec;
	camera_persp.setEyePoint(transform.pos);
	camera_persp.setCenterOfInterestPoint(transform.pos + interest_point);
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