#pragma once
#include "cinder/Camera.h"
#include "../Utillity/Input/Key/Key.h"
#include "../Utillity/Input/Mouse/Mouse.h"
#include "../Utillity/Manager/TimeManager/TimeManager.h"
#include "../Utillity/Manager/TextureManager/TextureManager.h"
#include "../Utillity/Manager/SoundManager/SoundManager.h"

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

};