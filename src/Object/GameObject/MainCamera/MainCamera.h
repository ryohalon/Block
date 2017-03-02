#pragma once
#include <cinder/Camera.h>
#include "../GameObject.h"



class MainCamera : public GameObject
{
public:

	MainCamera();
	~MainCamera();

	const ci::CameraPersp& GetCamera() const { return camera_persp; }
	void SetInterestPoint(const ci::Vec3f &map_center_pos) { interest_point = map_center_pos; }

	void Setup() override;
	void Setup(const ci::JsonTree &params) override;
	void Update() override;
	void Draw() override;

private:

	void Move();
	void RotateStart();
	void Rotating();

	ci::CameraPersp camera_persp;
	ci::Vec3f interest_point;
	float move_speed;
	float time;
	float rotate_take_time;
	float start_rotate_angle,
		end_rotate_angle;
	float max_rotate_angle;
	bool is_rotating;
	float camera_distance;
};