#include "StageSelect.h"
#include "../../../SaveData/SaveData.h"
#include "../../../Utility/Manager/FadeManager/FadeManager.h"

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
	next_scene = SceneType::GAMEMAIN;
	camera_persp = ci::CameraPersp(ci::app::getWindowWidth(),
		ci::app::getWindowHeight(),
		60.0f,
		0.1f, 2000.0f);
	camera_persp.setEyePoint(ci::Vec3f(0.0f, 0.0f, -10.0f));
	camera_persp.setCenterOfInterestPoint(ci::Vec3f(0.0f, 0.0f, 0.0f));
	sky_dome.Setup();

	ci::JsonTree params(ci::app::loadAsset("LoadFile/UIData/StageSelect.json"));
	CreateStageButton(params["stage"]);

	FontUI font;
	font.Setup(params["select_stage"]);
	fonts.push_back(font);

	font.Setup(params["back_title.font"]);
	fonts.push_back(font);

	ButtonUI button;
	button.Setup(params["back_title.button"]);
	button.SetClickedFunc([this] { BackTitle(); });
	buttons.push_back(button);

	SoundManager::Get().GetSound("LargeTriangleOfSummer").SetIsLoop(true);
	SoundManager::Get().GetSound("LargeTriangleOfSummer").Loop();

	FadeManager::Get().FadeIn(EasingManager::EasingType::LINEAR,
		ci::Colorf::black(),
		0.0f, 1.0f);
}

void StageSelect::Update()
{
	SoundManager::Get().GetSound("LargeTriangleOfSummer").Loop();

	if (!FadeManager::Get().GetisFading())
	{
		for (auto &button : buttons)
			button.Update();
	}

	if (FadeManager::Get().IsFadeOutEnd())
		is_end = true;
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

void StageSelect::CreateStageButton(const ci::JsonTree &params)
{
	ci::Vec3f first_pos = GetVec3f(params["stage_button.first_pos"]);
	ci::Vec2f button_size[] = {
		GetVec2f(params["stage_button.size." + std::to_string(0)]),
		GetVec2f(params["stage_button.size." + std::to_string(1)]),
	};
	ci::Vec2f distance = GetVec2f(params["stage_button.distance"]);
	float flexible_value = params.getValueForKey<float>("stage_button.flexible_value");
	float take_time = params.getValueForKey<float>("stage_button.take_time");
	ci::ColorAf button_color[SaveData::StageStatus::MAXNUM];
	ci::JsonTree color_params = params["stage_button.color"];
	for (int i = 0; i < SaveData::StageStatus::MAXNUM; i++)
	{
		ci::Vec4f color_ = GetVec4f(color_params[i]);
		button_color[i] = ci::ColorAf(color_.x, color_.y, color_.z, color_.w);
	}
	
	std::vector<std::vector<int>> save_datas = SaveData::Get().GetSaveData();
	for (int i = 0; i < save_datas.size(); i++)
	{
		int stage_num = save_datas[i].size();
		for (int k = 0; k < save_datas[i].size(); k++)
		{
			ci::Vec3f pos = ci::Vec3f(first_pos.x + (k % (stage_num / 2)) * (button_size[0].x + distance.x),
				first_pos.y - (k / (stage_num / 2)) * (button_size[0].y + distance.y),
					0.0f);
			
			ci::Vec2f button_size_ = button_size[save_datas[i][k] / SaveData::StageStatus::LOCK];
			ButtonUI button;
			button.SetPos(pos);
			button.SetScale(ci::Vec3f(button_size_.x, button_size_.y, 1.0f));
			button.SetOriginSize(button_size[save_datas[i][k] / SaveData::StageStatus::LOCK].xy());
			button.SetFlexibleValue(flexible_value);
			button.SetTextureName(params["stage_button.texture_name"].getValueAtIndex<std::string>(i));
			button.SetTakeTime(take_time);
			if (save_datas[i][k] != SaveData::StageStatus::LOCK)
				button.SetClickedFunc([this, i, k] {GoStage(i + 1, k + 1); });
			button.SetColor(button_color[save_datas[i][k]]);
			buttons.push_back(button);

			FontUI font;
			font.SetStr(std::to_string(k + 1));
			font.SetPos(pos);
			std::string font_path = "Resource/Font/" + params.getValueForKey<std::string>("font.font_type");
			font.SetFont(ci::Font(ci::app::loadAsset(font_path),
				params["font.size"].getValueAtIndex<int>(save_datas[i][k] / SaveData::StageStatus::LOCK)));
			font.SetColor(GetColorAf(params["font.color"]));

			fonts.push_back(font);
		}
	}

}

void StageSelect::GoStage(const int &world, const int &stage)
{
	ci::JsonTree params(ci::app::loadAsset("LoadFile/StageData/SelectStage.json"));
	params["world"] = ci::JsonTree("world", world);
	params["stage"] = ci::JsonTree("stage", stage);
	params.write(ci::app::getAssetPath("LoadFile/StageData/SelectStage.json"));

	next_scene = SceneType::GAMEMAIN;
	SoundManager::Get().GetSound("LargeTriangleOfSummer").SetIsLoop(false);
	SoundManager::Get().GetSound("LargeTriangleOfSummer").Stop();

	FadeManager::Get().FadeOut(EasingManager::EasingType::LINEAR,
		ci::Colorf::black(),
		0.0f, 1.0f);
}

void StageSelect::BackTitle()
{
	next_scene = SceneType::TITLE;
	FadeManager::Get().FadeOut(EasingManager::EasingType::LINEAR,
		ci::Colorf::black(),
		0.0f, 1.0f);
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

	ci::gl::translate(ci::Vec3f(0.0f, 0.0f, 1.0f));
	for (auto &font : fonts)
		font.Draw();
}
