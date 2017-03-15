#include "SceneManager.h"
#include "../Category/Title/Title.h"
#include "../Category/StageSelect/StageSelect.h"
#include "../Category/GameMain/GameMain.h"
#include "../../Utility/Manager/EasingManager/EasingManager.h"

SceneManager::SceneManager() :
	now_scene(nullptr),
	default_window_size(ci::Vec2i::zero())
{

}

SceneManager::~SceneManager()
{

}

void SceneManager::Resize()
{
	float window_ratio = static_cast<float>(ci::app::getWindowWidth()) / default_window_size.x;
	ci::app::setWindowSize(ci::app::getWindowWidth(),
		static_cast<float>(default_window_size.y) * window_ratio);
	now_scene->Resize(window_ratio);
}

void SceneManager::Setup()
{
	SoundManager::Get().Setup();
	TextureManager::Get().Setup();
	ModelManager::Get().Setup();
	EasingManager::Get();

	now_scene = std::make_shared<Title>();
	now_scene->Setup();

	ci::JsonTree params(ci::app::loadAsset("LoadFile/CameraOrthoData/CameraOrthoData.json"));

	camera_ortho = ci::CameraOrtho(-ci::app::getWindowWidth() / 2.0f,
		-ci::app::getWindowHeight() / 2.0f,
		ci::app::getWindowWidth() / 2.0f,
		ci::app::getWindowHeight() / 2.0f,
		params.getValueForKey<float>("near_plane"),
		params.getValueForKey<float>("far_plane"));

	default_window_size = ci::Vec2i(
		ci::app::getWindowWidth(),
		ci::app::getWindowHeight());

	ci::gl::enableAlphaBlending();
	ci::gl::enableDepthRead();
	ci::gl::enableDepthWrite();
	glCullFace(GL_BACK);
}

void SceneManager::Update()
{
	TimeManager::Get().Update(
		static_cast<float>(ci::app::getElapsedSeconds()),
		static_cast<int>(ci::app::getElapsedFrames()));

	EasingManager::Get().Update();

	now_scene->Update();

	if (now_scene->IsEnd())
		ChangeScene();

	Mouse::Get().FlushInput();
	Key::Get().FlushInput();
}

void SceneManager::Draw()
{
	ci::gl::clear();

	now_scene->Draw(camera_ortho);
}

void SceneManager::ChangeScene()
{
	std::function<void()> CreateScene[] =
	{
			[&] {
			now_scene = std::make_shared<Title>();
		},
			[&] {
			now_scene = std::make_shared<StageSelect>();
		},
			[&] {
			now_scene = std::make_shared<GameMain>();
		}
	};

	CreateScene[static_cast<int>(now_scene->GetNextSceneType())]();
	now_scene->Setup();
}