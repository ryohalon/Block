#pragma once
#include "../CharacterBase.h"
#include "../../../../Utillity/Input/LeapMotion/LeapController/LeapController.h"
#include "../../../../Utillity/Input/Key/Key.h"



class Player : public CharacterBase
{
private:

	enum class OperationType
	{
		LEAP,
		KEY
	};
	OperationType operation_type;

	float hand_exist_count;
	float hand_exist_take_time;
	ci::Vec2f hand_pos_by_ratio;
	int interval_time;

	ci::Vec3f prev_hand_pos;
	ci::Vec2f prev_hand_pos_by_ratio;
	ci::Vec3f prev_hand_normal;

	ci::Vec2f move_range;

	float start_delay_time;
	float start_delay_take_time;

	float course_rad;

	// rollで使う範囲指定の変数
	float min_hand_normal_z_range;
	float max_hand_normal_z_range;
	float min_hand_normal_xy_range;
	float max_hand_normal_xy_range;
	float min_dot_product_range;
	float max_dot_product_range;

	// dashで使う範囲指定の変数
	float dash_range;

	void UpdateLeap();
	void ChangeMovePos();
	bool StartDelay();
	void HandNormalRotation();
	void HandPosZDistance();

	void CollisionPlayerToCourse();

	void ChangeOperationType();

public:

	ci::Vec3f GetWorldPosition() const { return matrix * ci::Vec3f::zero(); }

public:

	Player();
	~Player();

	void Setup() override;
	void Setup(const float &hand_exist_take_time_,
		const int &interval_time_,
		const ci::Vec2f &move_range_,
		const float &start_delay_take_time_,
		const float &course_rad_,
		const float &min_hand_normal_z_range_,
		const float &max_hand_normal_z_range_,
		const float &min_hand_normal_xy_range_,
		const float &max_hand_normal_xy_range_,
		const float &min_dot_product_range_,
		const float &max_dot_product_range_,
		const float &dash_range_);
	void Update() override;
	void Draw() override;
};