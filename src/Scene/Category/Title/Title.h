#pragma once
#include "../../SceneBase.h"
#include "../../../Object/GameObject/SkyDome/SkyDome.h"



class Title : public SceneBase
{
public:

	Title();
	~Title();

	void Resize() override;
	void Setup() override;
	void Update() override;
	void Draw() override;

private:

	ci::CameraPersp camera_persp;
	SkyDome sky_dome;
};