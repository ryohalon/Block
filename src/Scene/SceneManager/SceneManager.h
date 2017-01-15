#pragma once
#include "../Category/Title/Title.h"
#include "../Category/StageSelect/StageSelect.h"
#include "../Category/GameMain/GameMain.h"
#include "../Category/Option/Option.h"



class SceneManager
{
public:

	SceneManager();
	~SceneManager();

	static SceneManager Get()
	{
		static SceneManager scene_manager;

		return scene_manager;
	}

	void Resize();
	void Setup();
	void Update();
	void Draw();

private:

	void ChangeScene();

	std::shared_ptr<SceneBase> now_scene;
};