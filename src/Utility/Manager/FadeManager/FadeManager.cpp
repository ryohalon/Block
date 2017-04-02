#include "FadeManager.h"
#include <cinder/gl/gl.h>
#include <cinder/app/App.h>

FadeManager::FadeManager() :
	color(ci::ColorAf(0.0f, 0.0f, 0.0f, 1.0f)),
	is_fadein_end(false),
	is_fadeout_end(false),
	is_fading(false)
{
}

FadeManager::~FadeManager()
{

}

void FadeManager::FadeIn(const EasingManager::EasingType & type, const ci::Colorf & color_, const float & delay_time, const float & take_time)
{
	if (is_fading)
		return;

	is_fading = true;
	color = ci::ColorAf(color_.r, color_.g, color_.b, 1.0f);
	EasingManager::Get().Register(
		&(color.a),
		type,
		delay_time, take_time,
		1.0f, 0.0f).SetEndFunc([this] {
		is_fading = false;
		is_fadein_end = true;
	});
}

void FadeManager::FadeOut(const EasingManager::EasingType & type, const ci::Colorf & color_, const float & delay_time, const float & take_time)
{
	if (is_fading)
		return;

	is_fading = true;
	color = ci::ColorAf(color_.r, color_.g, color_.b, 0.0f);
	EasingManager::Get().Register(
		&(color.a),
		type,
		delay_time, take_time,
		0.0f, 1.0f).SetEndFunc([this] {
		is_fading = false;
		is_fadeout_end = true;
	});
}

void FadeManager::Draw()
{
	if (is_fadein_end)
		is_fadein_end = false;
	if (is_fadeout_end)
		is_fadeout_end = false;

	ci::Vec2f window_size = ci::app::getWindowSize();
	ci::gl::color(color);
	ci::gl::drawSolidRect(ci::Rectf(-window_size / 2.0f, window_size / 2.0f));
}
