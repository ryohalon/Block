#pragma once
#include "cinder/Camera.h"
#include "../Utility/Input/Key/Key.h"
#include "../Utility/Input/Mouse/Mouse.h"
#include "../Utility/Manager/TimeManager/TimeManager.h"
#include "../Utility/Manager/TextureManager/TextureManager.h"
#include "../Utility/Manager/SoundManager/SoundManager.h"
#include "../Utility/Manager/ModelManager/ModelManager.h"
#include "../Object/GameObject/UIBase/TextureUI/ButtonUI/ButtonUI.h"
#include "../Object/GameObject/UIBase/FontUI/FontUI.h"

enum class SceneType
{
	TITLE,
	STAGESELECT,
	GAMEMAIN,
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

	virtual void Resize(const float &window_ratio) = 0;
	virtual void Setup() = 0;
	virtual void Update() = 0;
	virtual void Draw(const ci::CameraOrtho &camera_ortho) = 0;

protected:

	virtual void DrawObject() = 0;
	virtual void DrawUI() = 0;

	SceneType next_scene;
	bool is_end;
};