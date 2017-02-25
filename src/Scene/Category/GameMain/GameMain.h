#pragma once
#include "../../SceneBase.h"
#include "../../../Object/MapManager/MapManager.h"
#include "../../../Object/GameObject/CubeBase/AutoMoveCube/AutoMoveCube.h"
#ifdef _DEBUG
#include "../../../NotUse/MainCamera/MainCamera.h"
#include "../../../Object/GameObject/SkyDome/SkyDome.h"
#include <cinder/gl/Light.h>
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
	void SearchUnderCube(const ci::Vec3i &player_map_pos);
	void SearchMoveDirectionCube(const ci::Vec3i &player_map_pos, const int &move_direction);
	void SearchMoveDirectionUnderCube(const ci::Vec3i &player_map_pos, const int &move_direction);
	void SetFallPos(const ci::Vec3i &player_map_pos);

	MapManager map_manager;
	AutoMoveCube main_cube;

#ifdef _DEBUG
	MainCamera camera;
	SkyDome sky;
	ci::gl::Light *point_light;
#endif
};