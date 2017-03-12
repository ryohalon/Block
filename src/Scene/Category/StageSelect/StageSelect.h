#pragma once
#include "../../SceneBase.h"



class StageSelect : public SceneBase
{
public:

	StageSelect();
	~StageSelect();

	void Resize() override;
	void Setup() override;
	void Update() override;
	void Draw(const ci::CameraOrtho &camera_ortho) override;

private:

	ci::CameraPersp camera_persp;

};