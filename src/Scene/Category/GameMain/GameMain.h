#pragma once
#include "../../SceneBase.h"
#include "../../../Object/MapManager/MapManager.h"
#include "../../../Object/GameObject/CubeBase/AutoMoveCube/AutoMoveCube.h"
// Debug
#include "../../../NotUse/MainCamera/MainCamera.h"
#include "../../../Object/GameObject/SkyDome/SkyDome.h"



class GameMain : public SceneBase
{
public:

	GameMain();
	~GameMain();

	void Resize() override;
	void Setup() override;
	void Update() override;
	void Draw() override;

private:

	MapManager map_manager;
	AutoMoveCube main_cube;

	// Debug
	MainCamera camera;
	SkyDome sky;
};