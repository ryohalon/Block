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
		const float &move_take_time,
		const float &fall_take_time,
		const MoveDirection &move_direction);
	~AutoMoveCube();

	bool GetIsMoving() const { return is_moving; }
	bool GetIsFalling() const { return is_falling; }
	MoveDirection GetMoveDirection() const { return next_direction; }

	void Setup() override;
	void Setup(const ci::JsonTree &params) override;
	void Update() override;
	void Draw() override;

	// �ړ�������߂�
	void MoveStart();

	// ������Ƃ��ɌĂԊ֐�
	// fall_pos : ��������W
	void FallStart(const ci::Vec3f &fall_pos);

	// �ړ���̕ύX : ���v����
	void ChangeMoveDirection();

	// �ق��̃L���[�u�ɂԂ������Ƃ��̊֐�
	void Hit();

private:

	
	void UpdateAction();
	// �ړ���
	void Moving(const float &time_);
	// ������
	void Falling(const float &time_);

	ci::Vec3f start_pos, end_pos;
	ci::Quatf now_quat, rotating_quat;
	// �g���Ă��Ȃ�
	ci::Quatf prev_quat;
	float rotate_angle;
	float time, take_time,
		move_take_time, fall_take_time;
	bool is_moving, is_falling;
	MoveDirection move_direction, next_direction;
	ci::Matrix44f rotate_axis;
};