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

	EasingManager() {};
	~EasingManager() {};

	static EasingManager& Get()
	{
		static EasingManager easing_manager;
		
		return easing_manager;
	}
	
	void Register(float *p,
		const EasingType &easing_type,
		const float &delay_time,
		const float &take_time,
		const float &start_value,
		const float &end_value);
	void AllDelete();
	void Update();

private:
	
	std::deque<EasingManageOne> easings;

};