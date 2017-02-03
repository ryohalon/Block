#pragma once
#include "../../SceneBase.h"
#include "../../../Object/MapManager/MapManager.h"



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
};