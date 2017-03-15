#include "Title.h"
#include "../../../Utility/Utility.h"
#include "../../../Utility/Manager/EasingManager/EasingManager.h"

Title::Title() :
	rotate_angle(0.0f),
	rotate_speed(0.0f)
{

}

Title::~Title()
{

}

void Title::Resize(const float &window_ratio)
{
	camera_persp.setAspectRatio(ci::app::getWindowAspectRatio());
}

void Title::Setup()
{
	ci::JsonTree params(ci::app::loadAsset("LoadFile/TitleLogoData/TitleLogoData.json"));
	titlelogo_trans.pos = GetVec3f(params["pos"]);
	titlelogo_trans.angle = GetVec3f(params["angle"]);
	titlelogo_trans.scale = GetVec3f(params["scale"]);
	rotate_speed = params.getValueForKey<float>("rotate_speed");

	next_scene = SceneType::STAGESELECT;
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

	if (Mouse::Get().IsPushButton(ci::app::MouseEvent::RIGHT_DOWN))
	{
		ci::JsonTree params(ci::app::loadAsset("LoadFile/TitleLogoData/TitleLogoData.json"));
		titlelogo_trans.pos = GetVec3f(params["pos"]);
		titlelogo_trans.angle = GetVec3f(params["angle"]);
	}

	rotate_angle += TimeManager::Get().GetDeltaTime() * rotate_speed;
}

void Title::Draw(const ci::CameraOrtho &camera_ortho)
{
	ci::gl::pushModelView();
	ci::gl::setMatrices(camera_persp);
	DrawObject();
	ci::gl::popModelView();

	ci::gl::pushModelView();
	ci::gl::setMatrices(camera_ortho);
	DrawUI();
	ci::gl::popModelView();
}

void Title::DrawObject()
{
	sky_dome.Draw();

	ci::gl::pushModelView();
	// ÉÇÉfÉãÇÃíÜêSÇ™Ç∏ÇÍÇƒÇ¢ÇÈÇΩÇﬂè≠ÇµèCê≥
	ci::gl::translate(titlelogo_trans.pos);
	ci::gl::rotate(ci::Vec3f::yAxis() * rotate_angle);
	//ci::gl::translate(titlelogo_trans.pos);
	ci::gl::rotate(titlelogo_trans.angle);
	ci::gl::scale(titlelogo_trans.scale);

	const Model &model = ModelManager::Get().GetModel("TitleLogo");
	model.GetTexture().enableAndBind();
	ci::gl::draw(model.GetTriMesh());
	model.GetTexture().unbind();

	ci::gl::popModelView();

	ci::gl::drawStrokedCube(ci::AxisAlignedBox3f(ci::Vec3f::one() * -1.0f, ci::Vec3f::one() * 1.0f));
}

void Title::DrawUI()
{
	ci::gl::translate(0.0f, 0.0f, -10.0f);

	ci::gl::color(ci::ColorA(1.0f, 0.0f, 0.0f));
	ci::gl::drawSolidRect(ci::Rectf(ci::Vec2f(-100.0f, -100.0f), ci::Vec2f(100.0f, 100.0f)));
	ci::gl::color(ci::ColorA(1.0f, 1.0f, 1.0f));
}
