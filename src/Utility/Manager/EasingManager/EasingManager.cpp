#include "EasingManager.h"
#include <cinder/app/App.h>


EasingManageOne& EasingManager::Register(float *p,
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

	EasingOne easing;
	easing.p = p;
	easing.easing_manage = EasingManageOne(p,
		easing_func[easing_type],
		delay_time,
		take_time,
		start_value,
		end_value);

	easings.emplace_back(easing);

	return easings[easings.size() - 1].easing_manage;
}

bool EasingManager::IsEaseEnd(const float * p)
{
	for (const auto &manage_one : easings)
	{
		if (p == manage_one.p)
			return false;
	}

	return true;
}

void EasingManager::AllDelete()
{
	easings.clear();
}


void EasingManager::Update()
{
	for (int i = 0; i < easings.size(); i++)
	{
		easings[i].easing_manage.Update();

		if (easings[i].easing_manage.GetIsEnd())
				easings.erase(easings.begin() + i);
	}

}