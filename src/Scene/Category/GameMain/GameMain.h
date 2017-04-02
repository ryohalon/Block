#pragma once
#include "../../SceneBase.h"
#include "../../../Object/MapManager/MapManager.h"
#include "../../../Object/GameObject/CubeBase/MoveCube/PlayerCube/PlayerCube.h"
#include "../../../Object/GameObject/MainCamera/MainCamera.h"
#include "../../../Object/GameObject/SkyDome/SkyDome.h"
#include <cinder/gl/Light.h>



class GameMain : public SceneBase
{
public:

	GameMain();
	~GameMain();

	void Resize(const float &window_ratio) override;
	void Setup() override;
	void Update() override;
	void Draw(const ci::CameraOrtho &camera_ortho) override;

private:

	void DrawObject() override;
	void DrawUI() override;

	// マップ上の特殊なキューブとのカメラからのRayで当たり判定をとって
	// 　一番近いキューブのアクションを起こす
	void ClickAction();
	void CollisionPlayerToMap();
	void SearchUnderCube(const ci::Vec3i &player_map_pos);
	void SearchMoveDirectionCube(const ci::Vec3i &player_map_pos, const int &move_direction);
	void SetFallPos(const ci::Vec3i &player_map_pos);

	void Failed();
	void Goal();

	MainCamera main_camera;
	MapManager map_manager;
	PlayerCube player_cube;

	int world, stage;
	bool is_failed, is_goal, pause;
	float failed_fall_pos_y;

	SkyDome sky;
	ci::gl::Light *point_light;
	ci::gl::Light *light;

	TextureUI menu_bg;
	TextureUI clear;
	TextureUI failed;
	FontUI menu_font;
	ButtonUI retry;
	ButtonUI back_stage_select;
	ButtonUI next_stage;
	ButtonUI menu;
	ButtonUI back_game;
	
};