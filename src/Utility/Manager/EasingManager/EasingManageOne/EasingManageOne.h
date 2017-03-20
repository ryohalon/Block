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
		terget_value(nullptr),
		start_value(0.0f),
		end_value(0.0f),
		is_active(true),
		is_end(false)
	{};
	EasingManageOne(float *target_value,
		const std::function<float(float, float, float)> &easing_func,
		const float &delay_time,
		const float &take_time,
		const float &start_value,
		const float &end_value) :
		easing_func(easing_func),
		time(0.0f),
		delay_time(delay_time),
		take_time(take_time),
		terget_value(target_value),
		start_value(start_value),
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
	void SetIsActive(const bool &is_active_) { is_active = is_active_; }

	void EasingEnd() { time = delay_time + take_time; }

	void Update()
	{
		if (!is_active)
			return;
		if (is_end)
			return;

		time += TimeManager::Get().GetDeltaTime();
		float time_ = std::fminf(1.0f, std::fmaxf(0.0f,
			time - delay_time) / take_time);
		if (time_ == 1.0f)
			is_end = true;

		float ratio = easing_func(time_, 0.0f, 1.0f);
		(*terget_value) = ci::lerp(start_value, end_value, ratio);
	}

private:

	void UpdateTime()
	{
		
	}

	std::function<const float&(float, float, float)> easing_func;
	float time;
	float delay_time;
	float take_time;
	float *terget_value;
	float start_value;
	float end_value;
	bool is_active;
	bool is_end;

};