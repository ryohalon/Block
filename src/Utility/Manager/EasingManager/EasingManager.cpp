#include "EasingManager.h"
#include <cinder/app/App.h>


void EasingManager::Register(bool *is_end, 
	float *p,
	const EasingType &easing_type,
	const float &delay_time,
	const float &take_time,
	const float &start_value,
	const float &end_value)
{
	std::function<float(float, float, float)> easing_func[] = {
		Easing::Linear,
		Easing::BackIn,
		Easing::BackOut,
		Easing::BackInOut,
		Easing::BounceIn,
		Easing::BounceOut,
		Easing::BounceInOut,
		Easing::CircIn,
		Easing::CircOut,
		Easing::CircInOut,
		Easing::CubicIn,
		Easing::CubicOut,
		Easing::CubicInOut,
		Easing::ElasticIn,
		Easing::ElasticOut,
		Easing::ElasticInOut,
		Easing::ExpoIn,
		Easing::ExpoOut,
		Easing::ExpoInOut,
		Easing::QuadIn,
		Easing::QuadOut,
		Easing::QuadInOut,
		Easing::QuartIn,
		Easing::QuartOut,
		Easing::QuartInOut,
		Easing::QuintIn,
		Easing::QuintOut,
		Easing::QuintInOut,
		Easing::SineIn,
		Easing::SineOut,
		Easing::SineInOut
	};

	easings.emplace_back(EasingManageOne(is_end,
		p,
		easing_func[easing_type],
		delay_time,
		take_time,
		start_value,
		end_value));
}

void EasingManager::AllDelete()
{
	easings.clear();
}


void EasingManager::Update()
{
	for (int i = 0; i < easings.size(); i++)
	{
		easings[i].Update();

		if (easings[i].GetIsEnd())
			easings.erase(easings.begin() + i);
	}
		
}