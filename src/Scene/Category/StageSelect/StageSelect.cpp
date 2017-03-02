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
	camera_ortho = ci::CameraOrtho(-ci::app::getWindowWidth() / 2.0f,
		ci::app::getWindowWidth() / 2.0f,
		-ci::app::getWindowHeight() / 2.0f,
		ci::app::getWindowHeight() / 2.0f,
		0.1f,
		10.0f);

	sky_dome.Setup();
}

void StageSelect::Update()
{
	if (Mouse::Get().IsPushButton(ci::app::MouseEvent::LEFT_DOWN))
		is_end = true;
}

void StageSelect::Draw()
{
	ci::gl::pushModelView();

	ci::gl::setMatrices(camera_persp);

	sky_dome.Draw();
	ci::gl::popModelView();

	ci::gl::pushModelView();
	ci::gl::setMatrices(camera_ortho);
	ci::gl::translate(0.0f, 0.0f, -1.0f);

	ci::gl::color(ci::ColorA(0.0f, 1.0f, 0.0f));
	ci::gl::drawSolidRect(ci::Rectf(ci::Vec2f(-100.0f, -100.0f), ci::Vec2f(100.0f, 100.0f)));
	ci::gl::color(ci::ColorA(1.0f, 1.0f, 1.0f));

	ci::gl::popModelView();
}
