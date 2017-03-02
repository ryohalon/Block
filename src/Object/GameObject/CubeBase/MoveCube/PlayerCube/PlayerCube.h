#pragma once
#include "../MoveCube.h"


class PlayerCube : public MoveCube
{
public:

	PlayerCube();
	PlayerCube(const ci::Vec3f &pos,
		const ci::Vec3f &angle,
		const ci::Vec3f &scale,
		const ci::gl::Material &material,
		const CubeType &type,
		const ci::Vec3i &map_pos,
		const float &move_take_time,
		const float &fall_take_time,
		const MoveDirection &move_direction);
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