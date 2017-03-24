#include "StageSelect.h"
#include "../../../SaveData/SaveData.h"

StageSelect::StageSelect() :
	action_type(ActionType::WORLDSELECT)
{

}

StageSelect::~StageSelect()
{

}

void StageSelect::Resize(const float &window_ratio)
{

}

void StageSelect::Setup()
{
	SaveData::Get().LoadSaveData();
	next_scene = SceneType::GAMEMAIN;
	camera_persp = ci::CameraPersp(ci::app::getWindowWidth(),
		ci::app::getWindowHeight(),
		60.0f,
		0.1f, 2000.0f);
	camera_persp.setEyePoint(ci::Vec3f(0.0f, 0.0f, -10.0f));
	camera_persp.setCenterOfInterestPoint(ci::Vec3f(0.0f, 0.0f, 0.0f));
	sky_dome.Setup();

	CreateStageButton();
}

void StageSelect::Update()
{
	for(int i = 0; i < buttons.size(); i++)
	{
		buttons[i].Update();

		if (!buttons[i].GetIsClicked())
			continue;

		int world = i / SaveData::Get().GetStageNum();
		int stage = i - SaveData::Get().GetStageNum() * world;
		GoStage(world, stage);
	}
}

void StageSelect::Draw(const ci::CameraOrtho & camera_ortho)
{
	ci::gl::pushModelView();
	ci::gl::setMatrices(camera_persp);
	DrawObject();
	ci::gl::popModelView();

	ci::gl::pushModelView();
	ci::gl::setMatrices(camera_ortho);
	DrawUI();
	ci::gl::popModelView();
}

void StageSelect::CreateStageButton()
{
	// ここも
	std::vector<std::vector<int>> save_datas = SaveData::Get().GetSaveData();
	for (auto &world : save_datas)
		for (auto &stage : world)
			ci::app::console() << stage << std::endl;
}

void StageSelect::GoStage(const int &world, const int &stage)
{
	ci::JsonTree params(ci::app::loadAsset("LoadFile/StageData/SelectStage.json"));
	// 明日選択されたステージの保存やる
	params;
}

void StageSelect::DrawObject()
{
	sky_dome.Draw();
}

void StageSelect::DrawUI()
{
	ci::gl::translate(ci::Vec3f(0.0f, 0.0f, -10.0f));

	for (auto &button : buttons)
		button.Draw();
}
