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
	ci::app::console() << world << ',' << stage << std::endl;

	camera.Setup();
	sky.Setup();
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


}

void GameMain::Draw()
{
	ci::gl::pushModelView();

#ifdef _DEBUG
	camera.Draw();
	glCullFace(GL_FRONT);
	sky.Draw();
	glCullFace(GL_BACK);
#endif

	map_manager.Draw();
	main_cube.Draw();
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


}
