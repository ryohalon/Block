#include "GameMain.h"
#include "../../../Utility/Utility.h"
#include "../../../Utility/Input/Mouse/Mouse.h"


GameMain::GameMain()
{

}

GameMain::~GameMain()
{

}

void GameMain::Resize()
{

}

void GameMain::Setup()
{
	// �I�������X�e�[�W�̏����l��
	ci::JsonTree params(ci::app::loadAsset("LoadFile/StageData/SelectStage.json"));
	int world = params.getValueForKey<int>("world");
	int stage = params.getValueForKey<int>("stage");

#ifdef _DEBUG
	ci::app::console() << "world : " << world << std::endl;
	ci::app::console() << "stage : " << stage << std::endl;

	camera.Setup();
	/*camera.Setup(ci::Vec3f(-5.0f, 10.0f, -5.0f),
		ci::Vec3f(5.0f, -5.0f, 5.0f),
		45.0f, 0.1f, 2000.0f);*/
	sky.Setup();
	point_light = new ci::gl::Light(0, ci::gl::Light::POINT);
	point_light->setAmbient(ci::Color(0.5f, 0.5f, 0.5f));
	point_light->setDiffuse(ci::Color(0.6f, 0.6f, 0.6f));
	point_light->setSpecular(ci::Color(0.8f, 0.8f, 0.8f));
#endif

	// �}�b�v�̏���
	map_manager.Setup(ci::JsonTree(ci::app::loadAsset("LoadFile/StageData/World" + std::to_string(world)
		+ "/Stage" + std::to_string(stage) + "/Stage.json")));
	// ���C���L���[�u�̏���
	main_cube.Setup(ci::JsonTree(ci::app::loadAsset("LoadFile/StageData/World" + std::to_string(world)
		+ "/Stage" + std::to_string(stage) + "/MainCube.json")));
}

void GameMain::Update()
{
#ifdef _DEBUG
	camera.Update();
#endif

	main_cube.Update();
	map_manager.Update();

	CollisionPlayerToMap();
}

void GameMain::Draw()
{
	ci::gl::pushModelView();

#ifdef _DEBUG
	camera.Draw();
	glCullFace(GL_FRONT);
	sky.Draw();
	glCullFace(GL_BACK);
	point_light->setPosition(main_cube.GetTransform().pos);
	point_light->enable();
#endif

	ci::gl::enable(GL_LIGHTING);

	map_manager.Draw();
	main_cube.Draw();


	ci::gl::disable(GL_LIGHTING);
	ci::gl::popModelView();
}

void GameMain::ClickAction()
{
	// ���N���b�N���Ă��Ȃ��Ƃ��͂͂���
	if (!Mouse::Get().IsPushButton(ci::app::MouseEvent::LEFT_DOWN))
		return;

	// �}�b�v��̓���ȃL���[�u�Ƃ̃J���������Ray�œ����蔻����Ƃ���
	// �@��ԋ߂��L���[�u�̃A�N�V�������N����
	// ������


}

void GameMain::CollisionPlayerToMap()
{
	// ���C���L���[�u���A�N�V�������͎��̍s���̔��������K�v���Ȃ����߂͂���
	if (!main_cube.GetIsStop())
		return;
	if (main_cube.GetIsMoving())
		return;
	if (main_cube.GetIsFalling())
		return;

	// �܂��^���̃}�b�v��������
	// �@�����Ȃ������ꍇ : 
	// �@�@���ɃL���[�u������ꍇ : ���̃L���[�u�̏�܂ŗ�����
	// �@�@���ɃL���[�u���Ȃ��ꍇ : ��ʊO�܂ŗ����ăQ�[���I�[�o�[�ɂ���@���̌�̃��X�^�[�g�����͂ǂ����邩�͖���
	// �@�L���[�u������ꍇ :
	// �@�@���ʂ̃L���[�u : ���C���L���[�u�̈ړ������̃L���[�u�𒲂ׂ�
	// �@�@�@�����Ȃ��ꍇ : �ړ�
	// �@�@�@�L���[�u������ꍇ : 
	// �@�@�@�@���ʂ̃L���[�u : �ړ������̕ύX�@���̂��Ƃ����ړ����邩�A1�t���[����ɂ��邩�͖���
	// �@�@Vanish : �I���A�I�t�ŕς��
	// �@�@�@�I�� : �Ȃ����̂Ƃ��ď�������
	// �@�@�@�I�t : ���ʂ̃L���[�u�Ƃ��ď�������

	SearchUnderCube(main_cube.GetMapPos());
}

