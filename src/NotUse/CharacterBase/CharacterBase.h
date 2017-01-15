#pragma once
#include "../GameObject.h"
#include "../../../Utillity/Manager/EasingManager/Easing/Easing.h"
#include "../../../Utillity/Manager/TimeManager/TimeManager.h"



class CharacterBase : public GameObject
{
public:

	enum class Status
	{
		NORMAL,
		ROLL,
		ATTACK,
		CLASH
	};

protected:

	ci::Matrix44f stage_matrix;

	Status status;
	float speed;

	float move_count;
	float move_take_time;
	ci::Vec2f start_move_pos;
	ci::Vec2f end_move_pos;

	float roll_count;
	float roll_take_time;
	float start_roll_angle;
	float end_roll_angle;
	float max_roll_angle;

	float attack_count;
	float attack_take_time;
	float start_attack_speed;
	float end_attack_speed;

	float clash_count;
	float clash_take_time;
	float clash_speed;

	float interval_count;
	float interval_take_time;

protected:

	void UpdateStatus();
	void Move();
	void Roll();
	void Attack();
	void Clash();
	void Interval();

public:

	float GetSpeed() const { return speed; }
	Status GetStatus() const { return status; }
	float GetAttackCount() const { return attack_count; }
	float GetIntervalCount() const { return interval_count; }


	void SetSpeed(const float speed_) { speed = speed_; }
	void SetStatus(const Status status_) { status = status_; }

	bool IsAction() const { return interval_count == 1.0f; }
	bool IsAttacking() const { return status == Status::ATTACK; }
	bool IsRolling() const { return status == Status::ROLL; }
	bool IsInvincible()
	{
		switch (status)
		{
		case Status::CLASH:
			return clash_count < 1.0f;
		case Status::ROLL:
			return roll_count < 1.0f;
		}

		return false;
	}

	bool IsRoll(const ci::Vec2f &target_pos);
	bool IsAttack(const ci::Vec2f &target_pos = ci::Vec2f::zero());
	bool IsMove(const ci::Vec2f &target_pos);

	void Clashed();

public:

	CharacterBase();
	~CharacterBase();

	virtual void Setup() override;
	void Setup(const float &speed_,
		const float &move_take_time_,
		const float &roll_take_time_,
		const float &max_roll_angle_,
		const float &attack_take_time_,
		const float &start_attack_speed_,
		const float &clash_take_time_,
		const float &clash_speed_,
		const float &interval_take_time_);
	virtual void Update() override = 0;
	virtual void Draw() override = 0;
};