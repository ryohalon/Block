#include "ShrinkCube.h"
#include "../../../../Utility/Manager/TimeManager/TimeManager.h"
#include "../../../../Utility/Manager/EasingManager/Easing/Easing.h"
#include "../../../../Utility/Input/Key/Key.h"

ShrinkCube::ShrinkCube() :
	is_shrink(false),
	is_shrinking(false),
	shrink_direction(ShrinkDirection::UP),
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
	const CubeType &type,
	const ci::Vec3i & map_pos,
	const bool & is_shrink,
	const ci::Vec3f & shrink_value,
	const float & take_time) :
	CubeBase(pos, angle, scale, material, type, map_pos),
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

void ShrinkCube::Setup()
{
	if (shrink_value.x > 0)
		shrink_direction = ShrinkDirection::LEFT;
	else if (shrink_value.x < 0)
		shrink_direction = ShrinkDirection::LEFT;
	else if (shrink_value.y < 0)
		shrink_direction = ShrinkDirection::UNDER;
	else if (shrink_value.y > 0)
		shrink_direction = ShrinkDirection::UP;
	else if (shrink_value.z < 0)
		shrink_direction = ShrinkDirection::BACK;
	else if (shrink_value.z > 0)
		shrink_direction = ShrinkDirection::FRONT;

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

void ShrinkCube::Draw()
{
	ci::gl::pushModelView();

	glMultMatrixf(matrix);

	material.apply();
	ci::gl::drawCube(ci::Vec3f::zero(), ci::Vec3f::one());

	ci::gl::popModelView();
}

void ShrinkCube::AlreadyShrink()
{
	transform.scale = origin_scale
		+ ci::Vec3f(std::abs(shrink_value.x),
			std::abs(shrink_value.y),
			std::abs(shrink_value.z));

	transform.pos = origin_pos + shrink_value / 2.0f;
}

void ShrinkCube::Clicked()
{
	ShrinkStart();
}

void ShrinkCube::ShrinkStart()
{

	end_shrinking_scale = (is_shrink == true) ?
		origin_scale :
		origin_scale + ci::Vec3f(std::abs(shrink_value.x),
			std::abs(shrink_value.y),
			std::abs(shrink_value.z));

	start_shrinking_scale = transform.scale;
	time = 0.0f;
	is_shrink = !is_shrink;
	is_shrinking = true;
}

void ShrinkCube::Shrinking()
{
	if (!is_shrinking)
		return;

	time = std::fminf(1.0f, TimeManager::Get().GetDeltaTime() / take_time + time);
	float time_ = Easing::CubicOut(time, 0.0f, 1.0f);

	transform.scale = ci::lerp(start_shrinking_scale, end_shrinking_scale, time_);

	ci::Vec3f distance;
	if (shrink_direction == ShrinkDirection::UNDER ||
		shrink_direction == ShrinkDirection::BACK ||
		shrink_direction == ShrinkDirection::RIGHT)
	{
		distance = origin_scale - transform.scale;
	}
	else
	{
		distance = transform.scale - origin_scale;
	}
	
	transform.pos = origin_pos + distance / 2.0f;

	if (time_ >= 1.0f)
		is_shrinking = false;
}
