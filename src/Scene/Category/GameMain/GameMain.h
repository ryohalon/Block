#pragma once
#include "../../SceneBase.h"
#include "../../../Object/MapManager/MapManager.h"
#include "../../../Object/GameObject/CubeBase/MoveCube/PlayerCube/PlayerCube.h"
#include "../../../Object/GameObject/MainCamera/MainCamera.h"
#ifdef _DEBUG
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

	// �}�b�v��̓���ȃL���[�u�Ƃ̃J���������Ray�œ����蔻����Ƃ���
	// �@��ԋ߂��L���[�u�̃A�N�V�������N����
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

	bool is_failed, is_goal;
	float failed_fall_pos_y;

#ifdef _DEBUG
	SkyDome sky;
	ci::gl::Light *point_light;
	ci::gl::Light *light;
#endif
};