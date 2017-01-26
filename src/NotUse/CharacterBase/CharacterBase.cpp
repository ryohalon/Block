#include "CharacterBase.h"

void CharacterBase::UpdateStatus()
{
	Roll();
	Attack();
	Clash();
	Interval();

	Move();
}

void CharacterBase::Move()
{
	move_count += TimeManager::Get().GetDeltaTime() / move_take_time;
	if (move_count >= 1.0f)
		move_count = 1.0f;

	ci::Vec2f move_pos = Easing::QuadOut(move_count, start_move_pos, end_move_pos);
	transform.position = ci::Vec3f(move_pos.x, move_pos.y, transform.position.z);
}

void CharacterBase::Roll()
{
	if (roll_count == 1.0f)
		return;

	roll_count += TimeManager::Get().GetDeltaTime() / roll_take_time;
	if (roll_count >= 1.0f)
	{
		roll_count = 1.0f;
		status = Status::NORMAL;
	}

	transform.angle.z = Easing::QuadOut(roll_count, start_roll_angle, end_roll_angle);
}

void CharacterBase::Attack()
{
	if (status != Status::ATTACK)
		return;

	attack_count += TimeManager::Get().GetDeltaTime() / attack_take_time;
	if (attack_count >= 1.0f)
	{
		attack_count = 1.0f;
		status = Status::NORMAL;
	}

	speed = Easing::QuadOut(attack_count, start_attack_speed, end_attack_speed);
}

void CharacterBase::Clash()
{
	if (status != Status::CLASH)
		return;

	clash_count += TimeManager::Get().GetDeltaTime() / clash_take_time;
	if (clash_count >= 1.0f)
	{
		clash_count = 1.0f;
		status = Status::NORMAL;
	}

	transform.angle.z = std::sin(clash_count
		* clash_take_time * static_cast<float>(M_PI) * 4.0f)
		* static_cast<float>(M_PI) / 4.0f;
}

void CharacterBase::Interval()
{
	if (interval_count >= 1.0f)
		return;

	interval_count += TimeManager::Get().GetDeltaTime() / interval_take_time;
	if (interval_count >= 1.0f)
		interval_count = 1.0f;
}

bool CharacterBase::IsRoll(const ci::Vec2f &target_pos)
{
	if (status != Status::NORMAL)
		return false;

	status = Status::ROLL;
	move_count = 0.0f;
	roll_count = 0.0f;

	end_roll_angle = (transform.position.x < target_pos.x) ?
		-max_roll_angle :
		max_roll_angle;

	start_move_pos = transform.position.xy();
	end_move_pos = target_pos;

	return true;
}

bool CharacterBase::IsAttack(const ci::Vec2f &target_pos)
{
	if (status != Status::NORMAL)
		return false;
	if (!IsAction())
		return false;

	status = Status::ATTACK;
	clash_count = 0.0f;
	interval_count = 0.0f;

	roll_count = 0.0f;
	end_roll_angle = -max_roll_angle;

	if (target_pos != ci::Vec2f::zero())
	{
		move_count = 0.0f;
		start_move_pos = transform.position.xy();
		end_move_pos = target_pos;
	}

	return true;
}

bool CharacterBase::IsMove(const ci::Vec2f &target_pos)
{
	if (status != Status::NORMAL)
		return false;

	move_count = 0.0f;
	start_move_pos = transform.position.xy();
	end_move_pos = target_pos;

	return false;
}

void CharacterBase::Clashed()
{
	if (clash_count < 1.0f)
		return;

	status = Status::CLASH;
	speed = clash_speed;
	clash_count = 0.0f;
	roll_count = 1.0f;
	move_count = 0.0f;
	start_move_pos = transform.position.xy();
	end_move_pos = transform.position.xy();
}

CharacterBase::CharacterBase() :
	status(Status::NORMAL),
	speed(1.0f),
	move_count(0.0f),
	move_take_time(1.0f),
	start_move_pos(transform.position.xy()),
	end_move_pos(transform.position.xy()),
	roll_count(0.0f),
	roll_take_time(1.0f),
	start_roll_angle(0.0f),
	end_roll_angle(0.0f),
	max_roll_angle((float)M_PI * 2.0f * 3.0f),
	attack_count(0.0f),
	attack_take_time(1.0f),
	start_attack_speed(1.0f),
	end_attack_speed(1.0f),
	clash_count(0.0f),
	clash_take_time(1.0f),
	clash_speed(1.0f),
	interval_count(0.0f),
	interval_take_time(1.0f)
{

}

CharacterBase::~CharacterBase()
{

}

void CharacterBase::Setup()
{

}

void CharacterBase::Setup(const float &speed_,
	const float & move_take_time_,
	const float & roll_take_time_,
	const float & max_roll_angle_,
	const float & attack_take_time_,
	const float & start_attack_speed_,
	const float & clash_take_time_,
	const float & clash_speed_,
	const float & interval_take_time_)
{
	status = Status::NORMAL;
	speed = speed_;
	move_count = 0.0f;
	move_take_time = move_take_time_;
	start_move_pos = transform.position.xy();
	end_move_pos = transform.position.xy();
	roll_count = 1.0f;
	roll_take_time = roll_take_time_;
	start_roll_angle = 0.0f;
	end_roll_angle = 0.0f;
	max_roll_angle = max_roll_angle_;
	attack_count = 1.0f;
	attack_take_time = attack_take_time_;
	start_attack_speed = start_attack_speed_;
	end_attack_speed = speed_;
	clash_count = 0.0f;
	clash_take_time = clash_take_time_;
	clash_speed = clash_speed_;
	interval_count = 1.0f;
	interval_take_time = interval_take_time_;
}
