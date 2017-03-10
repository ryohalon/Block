#pragma once
#include "../CubeBase.h"


class MoveCube : public CubeBase
{
public:

	enum class MoveDirection
	{
		FRONT,
		RIGHT,
		BACK,
		LEFT,
		DIRECTIONNUM
	};

	MoveCube();
	MoveCube(const CubeBase &cube_base,
		const float &move_take_time,
		const MoveDirection &move_direction);
	virtual ~MoveCube();

	bool GetIsMoving() const { return is_moving; }
	MoveDirection GetMoveDirection() const { return next_direction; }

	virtual void Setup() override;
	virtual void Setup(const ci::JsonTree &params) override;
	virtual void Update() override;
	virtual void Draw() override;

	// 移動スタート
	void StartMotion();

protected:

	// 移動中
	void Moving(const float &time_);

	ci::Vec3f start_pos, end_pos;
	ci::Quatf now_quat, rotating_quat;
	float rotate_angle;
	float time, take_time;
	float move_take_time;
	bool is_moving;
	MoveDirection move_direction, next_direction;
	ci::Matrix44f rotate_axis;
};