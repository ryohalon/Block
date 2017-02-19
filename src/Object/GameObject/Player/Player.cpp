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

	// プレイヤーの見た目関連の読み込み
	LoadStatus();

	// ステージ情報の読み込み
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
		// 未実装
	}
	{
		cube = new AutoMoveCube();
	}

	cube->SetMaterial(GetMaterial(params["material"]));
}