void GameMain::SearchUnderCube(const ci::Vec3i & player_map_pos)
{
	MapManager::CubeType type = map_manager.GetCubeType(player_map_pos + ci::Vec3i(0, -1, 0));

	if (type == MapManager::CubeType::TYPEMAX)
		assert(!"error : cube�̃^�C�v����������");

	switch (type)
	{
	case MapManager::CubeType::NONE:
		SetFallPos(player_map_pos);
		break;
	case MapManager::CubeType::NORMAL:

		SearchMoveDirectionCube(player_map_pos,
			static_cast<int>(main_cube.GetMoveDirection()));
		break;
	case MapManager::CubeType::SHRINK:
		break;
	case MapManager::CubeType::VANISH:
		break;
	}
}

void GameMain::SearchMoveDirectionCube(const ci::Vec3i &player_map_pos, const int &move_direction)
{
	ci::Vec3i move_map_pos[] = {
		ci::Vec3i(0, 0, 1),
		ci::Vec3i(-1, 0, 0),
		ci::Vec3i(0, 0, -1),
		ci::Vec3i(1, 0, 0)
	};
	MapManager::CubeType type = map_manager.GetCubeType(player_map_pos + move_map_pos[move_direction]);

	if (type == MapManager::CubeType::TYPEMAX)
		assert(!"error : cube�̃^�C�v����������");

	switch (type)
	{
	case MapManager::CubeType::NONE:
		SearchMoveDirectionUnderCube(player_map_pos, move_direction);
		break;
	case MapManager::CubeType::NORMAL:
		main_cube.Hit();
		break;
	case MapManager::CubeType::SHRINK:
		main_cube.Hit();
		break;
	case MapManager::CubeType::VANISH:
		break;
	}
}

void GameMain::SearchMoveDirectionUnderCube(const ci::Vec3i & player_map_pos, const int & move_direction)
{
	ci::Vec3i move_map_pos[] = {
		ci::Vec3i(0, -1, 1),
		ci::Vec3i(-1, -1, 0),
		ci::Vec3i(0, -1, -1),
		ci::Vec3i(1, -1, 0)
	};
	MapManager::CubeType type = map_manager.GetCubeType(player_map_pos + move_map_pos[move_direction]);

	if(type == MapManager::CubeType::TYPEMAX)
		assert(!"error : cube�̃^�C�v����������");

	switch (type)
	{
	case MapManager::CubeType::NONE:
		main_cube.MoveStart();
		break;
	case MapManager::CubeType::NORMAL:
		main_cube.MoveStart();
		break;
	case MapManager::CubeType::SHRINK:
		break;
	case MapManager::CubeType::VANISH:
		main_cube.MoveStart();
		break;
	}
}

void GameMain::SetFallPos(const ci::Vec3i &player_map_pos)
{
	for (int y = player_map_pos.y; y >= 0; y--)
	{
		MapManager::CubeType type = map_manager.GetCubeType(ci::Vec3i(player_map_pos.x, y, player_map_pos.z));
		if (type == MapManager::CubeType::TYPEMAX)
			assert(!"error : cube�̃^�C�v����������");

		switch (type)
		{
		case MapManager::CubeType::NONE:
			break;
		case MapManager::CubeType::NORMAL:
			main_cube.FallStart(ci::Vec3f(
				static_cast<float>(player_map_pos.x),
				static_cast<float>(y + 1), static_cast<float>(player_map_pos.z)));
			return;
		case MapManager::CubeType::SHRINK:
			break;
		case MapManager::CubeType::VANISH:
			break;
		}
	}
}
