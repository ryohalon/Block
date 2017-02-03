#include "EasingManager.h"

void EasingManager::Register(const std::string &name,
	const std::function<const float&(float, const float&, const float&)> &easing_func,
	const float &delay_time,
	const float & take_time,
	float &start_value,
	const float &end_value)
{
	if (easing_list.find(name) != easing_list.cend())
		return;

	easing_list.insert(std::make_pair(name,
		EasingManageOne(easing_func, delay_time, take_time, start_value, end_value)));
}

void EasingManager::Delete(const std::string &name)
{
	if (easing_list.find(name) == easing_list.cend())
		return;

	easing_list.erase(name);
}

void EasingManager::AllDelete()
{
	easing_list.clear();
}

void EasingManager::Update()
{
	for (auto &easing : easing_list)
	{
		easing.second.Update();

		if (easing.second.GetIsEnd())
			easing_list.erase(easing.first);
	}
}