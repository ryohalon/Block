#include "ShrinkCube.h"
#include "../../../../Utillity/Manager/TimeManager/TimeManager.h"
#include "../../../../Utillity/Manager/EasingManager/Easing/Easing.h"
#include "../../../../Utillity/Input/Key/Key.h"

ShrinkCube::ShrinkCube() :
	is_shrink(false),
	is_shrinking(false),
	shrink_value(ci::Vec3f(1.0f, 2.0f, 1.0f)),
	origin_pos(ci::Vec3f::zero()),
	origin_scale(ci::Vec3f::one()),
	start_shrinking_scale(ci::Vec3f::zero()),
	end_shrinking_scale(ci::Vec3f::zero()),
	time(0.0f),
	take_time(1.0f)
{

}

ShrinkCube::~ShrinkCube()
{

}

void ShrinkCube::AlreadyShrink()
{
	is_shrink = true;
	transform.scale = shrink_value;
	transform.pos = origin_pos + (shrink_value - origin_scale) / 2.0f;
}

void ShrinkCube::ShrinkStart()
{
	end_shrinking_scale = (is_shrink == true) ?
		origin_scale :
		shrink_value;

	start_shrinking_scale = transform.scale;
	time = 0.0f;
	is_shrink = !is_shrink;
	is_shrinking = true;
}

void ShrinkCube::Setup()
{
	origin_pos = transform.pos;
}

void ShrinkCube::Update()
{
	if (Key::Get().IsPushKey(ci::app::KeyEvent::KEY_RETURN))
		ShrinkStart();

	Shrinking();

	UpdateMatrix();
}

void ShrinkCube::Shrinking()
{
	if (!is_shrinking)
		return;

	time = std::fminf(1.0f, TimeManager::Get().GetDeltaTime() / take_time + time);
	float time_ = Easing::CubicOut(time, 0.0f, 1.0f);

	transform.scale = ci::lerp(start_shrinking_scale, end_shrinking_scale, time_);
	ci::Vec3f distance = transform.scale - origin_scale;
	transform.pos = origin_pos + distance / 2.0f;

	if (time_ >= 1.0f)
	{
		time = 0.0f;
		is_shrinking = false;
	}
}
