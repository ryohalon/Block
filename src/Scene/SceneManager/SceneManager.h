#pragma once
#include "cinder/Camera.h"

class SceneBase;



class SceneManager
{
public:

	SceneManager();
	~SceneManager();

	static SceneManager& Get()
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
	ci::Vec2i default_window_size;
	ci::CameraOrtho camera_ortho;
};