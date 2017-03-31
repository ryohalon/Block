#pragma once
#include "EasingManageOne/EasingManageOne.h"
#include <deque>



class EasingManager
{
public:

	enum EasingType
	{
		LINEAR,
		BACKIN,
		BACKOUT,
		BACKINOUT,
		BOUNCEIN,
		BOUNCEOUT,
		BOUNCEINOUT,
		CIRCIN,
		CIRCOUT,
		CIRCINOUT,
		CUBICIN,
		CUBICOUT,
		CUBICINOUT,
		ELASTICIN,
		ELASTICOUT,
		ELASTICINOUT,
		EXPOIN,
		EXPOOUT,
		EXPOINOUT,
		QUADIN,
		QUADOUT,
		QUADINOUT,
		QUARTIN,
		QUARTOUT,
		QUARTINOUT,
		QUINTIN,
		QUINTOUT,
		QUINTINOUT,
		SINEIN,
		SINEOUT,
		SINEINOUT
	};

	struct EasingOne
	{
		EasingManageOne easing_manage;
		float *p;
	};

	EasingManager() {};
	~EasingManager() {};

	static EasingManager& Get()
	{
		static EasingManager easing_manager;
		
		return easing_manager;
	}
	
	EasingManageOne& Register(float *p,
		const EasingType &easing_type,
		const float &delay_time,
		const float &take_time,
		const float &start_value,
		const float &end_value);
	bool IsEaseEnd(const float *p);
	void AllDelete();
	void Update();

private:
	
	std::deque<EasingOne> easings;

};