#pragma once
#include "../../SceneBase.h"



class Option : public SceneBase
{
public:

	Option();
	~Option();

	void Resize() override;
	void Setup() override;
	void Update() override;
	void Draw(const ci::CameraOrtho &camera_ortho) override;

private:


};