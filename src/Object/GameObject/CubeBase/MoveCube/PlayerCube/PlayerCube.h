#pragma once
#include "../MoveCube.h"



class PlayerCube : public MoveCube
{
public:

	PlayerCube();
	PlayerCube(const MoveCube &move_cube,
		const float &fall_take_time);
	~PlayerCube();

	bool GetIsFalling() const { return is_falling; }

	void Setup() override;
	void Setup(const ci::JsonTree &params) override;
	void Update() override;
	
	// ������Ƃ��ɌĂԊ֐�
	// fall_pos : ��������W
	void FallStart(const ci::Vec3f &fall_pos);

	// �ړ���̕ύX : ���v����
	void ChangeMoveDirection();

	// �ق��̃L���[�u�ɂԂ������Ƃ��̊֐�
	void Hit();

private:

	void UpdateAction();

	// ������
	void Falling(const float &time_);

	float fall_take_time;
	bool is_falling;
};