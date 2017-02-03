#pragma once
#include "EasingManageOne/EasingManageOne.h"
#include <map>


class EasingManager
{
public:

	EasingManager() {};
	~EasingManager() {};

	void SetIsActive(const std::string &name, const bool &is_active)
	{
		if (easing_list.find(name) == easing_list.cend())
			return;

		easing_list[name].SetIsActive(is_active);
	}

	void Register(const std::string &name,
		const std::function<const float&(float, const float&, const float&)> &easing_func,
		const float &delay_time,
		const float &take_time,
		float &start_value,
		const float &end_value);
	void Delete(const std::string &name);
	void AllDelete();
	void Update();

private:

	std::map<std::string, EasingManageOne> easing_list;

};