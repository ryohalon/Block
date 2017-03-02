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
	
	// 落ちるときに呼ぶ関数
	// fall_pos : 落ちる座標
	void FallStart(const ci::Vec3f &fall_pos);

	// 移動先の変更 : 時計周り
	void ChangeMoveDirection();

	// ほかのキューブにぶつかったときの関数
	void Hit();

private:

	void UpdateAction();

	// 落下中
	void Falling(const float &time_);

	float fall_take_time;
	bool is_falling;
};