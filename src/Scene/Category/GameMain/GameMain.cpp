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
	ci::JsonTree params(ci::app::loadAsset("LoadFile/StageData/SelectStage.json"));
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

	// Debug
	camera.Setup();
	sky.Setup();
}

void GameMain::Update()
{
	// Debug
	camera.Update();

	map_manager.Update();
	main_cube.Update();
}

void GameMain::Draw()
{
	ci::gl::pushModelView();
	// Debug
	camera.Draw();
	glCullFace(GL_FRONT);
	sky.Draw();
	glCullFace(GL_BACK);

	map_manager.Draw();
	main_cube.Draw();
	ci::gl::popModelView();
}
