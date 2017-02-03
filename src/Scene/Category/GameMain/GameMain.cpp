#include "GameMain.h"
#include "../../../Utility/Utility.h"

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
	// 選択したステージの情報を獲得
	ci::JsonTree params(ci::app::loadAsset("StageData/SelectStage.json"));
	int world = params.getValueForKey<int>("world");
	int stage = params.getValueForKey<int>("stage");

#ifdef _DEBUG
	ci::app::console() << world << ',' << stage << std::endl;
#endif

	;

	// マップの準備
	map_manager.Setup(ci::JsonTree(ci::app::loadAsset("LoadFile/StageData/World" + std::to_string(world)
		+ "/Stage" + std::to_string(stage) + "/Stage.json")));
	// メインキューブの準備
	main_cube.Setup(ci::JsonTree(ci::app::loadAsset("LoadFile/StageData/World" + std::to_string(world)
		+ "/Stage" + std::to_string(stage) + "/MainCube.json")));
}

void GameMain::Update()
{
	map_manager.Update();
}

void GameMain::Draw()
{
	map_manager.Draw();
}
