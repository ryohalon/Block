#include "SceneManager.h"

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
	now_scene = std::make_shared<Title>();
	now_scene->Setup();
}

void SceneManager::Update()
{
	now_scene->Update();

	if (now_scene->IsEnd())
		ChangeScene();
}

void SceneManager::Draw()
{
	ci::gl::clear();

	now_scene->Draw();
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
		},
			[&] {
			now_scene = std::make_shared<Option>();
		}
	};

	CreateScene[static_cast<int>(now_scene->GetNextSceneType())]();
	now_scene->Setup();
}