#include "AutoMoveCube.h"
#include "../../../../Utility/Manager/EasingManager/Easing/Easing.h"
#include "../../../../Utility/Manager/TimeManager/TimeManager.h"
#include "../../../../Utility/Utility.h"
#ifdef _DEBUG
#include "../../../../Utility/Input/Mouse/Mouse.h"
#endif

AutoMoveCube::AutoMoveCube() :
	start_pos(ci::Vec3f::zero()),
	end_pos(ci::Vec3f::zero()),
	now_quat(ci::Quatf::identity()),
	rotating_quat(ci::Quatf::identity()),
	prev_quat(ci::Quatf::identity()),
	rotate_angle(0.0f),
	time(0.0f),
	take_time(0.0f),
	move_take_time(1.0f),
	fall_take_time(1.0f),
	is_moving(false),
	is_falling(false),
	move_direction(MoveDirection::FRONT),
	next_direction(MoveDirection::FRONT)
{
	rotate_axis.identity();
}

AutoMoveCube::AutoMoveCube(const ci::Vec3f & pos,
	const ci::Vec3f & angle,
	const ci::Vec3f & scale,
	const ci::gl::Material & material,
	const ci::Vec3i &map_pos,
	const float & move_take_time,
	const float & fall_take_time,
	const MoveDirection & move_direction) :
	CubeBase(pos, angle, scale, material, map_pos),
	start_pos(ci::Vec3f::zero()),
	end_pos(ci::Vec3f::zero()),
	now_quat(ci::Quatf::identity()),
	rotating_quat(ci::Quatf::identity()),
	prev_quat(ci::Quatf::identity()),
	rotate_angle(0.0f),
	time(0.0f),
	take_time(0.0f),
	move_take_time(move_take_time),
	fall_take_time(fall_take_time),
	is_moving(false),
	is_falling(false),
	move_direction(move_direction),
	next_direction(move_direction)
{
	rotate_axis.identity();
}

AutoMoveCube::~AutoMoveCube()
{

}

void AutoMoveCube::Setup()
{

}

void AutoMoveCube::Setup(const ci::JsonTree & params)
{
	transform.pos = GetVec3f(params["start_pos"]);
	transform.scale = GetVec3f(params["scale"]);
	map_pos = GetVec3i(params["map_pos"]);
	move_take_time = params.getValueForKey<float>("move_take_time");
	fall_take_time = params.getValueForKey<float>("fall_take_time");
	move_direction = static_cast<MoveDirection>(params.getValueForKey<int>("start_move_direction"));
}

void AutoMoveCube::Update()
{
	UpdateAction();
}

void AutoMoveCube::Draw()
{
	if (!is_active)
		return;

	ci::gl::pushModelView();

	ci::Matrix44f mtranstale = ci::Matrix44f::createTranslation(transform.pos);
	ci::Matrix44f mrotate = now_quat.toMatrix44();
	ci::Matrix44f mscale = ci::Matrix44f::createScale(transform.scale);

	// ˆÚ“®’†‚Ìˆ—
	if (is_moving)
	{
		// ‰ñ“]‚³‚¹‚éˆÊ’u
		ci::Matrix44f mrotate_axis;
		switch (move_direction)
		{
		case MoveDirection::FRONT:
			mrotate_axis = ci::Matrix44f::createTranslation(
				transform.scale * ci::Vec3f(0.0f, -0.5f, 0.5f));
			break;
		case MoveDirection::RIGHT:
			mrotate_axis = ci::Matrix44f::createTranslation(
				transform.scale * ci::Vec3f(-0.5f, -0.5f, 0.0f));
			break;
		case MoveDirection::BACK:
			mrotate_axis = ci::Matrix44f::createTranslation(
				transform.scale * ci::Vec3f(0.0f, -0.5f, -0.5f));
			break;
		case MoveDirection::LEFT:
			mrotate_axis = ci::Matrix44f::createTranslation(
				transform.scale * ci::Vec3f(0.5f, -0.5f, 0.0f));
			break;
		}

		ci::Matrix44f mtranstale = ci::Matrix44f::createTranslation(transform.pos);
		ci::Matrix44f mrotate = now_quat.toMatrix44();
		ci::Matrix44f mrotating = rotating_quat.toMatrix44();
		ci::Matrix44f mscale = ci::Matrix44f::createScale(transform.scale);
		// ¡Œ»İ‰ñ“]‚µ‚Ä‚¢‚és—ñ‚ğ‚©‚¯‚Ä‚©‚çŒ³‚Ì‰ñ“]s—ñ‚ğ‚©‚¯‚é
		matrix = mtranstale * mrotate_axis * mrotating * mrotate_axis.inverted() * mrotate * mscale;
	}
	else
	{
		matrix = mtranstale * now_quat * mscale;
	}


	glMultMatrixf(matrix);

	material.apply();

	ci::gl::drawCube(ci::Vec3f::zero(), ci::Vec3f::one());

	ci::gl::popModelView();
}

