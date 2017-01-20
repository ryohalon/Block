#pragma once
#include "../GameObject.h"



class AutoMoveCube : public GameObject
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
	~AutoMoveCube();

	void Setup() override;
	void Update() override;
	void Draw() override;

private:

	// �ړ�������߂�
	void MoveStart();
	// �ړ���
	void Moving();
	// �ړ���̕ύX : ���v����
	void ChangeMoveDirection();

	ci::Vec3f start_pos, end_pos;
	ci::Quatf now_quat, prev_quat;
	float rotate_angle;
	float time, take_time;
	bool is_moving;
	MoveDirection move_direction;
};