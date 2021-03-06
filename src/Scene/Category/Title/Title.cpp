#include "Title.h"
#include "../../../Utility/Utility.h"
#include "../../../Utility/Manager/FadeManager/FadeManager.h"

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
	ci::JsonTree params(ci::app::loadAsset("LoadFile/UIData/TitleLogo.json"));
	titlelogo_trans.pos = GetVec3f(params["title_logo.pos"]);
	titlelogo_trans.angle = GetVec3f(params["title_logo.angle"]);
	titlelogo_trans.scale = GetVec3f(params["title_logo.scale"]);
	rotate_speed = params["title_logo"].getValueForKey<float>("rotate_speed");

	params = ci::JsonTree(ci::app::loadAsset("LoadFile/UIData/Title.json"));
	ui_namager.Setup(params);

	next_scene = SceneType::STAGESELECT;
	camera_persp = ci::CameraPersp(ci::app::getWindowWidth(),
		ci::app::getWindowHeight(),
		60.0f,
		0.1f, 2000.0f);
	camera_persp.setEyePoint(ci::Vec3f(0.0f, 0.0f, -10.0f));
	camera_persp.setCenterOfInterestPoint(ci::Vec3f(0.0f, 0.0f, 0.0f));

	sky_dome.Setup();
	SoundManager::Get().GetSound("LargeTriangleOfSummer").SetIsLoop(true);
	SoundManager::Get().GetSound("LargeTriangleOfSummer").Loop();

	FadeManager::Get().FadeIn(EasingManager::EasingType::LINEAR,
		ci::Colorf::black(),
		0.0f, 1.0f);
}

void Title::Update()
{
	SoundManager::Get().GetSound("LargeTriangleOfSummer").Loop();

	if (FadeManager::Get().IsFadeOutEnd())
	{
		is_end = true;
		return;
	}

	if (!FadeManager::Get().GetisFading())
	{
		ui_namager.Update();

		if (Mouse::Get().IsPushButton(ci::app::MouseEvent::LEFT_DOWN))
		{
			SoundManager::Get().GetSound("Select").Play();
			FadeManager::Get().FadeOut(EasingManager::EasingType::LINEAR,
				ci::Colorf::black(),
				0.0f, 1.0f);
		}
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

void Title::Delete()
{
	ui_namager.AllDelete();
}

void Title::DrawObject()
{
	sky_dome.Draw();

	ci::gl::pushModelView();
	ci::gl::translate(titlelogo_trans.pos);
	ci::gl::rotate(ci::Vec3f::yAxis() * rotate_angle);
	ci::gl::scale(titlelogo_trans.scale);

	const Model &model = ModelManager::Get().GetModel("TitleLogo");
	model.GetTexture().enableAndBind();
	ci::gl::draw(model.GetTriMesh());
	model.GetTexture().unbind();
	ci::gl::popModelView();
}

void Title::DrawUI()
{
	ci::gl::translate(0.0f, 0.0f, -10.0f);
	ui_namager.Draw();
}
