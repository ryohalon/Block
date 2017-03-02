#pragma once
#include "../../SceneBase.h"
#include "../../../Object/GameObject/SkyDome/SkyDome.h"



class StageSelect : public SceneBase
{
public:

	StageSelect();
	~StageSelect();

	void Resize() override;
	void Setup() override;
	void Update() override;
	void Draw() override;

private:

	ci::CameraPersp camera_persp;
	SkyDome sky_dome;
};