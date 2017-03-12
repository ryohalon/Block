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

	ci::CameraPersp camera_persp;
	SkyDome sky_dome;

	Transform transform;
	ci::TriMesh title_logo;
	ci::gl::Material title_logo_material;
};