#pragma once
#include "../../SceneBase.h"
#include "../../../Object/GameObject/SkyDome/SkyDome.h"



class StageSelect : public SceneBase
{
public:

	enum class ActionType
	{
		WORLDSELECT,
		STAGESELECT
	};

	StageSelect();
	~StageSelect();

	void Resize(const float &window_ratio) override;
	void Setup() override;
	void Update() override;
	void Draw(const ci::CameraOrtho &camera_ortho) override;

private:

	void CreateStageButton(const ci::JsonTree &params);
	void GoStage(const int &world, const int &stage);
	void BackTitle();

	void DrawObject() override;
	void DrawUI() override;

	ci::CameraPersp camera_persp;
	SkyDome sky_dome;
	ActionType action_type;

	std::vector<ButtonUI> buttons;
	std::vector<FontUI> fonts;
};