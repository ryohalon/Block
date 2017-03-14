#pragma once
#include "EasingManageOne/EasingManageOne.h"
#include <map>



class EasingManager
{
public:

	EasingManager() {};
	~EasingManager() {};

	static EasingManager& Get()
	{
		static EasingManager easing_manager;
		
		return easing_manager;
	}

	
	void SetIsActive(float *p, const bool &is_active)
	{
		if (easings.find(p) == easings.cend())
			return;

		easings[p].SetIsActive(is_active);
	}

	
	void Register(float *p,
		const std::function<const float&(float, const float&, const float&)> &easing_func,
		const float &delay_time,
		const float &take_time,
		const float &start_value,
		const float &end_value);
	bool IsExist(float *p);
	void Delete(float *p);
	void AllDelete();
	void Update();
	void UpdateDelete();

private:

	
	std::map<float*, EasingManageOne> easings;

};