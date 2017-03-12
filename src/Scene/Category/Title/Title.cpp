#include "Title.h"

Title::Title()
{

}

Title::~Title()
{

}

void Title::Resize()
{

}

void Title::Setup()
{
	ci::JsonTree params(ci::app::loadAsset("LoadFile/TitleLogoData.json"));
	std::string file_path = params["model"].getValueForKey<std::string>("file_path");
	ci::ObjLoader loader(ci::app::loadAsset(file_path + params["model"].getValueForKey<std::string>("name")));
	loader.load(&title_logo);

	next_scene = SceneType::GAMEMAIN;
	camera_persp = ci::CameraPersp(ci::app::getWindowWidth(),
		ci::app::getWindowHeight(),
		60.0f,
		0.1f, 2000.0f);
	camera_persp.setEyePoint(ci::Vec3f(0.0f, 0.0f, -10.0f));
	camera_persp.setCenterOfInterestPoint(ci::Vec3f(0.0f, 0.0f, 0.0f));

	sky_dome.Setup();
}

void Title::Update()
{
	if (Mouse::Get().IsPushButton(ci::app::MouseEvent::LEFT_DOWN))
		is_end = true;
}

void Title::Draw(const ci::CameraOrtho &camera_ortho)
{
	ci::gl::pushModelView();

	ci::gl::setMatrices(camera_persp);

	sky_dome.Draw();
	ci::gl::popModelView();

	ci::gl::pushModelView();
	ci::gl::setMatrices(camera_ortho);
	ci::gl::translate(0.0f, 0.0f, -10.0f);
	
	ci::gl::color(ci::ColorA(1.0f, 0.0f, 0.0f));
	ci::gl::drawSolidRect(ci::Rectf(ci::Vec2f(-100.0f, -100.0f), ci::Vec2f(100.0f, 100.0f)));
	ci::gl::color(ci::ColorA(1.0f, 1.0f, 1.0f));

	ci::gl::popModelView();
}
