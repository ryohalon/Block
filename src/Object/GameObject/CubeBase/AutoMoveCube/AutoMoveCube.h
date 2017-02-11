#pragma once
#include "../CubeBase.h"



class AutoMoveCube : public CubeBase
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

	AutoMoveCube();
	AutoMoveCube(const ci::Vec3f &pos,
		const ci::Vec3f &angle,
		const ci::Vec3f &scale,
		const ci::gl::Material &material,
		const ci::Vec3i &map_pos,
		const float &take_time,
		const MoveDirection &move_direction);
	~AutoMoveCube();

	void Setup() override;
	void Setup(const ci::JsonTree &params) override;
	void Update() override;
	void Draw() override;

	void Hit();
	void FallStart();

private:

	// 移動先を決める
	void MoveStart();
	// 移動中
	void Moving();
	// 移動先の変更 : 時計周り
	void ChangeMoveDirection();

	ci::Vec3f start_pos, end_pos;
	ci::Quatf now_quat, rotating_quat;
	// 使っていない
	ci::Quatf prev_quat;
	float rotate_angle;
	float time, take_time;
	bool is_move, is_moving,
		is_fall, is_falling;
	MoveDirection move_direction, next_direction;
	ci::Matrix44f rotate_axis;
};