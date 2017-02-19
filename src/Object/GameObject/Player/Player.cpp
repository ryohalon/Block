#include "Player.h"
#include "../../../Utility/Utility.h"

Player::Player() :
	cube(nullptr)
{
}

Player::~Player()
{
	if (cube != nullptr)
		delete cube;
}

void Player::Setup(const ci::JsonTree & params)
{
	if (cube != nullptr)
		delete cube;

	// �v���C���[�̌����ڊ֘A�̓ǂݍ���
	LoadStatus();

	// �X�e�[�W���̓ǂݍ���
	cube->Setup(params);
}

void Player::Update()
{
	cube->Update();
}

void Player::Draw()
{
	cube->Draw();
}

void Player::LoadStatus()
{
	ci::JsonTree params(ci::app::loadAsset("LoadFile/PlayerData/Player.json"));

	if (params.getValueForKey<bool>("model"))
	{
		// ������
	}
	{
		cube = new AutoMoveCube();
	}

	cube->SetMaterial(GetMaterial(params["material"]));
}
