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
		const float &take_time,
		const MoveDirection &move_direction);
	~AutoMoveCube();

	void Setup() override;
	void Setup(const ci::JsonTree &json);
	void Update() override;
	void Draw() override;

private:

	// ˆÚ“®æ‚ğŒˆ‚ß‚é
	void MoveStart();
	// ˆÚ“®’†
	void Moving();
	// ˆÚ“®æ‚Ì•ÏX : Œvü‚è
	void ChangeMoveDirection();

	ci::Vec3f start_pos, end_pos;
	ci::Quatf now_quat, prev_quat;
	float rotate_angle;
	float time, take_time;
	bool is_move, is_moving;
	MoveDirection move_direction;
};