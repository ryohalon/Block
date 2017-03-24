#pragma once
#include "../../SceneBase.h"
#include "../../../Object/GameObject/SkyDome/SkyDome.h"



class Title : public SceneBase
{
public:

	Title();
	~Title();

	void Resize(const float &window_ratio) override;
	void Setup() override;
	void Update() override;
	void Draw(const ci::CameraOrtho &camera_ortho) override;

private:

	void DrawObject() override;
	void DrawUI() override;

	ci::CameraPersp camera_persp;
	SkyDome sky_dome;

	Transform titlelogo_trans;
	float rotate_angle;
	float rotate_speed;

	TextureUI click_start;
};