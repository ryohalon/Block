#include "PlayerCube.h"
#include "../../../../../Utility/Manager/EasingManager/Easing/Easing.h"
#include "../../../../../Utility/Manager/TimeManager/TimeManager.h"
#include "../../../../../Utility/Utility.h"

PlayerCube::PlayerCube() :
	MoveCube(),
	fall_take_time(1.0f),
	is_falling(false)
{

}

PlayerCube::PlayerCube(const ci::Vec3f & pos,
	const ci::Vec3f & angle,
	const ci::Vec3f & scale,
	const ci::gl::Material & material,
	const CubeType & type,
	const ci::Vec3i & map_pos,
	const float & move_take_time,
	const float & fall_take_time,
	const MoveDirection & move_direction) :
	MoveCube(pos, angle, scale, material, type, map_pos, move_take_time, move_direction),
	fall_take_time(1.0f)
{

}

PlayerCube::~PlayerCube()
{
}

void PlayerCube::Setup()
{
}

void PlayerCube::Setup(const ci::JsonTree & params)
{
	move_take_time = params.getValueForKey<float>("move_take_time");
	fall_take_time = params.getValueForKey<float>("fall_take_time");
	move_direction = static_cast<MoveDirection>(params.getValueForKey<int>("start_move_direction"));
	transform.pos = ci::Vec3f(
		static_cast<float>(map_pos.x) * transform.scale.x,
		static_cast<float>(map_pos.y) * transform.scale.y,
		static_cast<float>(map_pos.z) * transform.scale.z);
}

void PlayerCube::Update()
{
	UpdateAction();
}

void PlayerCube::FallStart(const ci::Vec3f &fall_pos)
{
	if (!is_stop)
		return;
	if (is_falling)
		return;
	if (is_moving)
		return;

	start_pos = transform.pos;
	end_pos = fall_pos;
	map_pos.y = static_cast<int>(end_pos.y / transform.scale.y);
	// —‚¿‚é”•ª•b”‚ğL‚Î‚·
	take_time = fall_take_time * (start_pos.y - end_pos.y);
	is_falling = true;

	// —‚¿‚é‰¹‚ÌÄ¶
	// –¢À‘•
}

void PlayerCube::ChangeMoveDirection()
{
	next_direction = static_cast<MoveDirection>(
		(static_cast<int>(next_direction) + 1)
		% static_cast<int>(MoveDirection::DIRECTIONNUM));
}

void PlayerCube::Hit()
{
	// ƒ‚ƒm‚É‚Ô‚Â‚©‚Á‚½‚ÌÕ“Ë‰¹‚ÌÄ¶
	// –¢À‘•

	// ˆÚ“®•ûŒü•ÏX
	ChangeMoveDirection();
}

void PlayerCube::UpdateAction()
{
	if (!is_stop)
		return;

	time = std::min(1.0f, TimeManager::Get().GetDeltaTime() / take_time + time);
	float time_ = Easing::CubicIn(time, 0.0f, 1.0f);

	if (is_moving)
		Moving(time_);
	if (is_falling)
		Falling(time_);
}

void PlayerCube::Falling(const float & time_)
{
	if (!is_falling)
		return;

	transform.pos = ci::lerp(start_pos, end_pos, time_);

	if (time < 1.0f)
		return;

	time = 0.0f;
	is_falling = false;
}
