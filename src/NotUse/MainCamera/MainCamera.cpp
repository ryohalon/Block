#include "MainCamera.h"

void MainCamera::ChangeMode()
{
	if (!Key::Get().IsPushKey(ci::app::KeyEvent::KEY_SPACE))
		return;

	operation_mode = (operation_mode == OperationMode::KEY_MODE) ?
		OperationMode::MOUSE_MODE : OperationMode::KEY_MODE;

	transform.position = maya_camera.getCamera().getEyePoint();
	ci::Vec3f center_of_interest_point = maya_camera.getCamera().getCenterOfInterestPoint() - transform.position;

	theta.x = asin(center_of_interest_point.y);
	theta.y;



}

void MainCamera::KeyMove()
{
	if (operation_mode != OperationMode::KEY_MODE)
		return;

	//////////////////////////////////////////////////////////////////////
	// sin,cosを使った移動の計算方法
	if (Key::Get().IsPressKey(ci::app::KeyEvent::KEY_a))
	{
		transform.position += move_speed * ci::Vec3f(
			cos(theta.y) * cos(theta.x),
			0.0f,
			-sin(theta.y) * cos(theta.x));
	}
	if (Key::Get().IsPressKey(ci::app::KeyEvent::KEY_d))
	{
		transform.position -= move_speed * ci::Vec3f(
			cos(theta.y) * cos(theta.x),
			0.0f,
			-sin(theta.y) * cos(theta.x));
	}
	if (Key::Get().IsPressKey(ci::app::KeyEvent::KEY_w))
	{
		transform.position += move_speed * ci::Vec3f(
			sin(theta.y) * cos(theta.x),
			sin(theta.x),
			cos(theta.y) * cos(theta.x)
		);
	}
	if (Key::Get().IsPressKey(ci::app::KeyEvent::KEY_s))
	{
		transform.position -= move_speed * ci::Vec3f(
			sin(theta.y) * cos(theta.x),
			sin(theta.x),
			cos(theta.y) * cos(theta.x)
		);
	}
	//////////////////////////////////////////////////////////////////////

	ci::CameraPersp camera_persp = maya_camera.getCamera();
	camera_persp.setEyePoint(transform.position);
	maya_camera.setCurrentCam(camera_persp);
}

void MainCamera::KeyRotate()
{
	if (operation_mode != OperationMode::KEY_MODE)
		return;

	//////////////////////////////////////////////////////////////////////
	// sin,cosを使ったFPS視点回転の計算方法
	if (Key::Get().IsPressKey(ci::app::KeyEvent::KEY_j))
		theta.y += rotate_speed.y;
	if (Key::Get().IsPressKey(ci::app::KeyEvent::KEY_l))
		theta.y -= rotate_speed.y;
	if (Key::Get().IsPressKey(ci::app::KeyEvent::KEY_i))
		theta.x = std::min(0.99f, theta.x + rotate_speed.x);
	if (Key::Get().IsPressKey(ci::app::KeyEvent::KEY_k))
		theta.x = std::max(-0.99f, theta.x - rotate_speed.x);

	eye_direction = 1.0f * ci::Vec3f(
		sin(theta.y) * cos(theta.x),
		sin(theta.x),
		cos(theta.y) * cos(theta.x));
	//////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////
	// matrixを使ったFPS視点回転の計算方法
	/*if (KEY.IsPressKey(ci::app::KeyEvent::KEY_j))
		theta.y += rotate_speed.y;
	if (KEY.IsPressKey(ci::app::KeyEvent::KEY_l))
		theta.y -= rotate_speed.y;
	if (KEY.IsPressKey(ci::app::KeyEvent::KEY_i))
		theta.x = std::max(-0.99f, theta.x - rotate_speed.x);
	if (KEY.IsPressKey(ci::app::KeyEvent::KEY_k))
		theta.x = std::min(0.99f, theta.x + rotate_speed.x);

	ci::Matrix44f mrotate = ci::Matrix44f::createRotation(ci::Vec3f(theta.x, theta.y, 0.0f));
	eye_direction = mrotate * ci::Vec3f::zAxis();*/
	//////////////////////////////////////////////////////////////////////

	ci::CameraPersp camera_persp = maya_camera.getCamera();
	camera_persp.setCenterOfInterestPoint(camera_persp.getEyePoint() + eye_direction);
	maya_camera.setCurrentCam(camera_persp);
}

void MainCamera::MouseMoveAndRotate()
{
	if (operation_mode != OperationMode::MOUSE_MODE)
		return;

	if (MOUSE.IsPushButton())
		maya_camera.mouseDown(MOUSE.GetMousePosition());

	maya_camera.mouseDrag(MOUSE.GetMousePosition(),
		MOUSE.IsPressButton(ci::app::MouseEvent::RIGHT_DOWN),
		MOUSE.IsPressButton(ci::app::MouseEvent::MIDDLE_DOWN),
		false);

	ci::CameraPersp camera_persp = maya_camera.getCamera();
	camera_persp.setEyePoint(camera_persp.getEyePoint() +
		camera_persp.getViewDirection() *
		MOUSE.GetMouseWheelValue());
	maya_camera.setCurrentCam(camera_persp);
}

void MainCamera::Reset()
{
	if (!Key::Get().IsPushKey(ci::app::KeyEvent::KEY_ESCAPE))
		return;

	ci::CameraPersp camera_persp;
	camera_persp.setEyePoint(ci::Vec3f(0.0f, 0.0f, -10.0f));
	camera_persp.setCenterOfInterestPoint(ci::Vec3f::zero());
	maya_camera.setCurrentCam(camera_persp);
}

MainCamera::MainCamera() :
	GameObject(),
	eye_direction(ci::Vec3f(0.0f, 0.0f, 1.0f)),
	move_speed(ci::Vec3f::one()),
	rotate_speed(ci::Vec2f(0.03f, 0.03f)),
	theta(ci::Vec2f::zero()),
	operation_mode(OperationMode::MOUSE_MODE)
{

}

MainCamera::~MainCamera()
{

}

void MainCamera::Setup()
{
	transform.position = ci::Vec3f(0.0f, 0.0f, -10.0f);
	ci::CameraPersp camera_persp;
	camera_persp.setEyePoint(transform.position);
	camera_persp.setCenterOfInterestPoint(camera_persp.getEyePoint()
		+ eye_direction);
	camera_persp.setPerspective(45.0f,
		ci::app::getWindowAspectRatio(),
		0.1f,
		2000.0f);

	maya_camera.setCurrentCam(camera_persp);
}

void MainCamera::Setup(const ci::Vec3f &pos,
	const ci::Vec3f &eye_direction,
	const float &view_angle,
	const float &near_plane,
	const float &far_plane)
{
	transform.position = pos;
	ci::CameraPersp camera_persp;
	camera_persp.setEyePoint(transform.position);

	this->eye_direction = eye_direction;
	camera_persp.setCenterOfInterestPoint(camera_persp.getEyePoint()
		+ this->eye_direction);

	camera_persp.setPerspective(view_angle,
		ci::app::getWindowAspectRatio(),
		near_plane,
		far_plane);

	maya_camera.setCurrentCam(camera_persp);
}

void MainCamera::Update()
{
	ChangeMode();

	KeyMove();
	KeyRotate();

	MouseMoveAndRotate();

	Reset();
}

void MainCamera::Draw()
{
	ci::gl::setMatrices(maya_camera.getCamera());
}
