#pragma once
#include "../../SceneBase.h"
#include "../../../Object/GameObject/SkyDome/SkyDome.h"
#include <cinder/ObjLoader.h>



class Title : public SceneBase
{
public:

	Title();
	~Title();

	void Resize() override;
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
};