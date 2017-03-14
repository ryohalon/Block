#include "EasingManager.h"
#include <cinder/app/App.h>


void EasingManager::Register(float *p,
	const std::function<const float&(float, const float&, const float&)> &easing_func,
	const float &delay_time,
	const float &take_time,
	const float &start_value,
	const float &end_value)
{
	if (easings.find(p) != easings.cend())
		return;

	easings.insert(std::make_pair(p,
		EasingManageOne(p, easing_func, delay_time, take_time, start_value, end_value)));
}


bool EasingManager::IsExist(float *p)
{
	if (easings.find(p) != easings.cend())
		return true;

	return false;
}


void EasingManager::Delete(float *p)
{
	if (easings.find(p) == easings.cend())
		return;

	easings.erase(p);
}


void EasingManager::AllDelete()
{
	easings.clear();
}


void EasingManager::Update()
{
	for (auto &easing : easings)
		easing.second.Update();
}

void EasingManager::UpdateDelete()
{
	ci::app::console() << "0easings : " << easings.size() << std::endl;
	for (auto &easing : easings)
	{
		if (easing.second.GetIsEnd())
			Delete(easing.first);
	}

	ci::app::console() << "1easings : " << easings.size() << std::endl;
}
