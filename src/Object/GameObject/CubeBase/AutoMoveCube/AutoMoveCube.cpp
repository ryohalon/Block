#include "AutoMoveCube.h"
#include "../../../../Utility/Manager/EasingManager/Easing/Easing.h"
#include "../../../../Utility/Manager/TimeManager/TimeManager.h"
#include "../../../../Utility/Input/Mouse/Mouse.h"

AutoMoveCube::AutoMoveCube() :
	start_pos(ci::Vec3f::zero()),
	end_pos(ci::Vec3f::zero()),
	now_quat(ci::Quatf::identity()),
	prev_quat(ci::Quatf::identity()),
	rotate_angle(0.0f),
	time(0.0f),
	take_time(1.0f),
	is_move(false),
	is_moving(false),
	move_direction(MoveDirection::FRONT)
{

}

AutoMoveCube::AutoMoveCube(const ci::Vec3f & pos, 
	const ci::Vec3f & angle, 
	const ci::Vec3f & scale, 
	const ci::gl::Material & material, 
	const ci::Vec3i &map_pos,
	const float & take_time, 
	const MoveDirection & move_direction):
	CubeBase(pos, angle, scale, material, map_pos),
	start_pos(ci::Vec3f::zero()),
	end_pos(ci::Vec3f::zero()),
	now_quat(ci::Quatf::identity()),
	prev_quat(ci::Quatf::identity()),
	rotate_angle(0.0f),
	time(0.0f),
	take_time(take_time),
	is_move(false),
	is_moving(false),
	move_direction(move_direction)
{

}

AutoMoveCube::~AutoMoveCube()
{

}

void AutoMoveCube::Setup()
{

}

void AutoMoveCube::Setup(const ci::JsonTree & json)
{
	
}

void AutoMoveCube::Update()
{
	MoveStart();
	Moving();

	if (Mouse::Get().IsPushButton(ci::app::MouseEvent::LEFT_DOWN))
		ChangeMoveDirection();
	if (Mouse::Get().IsPushButton(ci::app::MouseEvent::RIGHT_DOWN))
		is_move != is_move;
}

void AutoMoveCube::Draw()
{
	ci::gl::pushModelView();

	ci::Matrix44f mtranstale = ci::Matrix44f::createTranslation(transform.pos);
	ci::Matrix44f mrotate = now_quat.toMatrix44();
	ci::Matrix44f mscale = ci::Matrix44f::createScale(transform.scale);
	matrix = mtranstale * mrotate * mscale;
	glMultMatrixf(matrix);

	material.apply();

	ci::gl::drawCube(ci::Vec3f::zero(), ci::Vec3f::one());

	ci::gl::popModelView();
}

void AutoMoveCube::MoveStart()
{
	if (is_moving)
		return;

	// à⁄ìÆêÊ
	ci::Vec3f move_pos[] = {
		ci::Vec3f(0.0f, 0.0f, transform.scale.z),
		ci::Vec3f(-transform.scale.x, 0.0f, 0.0f),
		ci::Vec3f(0.0f, 0.0f, -transform.scale.z),
		ci::Vec3f(transform.scale.x, 0.0f, 0.0f)
	};

	// âÒì]é≤
	ci::Vec3f rotate_axes[] = {
		ci::Vec3f::xAxis(),
		ci::Vec3f::zAxis()
	};
	
	// âÒì]ó 
	float rotate_angles[] = {
		static_cast<float>(M_PI) / 2.0f,
		static_cast<float>(M_PI) / 2.0f,
		static_cast<float>(-M_PI) / 2.0f,
		static_cast<float>(-M_PI) / 2.0f
	};
	
	start_pos = transform.pos;
	end_pos = transform.pos + move_pos[static_cast<int>(move_direction)];
	transform.angle = rotate_axes[static_cast<int>(move_direction) % 2];
	rotate_angle = rotate_angles[static_cast<int>(move_direction)];

	is_moving = true;
}

void AutoMoveCube::Moving()
{
	if (!is_moving)
		return;

	time = std::min(1.0f, TimeManager::Get().GetDeltaTime() / take_time + time);
	float time_ = Easing::CubicIn(time, 0.0f, 1.0f);
	transform.pos = ci::lerp(start_pos, end_pos, time_);
	float now_angle = ci::lerp(0.0f, rotate_angle, time_);
	now_quat = prev_quat * ci::Quatf(transform.angle, now_angle);

	if (time >= 1.0f)
	{
		time = 0.0f;
		prev_quat = now_quat;
		is_moving = false;
	}
}

void AutoMoveCube::ChangeMoveDirection()
{
	move_direction = static_cast<MoveDirection>(
		(static_cast<int>(move_direction) + 1)
		% static_cast<int>(MoveDirection::DIRECTIONNUM));
}
