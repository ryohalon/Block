#pragma once
#include <cinder/Camera.h>
#include "../GameObject.h"

namespace cinder {
	class Ray;
}


class MainCamera : public GameObject
{
public:

	MainCamera();
	~MainCamera();

	const ci::CameraPersp& GetCamera() const { return camera_persp; }
	void SetInterestPoint(const ci::Vec3f &interest_point_) { interest_point = interest_point_; }
	void SetMapCenterPos(const ci::Vec3f &map_cneter_pos_) { map_cneter_pos = map_cneter_pos_; }
	void SetMoveRange(const ci::Vec3f &move_range_) { move_range = move_range_; }

	void Setup() override;
	void Setup(const ci::JsonTree &params) override;
	void Update() override;
	void Draw() override;

	ci::Ray CreateRayCameraToMouse();
	void StartMoving(const ci::Vec3f &target_pos,
		const float &end_distance,
		const float &delay_time,
		const float &take_time);
	void EndMoving(const ci::Vec3f &target_pos,
		const float &end_distance,
		const float &delay_time,
		const float &take_time);

private:

	void Move();
	void RotateStart();
	

	ci::Vec3f map_cneter_pos,
		move_range;
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