#pragma once
#include "../Easing/Easing.h"
#include "../../TimeManager/TimeManager.h"


class EasingManageOne
{
public:

	EasingManageOne() :
		easing_func(Easing::Linear),
		time(0.0f),
		delay_time(0.0f),
		take_time(1.0f),
		start_value(0.0f),
		terget_value(0.0f),
		end_value(0.0f),
		is_active(true),
		is_end(false)
	{};
	EasingManageOne(const std::function<const float&(float, float, float)> &easing_func,
		const float &delay_time,
		const float &take_time,
		float &start_value,
		const float &end_value) :
		easing_func(easing_func),
		time(0.0f),
		delay_time(delay_time),
		take_time(take_time),
		start_value(start_value),
		terget_value(start_value),
		end_value(end_value),
		is_active(true),
		is_end(false)
	{};
	~EasingManageOne() {};

	bool GetIsEnd() const { return is_end; }
	float GetTime() const { return time; }
	float GetTakeTime() const { return take_time; }
	bool GetIsActive() const { return is_active; }

	void SetTime(const float &time_) { time = time_; }
	void SetIsActive(const bool &is_active) { this->is_active = is_active; }

	void EasingEnd() { time = delay_time + take_time; }

	void Update()
	{
		if (!is_active)
			return;
		if (is_end)
			return;

		time += TimeManager::Get().GetDeltaTime();
		if (DelayTime() == 1.0f)
			is_end = true;

		terget_value = easing_func(DelayTime(), start_value, end_value);
	}

private:

	std::function<const float&(float, float, float)> easing_func;
	float time;
	const float delay_time;
	const float take_time;
	const float start_value;
	float terget_value;
	const float end_value;
	bool is_active;
	bool is_end;

	float DelayTime()
	{
		float time_ = std::fminf(1.0f, std::fmaxf(0.0f, time - delay_time) / take_time);

		return time_;
	}

};