#pragma once
#include "../../SceneBase.h"



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

	void Resize() override;
	void Setup() override;
	void Update() override;
	void Draw(const ci::CameraOrtho &camera_ortho) override;

private:

	void DrawObject() override;
	void DrawUI() override;

	ci::CameraPersp camera_persp;
	ActionType action_type;
	int world_select_num;
	int stage_select_num;
};