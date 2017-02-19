#pragma once
#include "../../SceneBase.h"
#include "../../../Object/MapManager/MapManager.h"
#include "../../../Object/GameObject/CubeBase/AutoMoveCube/AutoMoveCube.h"
#ifdef _DEBUG
#include "../../../NotUse/MainCamera/MainCamera.h"
#include "../../../Object/GameObject/SkyDome/SkyDome.h"
#endif



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

	void ClickAction();
	void CollisionPlayerToMap();

	MapManager map_manager;
	AutoMoveCube main_cube;

#ifdef _DEBUG
	MainCamera camera;
	SkyDome sky;
#endif
};