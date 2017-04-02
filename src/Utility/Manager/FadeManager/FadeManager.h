#pragma once
#include <cinder/Color.h>
#include "../EasingManager/EasingManager.h"


class FadeManager
{
public:

	FadeManager();
	~FadeManager();

	static FadeManager& Get()
	{
		static FadeManager fade_manager;

		return fade_manager;
	}

	bool IsFadeInEnd() const { return is_fadein_end; }
	bool IsFadeOutEnd() const { return is_fadeout_end; }
	bool GetisFading() const { return is_fading; }
	void SetAlpha(const float &alpha) { color.a = alpha; }

	void FadeIn(const EasingManager::EasingType &type,
		const ci::Colorf &color_,
		const float &delay_time,
		const float &take_time);
	void FadeOut(const EasingManager::EasingType &type,
		const ci::Colorf &color_,
		const float &delay_time,
		const float &take_time);

	void Draw();

private:

	ci::ColorAf color;
	bool is_fadein_end,
		is_fadeout_end,
		is_fading;
};