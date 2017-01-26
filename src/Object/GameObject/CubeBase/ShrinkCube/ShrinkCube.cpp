#include "ShrinkCube.h"
#include "../../../../Utillity/Manager/TimeManager/TimeManager.h"
#include "../../../../Utillity/Manager/EasingManager/Easing/Easing.h"
#include "../../../../Utillity/Input/Key/Key.h"

ShrinkCube::ShrinkCube() :
	is_shrink(false),
	is_shrinking(false),
	shrink_value(ci::Vec3f(0.0f, 2.0f, 0.0f)),
	origin_pos(ci::Vec3f::zero()),
	origin_scale(ci::Vec3f::one()),
	start_shrinking_scale(ci::Vec3f::zero()),
	end_shrinking_scale(ci::Vec3f::zero()),
	time(0.0f),
	take_time(1.0f)
{

}

ShrinkCube::ShrinkCube(const ci::Vec3f & pos,
	const ci::Vec3f & angle,
	const ci::Vec3f & scale,
	const ci::gl::Material & material,
	const bool & is_shrink,
	const ci::Vec3f & shrink_value,
	const float & take_time) :
	CubeBase(pos, angle, scale, material),
	is_shrink(is_shrink),
	is_shrinking(false),
	shrink_value(shrink_value),
	origin_pos(pos),
	origin_scale(scale),
	start_shrinking_scale(ci::Vec3f::one()),
	end_shrinking_scale(ci::Vec3f::one()),
	time(0.0f),
	take_time(take_time)
{

}

ShrinkCube::~ShrinkCube()
{

}

void ShrinkCube::AlreadyShrink()
{
	transform.scale = origin_scale + shrink_value;
	transform.pos = origin_pos + (shrink_value + origin_scale) / 2.0f;
}

void ShrinkCube::ShrinkStart()
{
	end_shrinking_scale = (is_shrink == true) ?
		origin_scale :
		origin_scale + shrink_value;

	start_shrinking_scale = transform.scale;
	time = 0.0f;
	is_shrink = !is_shrink;
	is_shrinking = true;
}

void ShrinkCube::Setup()
{
	if (is_shrink)
		AlreadyShrink();

	UpdateMatrix();
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
