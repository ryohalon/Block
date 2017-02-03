#pragma once
#include "cinder/Camera.h"
#include "../Utility/Input/Key/Key.h"
#include "../Utility/Input/Mouse/Mouse.h"
#include "../Utility/Manager/TimeManager/TimeManager.h"
#include "../Utility/Manager/TextureManager/TextureManager.h"
#include "../Utility/Manager/SoundManager/SoundManager.h"

enum class SceneType
{
	TITLE,
	STAGESELECT,
	GAMEMAIN,
	OPTION,
	NONE
};

class SceneBase
{
public:

	SceneBase() :
		next_scene(SceneType::NONE),
		is_end(false)
	{}
	~SceneBase() {}

	SceneType GetNextSceneType() const { return next_scene; }
	bool IsEnd() { return is_end; }

	virtual void Resize() = 0;
	virtual void Setup() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:

	SceneType next_scene;
	bool is_end;

	ci::CameraPersp camera_persp;
	ci::CameraOrtho camera_ortho;

};