#pragma once
#include "cinder/Camera.h"
#include "cinder/MayaCamUI.h"
#include "../GameObject.h"
#include "../../../Utillity/Input/Mouse/Mouse.h"
#include "../../../Utillity/Input/Key/Key.h"


class MainCamera : public GameObject
{
private:

	ci::MayaCamUI maya_camera;

	ci::Vec3f eye_direction;
	ci::Vec3f move_speed;
	ci::Vec2f rotate_speed;
	ci::Vec2f theta;

	enum class OperationMode
	{
		KEY_MODE,
		MOUSE_MODE
	};
	OperationMode operation_mode;

	void ChangeMode();

	void KeyMove();
	void KeyRotate();

	void MouseMoveAndRotate();

	void Reset();

public:

	MainCamera();
	~MainCamera();

	void SetEyeDirection(const ci::Vec3f &eye_direction) { this->eye_direction = eye_direction; }
	void SetMoveSpeed(const ci::Vec3f &move_speed) { this->move_speed = move_speed; }
	void SetRotateSpeed(const ci::Vec2f &rotate_speed) { this->rotate_speed = rotate_speed; }
	void SetTheta(const ci::Vec2f &theta) { this->theta = theta; }

	void Setup() override;
	void Setup(const ci::Vec3f &pos,
		const ci::Vec3f &eye_direction,
		const float &view_angle,
		const float &near_plane,
		const float &far_plane);
	void Update() override;
	void Draw() override;
};