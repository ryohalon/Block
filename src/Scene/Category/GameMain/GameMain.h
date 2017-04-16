#pragma once
#include "../../SceneBase.h"
#include "../../../Object/MapManager/MapManager.h"
#include "../../../Object/GameObject/CubeBase/MoveCube/PlayerCube/PlayerCube.h"
#include "../../../Object/GameObject/MainCamera/MainCamera.h"
#include "../../../Object/GameObject/SkyDome/SkyDome.h"
#include "../../../Object/GameObject/CubeCursor/CubeCurosr.h"
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
	void Delete() override;

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
	CubeCursor cube_cursor;

	int world, stage;
	bool is_failed, is_goal, pause, is_start;
	float failed_fall_pos_y;
	float start_delay_time;

	SkyDome sky;
	ci::gl::Light *point_light;
	ci::gl::Light *light;
	ci::gl::Light *directional_light;

	UIManager ui_manager;
	
};