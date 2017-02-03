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
	std::ifstream file(GetFilePath("SelectStage.txt"));
	int world, stage;

	file >> world;
	file >> stage;

	ci::app::console() << world << ',' << stage << std::endl;

	map_manager.Setup(world, stage);
}

void GameMain::Update()
{
	map_manager.Update();
}

void GameMain::Draw()
{
	map_manager.Draw();
}
