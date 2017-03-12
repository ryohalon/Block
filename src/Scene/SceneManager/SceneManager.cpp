#include "SceneManager.h"
#include "../Category/Title/Title.h"
#include "../Category/GameMain/GameMain.h"
#include "../Category/Option/Option.h"

SceneManager::SceneManager() :
	now_scene(nullptr)
{

}

SceneManager::~SceneManager()
{

}

void SceneManager::Resize()
{
	now_scene->Resize();
}

void SceneManager::Setup()
{
	//SoundManager::Get().Setup();
	TextureManager::Get().Setup();
	ModelManager::Get().Setup();

	now_scene = std::make_shared<Title>();
	now_scene->Setup();

	ci::JsonTree params(ci::app::loadAsset("LoadFile/WindowData/WindowData.json"));

	camera_ortho = ci::CameraOrtho(-ci::app::getWindowWidth() / 2.0f,
		-ci::app::getWindowHeight() / 2.0f,
		ci::app::getWindowWidth() / 2.0f,
		ci::app::getWindowHeight() / 2.0f,
		params.getValueForKey<float>("near_plane"),
		params.getValueForKey<float>("far_plane"));

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
			//now_scene = std::make_shared<StageSelect>();
		},
			[&] {
			now_scene = std::make_shared<GameMain>();
		},
			[&] {
			now_scene = std::make_shared<Option>();
		}
	};

	CreateScene[static_cast<int>(now_scene->GetNextSceneType())]();
	now_scene->Setup();
}