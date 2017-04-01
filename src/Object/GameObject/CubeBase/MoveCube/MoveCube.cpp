#include "MoveCube.h"
#include "../../../../Utility/Manager/EasingManager/Easing/Easing.h"
#include "../../../../Utility/Manager/TimeManager/TimeManager.h"
#include "../../../../Utility/Utility.h"


MoveCube::MoveCube() :
	start_pos(ci::Vec3f::zero()),
	end_pos(ci::Vec3f::zero()),
	now_quat(ci::Quatf::identity()),
	rotating_quat(ci::Quatf::identity()),
	rotate_angle(0.0f),
	time(0.0f),
	take_time(0.0f),
	move_take_time(1.0f),
	is_moving(false),
	move_direction(MoveDirection::FRONT),
	next_direction(MoveDirection::FRONT)
{
	rotate_axis.identity();
}

MoveCube::MoveCube(const CubeBase & cube_base,
	const float & move_take_time,
	const MoveDirection & move_direction) :
	CubeBase(cube_base),
	move_take_time(move_take_time),
	move_direction(move_direction)
{
	rotate_axis.identity();
}

MoveCube::~MoveCube()
{
}

void MoveCube::Setup()
{
}

void MoveCube::Setup(const ci::JsonTree & params)
{
	
}

void MoveCube::Update()
{
}

void MoveCube::Draw()
{
	if (!is_active)
		return;

	ci::gl::pushModelView();

	ci::Matrix44f mtranstale = ci::Matrix44f::createTranslation(transform.pos);
	ci::Matrix44f mrotate = now_quat.toMatrix44();
	ci::Matrix44f mscale = ci::Matrix44f::createScale(transform.scale);

	// �ړ����̏���
	if (is_moving)
	{
		// ��]������ʒu
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
		// �����݉�]���Ă���s��������Ă��猳�̉�]�s���������
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

void MoveCube::StartMotion()
{
	if (!is_stop)
		return;
	// �����Ă���Œ��͂͂���
	if (is_moving)
		return;

	// �ړ���
	ci::Vec3f move_pos[] = {
		ci::Vec3f(0.0f, 0.0f, transform.scale.z),
		ci::Vec3f(-transform.scale.x, 0.0f, 0.0f),
		ci::Vec3f(0.0f, 0.0f, -transform.scale.z),
		ci::Vec3f(transform.scale.x, 0.0f, 0.0f)
	};

	// ��]��
	ci::Vec3f rotate_axes[] = {
		ci::Vec3f::xAxis(),
		ci::Vec3f::zAxis()
	};

	// ��]��
	float rotate_angles[] = {
		static_cast<float>(M_PI) / 2.0f,
		static_cast<float>(M_PI) / 2.0f,
		static_cast<float>(-M_PI) / 2.0f,
		static_cast<float>(-M_PI) / 2.0f
	};

	// �}�b�v��ł̈ړ���
	ci::Vec3i move_map_pos[] = {
		ci::Vec3i(0, 0, 1),
		ci::Vec3i(-1, 0, 0),
		ci::Vec3i(0, 0, -1),
		ci::Vec3i(1, 0, 0)
	};

	// �ړ������̌���
	move_direction = next_direction;
	// ��]������̈ʒu
	end_pos = transform.pos + move_pos[static_cast<int>(move_direction)];
	// ��]��
	transform.angle = rotate_axes[static_cast<int>(move_direction) % 2];
	// ��]��
	rotate_angle = rotate_angles[static_cast<int>(move_direction)];

	// �}�b�v��̈ʒu�̍X�V
	map_pos += move_map_pos[static_cast<int>(move_direction)];

	// �ړ��ɂ����鎞�Ԃ̐ݒ�
	take_time = move_take_time;
	is_moving = true;
}

void MoveCube::Moving(const float &time_)
{
	if (!is_moving)
		return;

	float now_angle = ci::lerp(0.0f, rotate_angle, time_);
	rotating_quat = ci::Quatf(transform.angle, now_angle);

	if (time < 1.0f)
		return;

	time = 0.0f;
	now_quat = rotating_quat;
	rotating_quat = ci::Quatf::identity();
	// ��]���I��������Ɉʒu���ړ�������
	transform.pos = end_pos;
	is_moving = false;

	SoundManager::Get().GetSound("Move").Play();
}