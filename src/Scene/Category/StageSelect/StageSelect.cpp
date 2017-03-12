#include "StageSelect.h"

StageSelect::StageSelect()
{

}

StageSelect::~StageSelect()
{

}

void StageSelect::Resize()
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
}

void StageSelect::Update()
{

}

void StageSelect::Draw(const ci::CameraOrtho & camera_ortho)
{
	ci::gl::pushModelView();

	ci::gl::setMatrices(camera_persp);

	ci::gl::popModelView();
}