void AutoMoveCube::MoveStart()
{
	if (!is_stop)
		return;
	// “®‚¢‚Ä‚¢‚éÅ’†‚Í‚Í‚¶‚­
	if (is_moving)
		return;
	// —‚¿‚Ä‚¢‚éÅ’†‚Í‚Í‚¶‚­
	if (is_falling)
		return;

	// ˆÚ“®æ
	ci::Vec3f move_pos[] = {
		ci::Vec3f(0.0f, 0.0f, transform.scale.z),
		ci::Vec3f(-transform.scale.x, 0.0f, 0.0f),
		ci::Vec3f(0.0f, 0.0f, -transform.scale.z),
		ci::Vec3f(transform.scale.x, 0.0f, 0.0f)
	};

	// ‰ñ“]²
	ci::Vec3f rotate_axes[] = {
		ci::Vec3f::xAxis(),
		ci::Vec3f::zAxis()
	};

	// ‰ñ“]—Ê
	float rotate_angles[] = {
		static_cast<float>(M_PI) / 2.0f,
		static_cast<float>(M_PI) / 2.0f,
		static_cast<float>(-M_PI) / 2.0f,
		static_cast<float>(-M_PI) / 2.0f
	};

	// ƒ}ƒbƒvã‚Å‚ÌˆÚ“®æ
	ci::Vec3i move_map_pos[] = {
		ci::Vec3i(0, 0, 1),
		ci::Vec3i(-1, 0, 0),
		ci::Vec3i(0, 0, -1),
		ci::Vec3i(1, 0, 0)
	};

	// ˆÚ“®•ûŒü‚ÌŒˆ’è
	move_direction = next_direction;
	// ‰ñ“]‚µ‚½Œã‚ÌˆÊ’u
	end_pos = transform.pos + move_pos[static_cast<int>(move_direction)];
	// ‰ñ“]²
	transform.angle = rotate_axes[static_cast<int>(move_direction) % 2];
	// ‰ñ“]—Ê
	rotate_angle = rotate_angles[static_cast<int>(move_direction)];

	// ƒ}ƒbƒvã‚ÌˆÊ’u‚ÌXV
	map_pos += move_map_pos[static_cast<int>(move_direction)];

	// ˆÚ“®‚É‚©‚©‚éŠÔ‚Ìİ’è
	take_time = move_take_time;
	is_moving = true;

	// ˆÚ“®‰¹‚ÌÄ¶
	// –¢À‘•
}

void AutoMoveCube::FallStart(const ci::Vec3f &fall_pos)
{
	if (!is_stop)
		return;
	if (is_falling)
		return;
	if (is_moving)
		return;

	start_pos = transform.pos;
	end_pos = fall_pos;
	map_pos.y = static_cast<int>(end_pos.y / transform.scale.y);
	// —‚¿‚é”•ª•b”‚ğL‚Î‚·
	take_time = fall_take_time * (start_pos.y - end_pos.y);
	is_falling = true;
	
	// —‚¿‚é‰¹‚ÌÄ¶
	// –¢À‘•
}

void AutoMoveCube::ChangeMoveDirection()
{
	next_direction = static_cast<MoveDirection>(
		(static_cast<int>(next_direction) + 1)
		% static_cast<int>(MoveDirection::DIRECTIONNUM));
}

void AutoMoveCube::Hit()
{
	// ƒ‚ƒm‚É‚Ô‚Â‚©‚Á‚½‚ÌÕ“Ë‰¹‚ÌÄ¶
	// –¢À‘•

	// ˆÚ“®•ûŒü•ÏX
	ChangeMoveDirection();
}

void AutoMoveCube::UpdateAction()
{
	if (!is_stop)
		return;
	if (!is_moving && !is_falling)
		return;

	time = std::min(1.0f, TimeManager::Get().GetDeltaTime() / take_time + time);
	float time_ = Easing::CubicIn(time, 0.0f, 1.0f);

	Moving(time_);
	Falling(time_);
}

void AutoMoveCube::Moving(const float &time_)
{
	if (!is_moving)
		return;

	float now_angle = ci::lerp(0.0f, rotate_angle, time_);
	rotating_quat = ci::Quatf(transform.angle, now_angle);

	if (time < 1.0f)
		return;

	time = 0.0f;
	prev_quat = now_quat;
	now_quat = rotating_quat;
	rotating_quat = ci::Quatf::identity();
	// ‰ñ“]‚µI‚í‚Á‚½‚ÉˆÊ’u‚ğˆÚ“®‚³‚¹‚é
	transform.pos = end_pos;
	is_moving = false;
}

void AutoMoveCube::Falling(const float &time_)
{
	if (!is_falling)
		return;

	transform.pos = ci::lerp(start_pos, end_pos, time_);

	if (time < 1.0f)
		return;

	time = 0.0f;
	is_falling = false;
}

