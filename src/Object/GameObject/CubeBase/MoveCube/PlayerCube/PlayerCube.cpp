#include "PlayerCube.h"
#include "../../../../../Utility/Manager/EasingManager/Easing/Easing.h"
#include "../../../../../Utility/Manager/TimeManager/TimeManager.h"
#include "../../../../../Utility/Utility.h"

PlayerCube::PlayerCube() :
	fall_take_time(1.0f),
	is_falling(false)
{

}

PlayerCube::PlayerCube(const MoveCube & move_cube,
	const float & fall_take_time) :
	MoveCube(move_cube),
	fall_take_time(fall_take_time),
	is_falling(false)
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
	// óéÇøÇÈêîï™ïbêîÇêLÇŒÇ∑
	take_time = fall_take_time * (start_pos.y - end_pos.y);
	is_falling = true;

	SoundManager::Get().GetSound("Fall").Play();
}

void PlayerCube::ChangeMoveDirection()
{
	next_direction = static_cast<MoveDirection>(
		(static_cast<int>(next_direction) + 1)
		% static_cast<int>(MoveDirection::DIRECTIONNUM));
}

void PlayerCube::Hit()
{
	ChangeMoveDirection();

	SoundManager::Get().GetSound("Crash").Play();
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
	SoundManager::Get().GetSound("Fall").Stop();
}
