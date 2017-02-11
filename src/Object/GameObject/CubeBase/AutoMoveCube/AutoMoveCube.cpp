#include "AutoMoveCube.h"
#include "../../../../Utility/Manager/EasingManager/Easing/Easing.h"
#include "../../../../Utility/Manager/TimeManager/TimeManager.h"
#include "../../../../Utility/Input/Mouse/Mouse.h"
#include "../../../../Utility/Utility.h"

AutoMoveCube::AutoMoveCube() :
	start_pos(ci::Vec3f::zero()),
	end_pos(ci::Vec3f::zero()),
	now_quat(ci::Quatf::identity()),
	rotating_quat(ci::Quatf::identity()),
	prev_quat(ci::Quatf::identity()),
	rotate_angle(0.0f),
	time(0.0f),
	take_time(1.0f),
	is_move(false),
	is_moving(false),
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
	const float & take_time,
	const MoveDirection & move_direction) :
	CubeBase(pos, angle, scale, material, map_pos),
	start_pos(ci::Vec3f::zero()),
	end_pos(ci::Vec3f::zero()),
	now_quat(ci::Quatf::identity()),
	rotating_quat(ci::Quatf::identity()),
	prev_quat(ci::Quatf::identity()),
	rotate_angle(0.0f),
	time(0.0f),
	take_time(take_time),
	is_move(false),
	is_moving(false),
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
	move_direction = static_cast<MoveDirection>(params.getValueForKey<int>("start_move_direction"));
}

void AutoMoveCube::Update()
{
	MoveStart();
	Moving();

	if (Mouse::Get().IsPushButton(ci::app::MouseEvent::LEFT_DOWN))
		ChangeMoveDirection();
	if (Mouse::Get().IsPushButton(ci::app::MouseEvent::RIGHT_DOWN))
		is_move = !is_move;
}

void AutoMoveCube::Draw()
{
	ci::gl::pushModelView();

	ci::Matrix44f mtranstale = ci::Matrix44f::createTranslation(transform.pos);
	ci::Matrix44f mrotate = now_quat.toMatrix44();
	ci::Matrix44f mscale = ci::Matrix44f::createScale(transform.scale);

	if (is_moving)
	{
		// 回転させる位置
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

void AutoMoveCube::Hit()
{
	// モノにぶつかった時の音を鳴らす
	// まだ入れてない

	// 移動方向変更
	ChangeMoveDirection();
}

void AutoMoveCube::FallStart()
{

}

void AutoMoveCube::MoveStart()
{
	if (!is_move)
		return;
	// 動いている最中ははじく
	if (is_moving)
		return;

	// 移動先
	ci::Vec3f move_pos[] = {
		ci::Vec3f(0.0f, 0.0f, transform.scale.z),
		ci::Vec3f(-transform.scale.x, 0.0f, 0.0f),
		ci::Vec3f(0.0f, 0.0f, -transform.scale.z),
		ci::Vec3f(transform.scale.x, 0.0f, 0.0f)
	};

	// 回転軸
	ci::Vec3f rotate_axes[] = {
		ci::Vec3f::xAxis(),
		ci::Vec3f::zAxis()
	};

	// 回転量
	float rotate_angles[] = {
		static_cast<float>(M_PI) / 2.0f,
		static_cast<float>(M_PI) / 2.0f,
		static_cast<float>(-M_PI) / 2.0f,
		static_cast<float>(-M_PI) / 2.0f
	};

	// マップ上での移動先
	ci::Vec2i move_map_pos[] = {
		ci::Vec2i(0,1),
		ci::Vec2i(-1,0),
		ci::Vec2i(0,-1),
		ci::Vec2i(1,0)
	};

	// 移動方向の決定
	move_direction = next_direction;
	// 回転した後の位置
	end_pos = transform.pos + move_pos[static_cast<int>(move_direction)];
	// 回転軸
	transform.angle = rotate_axes[static_cast<int>(move_direction) % 2];
	// 回転量
	rotate_angle = rotate_angles[static_cast<int>(move_direction)];

	// マップ上の位置の更新
	map_pos = ci::Vec3i(move_pos[static_cast<int>(move_direction)].x,
		map_pos.y,
		move_pos[static_cast<int>(move_direction)].y);

	is_moving = true;
}

void AutoMoveCube::Moving()
{
	if (!is_move)
		return;
	if (!is_moving)
		return;

	time = std::min(1.0f, TimeManager::Get().GetDeltaTime() / take_time + time);
	float time_ = Easing::CubicIn(time, 0.0f, 1.0f);
	float now_angle = ci::lerp(0.0f, rotate_angle, time_);
	rotating_quat = ci::Quatf(transform.angle, now_angle);

	if (time < 1.0f)
		return;

	time = 0.0f;
	prev_quat = now_quat;
	transform.pos = end_pos;
	is_moving = false;
	now_quat = rotating_quat;
}

void AutoMoveCube::ChangeMoveDirection()
{
	next_direction = static_cast<MoveDirection>(
		(static_cast<int>(move_direction) + 1)
		% static_cast<int>(MoveDirection::DIRECTIONNUM));
}
