#include "GameMain.h"
#include "../../../Object/GameObject/CubeBase/ShrinkCube/ShrinkCube.h"
#include "../../../Object/GameObject/CubeBase/VanishCube/VanishCube.h"
#include "../../../Object/GameObject/CubeBase/SpringCube/SpringCube.h"
#include "../../../Utility/Utility.h"
#include "../../../Utility/Input/Mouse/Mouse.h"


GameMain::GameMain() :
	is_failed(false),
	is_goal(false),
	failed_fall_pos_y(-10.0f)
{

}

GameMain::~GameMain()
{

}

void GameMain::Resize(const float &window_ratio)
{

}

void GameMain::Setup()
{
	// 選択したステージの情報を獲得
	ci::JsonTree params(ci::app::loadAsset("LoadFile/StageData/SelectStage.json"));
	int world = params.getValueForKey<int>("world");
	int stage = params.getValueForKey<int>("stage");

#ifdef _DEBUG
	ci::app::console() << "world : " << world << std::endl;
	ci::app::console() << "stage : " << stage << std::endl;

	next_scene = SceneType::TITLE;

	sky.Setup();
	point_light = new ci::gl::Light(ci::gl::Light::POINT, 0);
	point_light->setAmbient(ci::Color(0.7f, 0.7f, 0.7f));
	point_light->setDiffuse(ci::Color(0.75f, 0.75f, 0.75f));
	point_light->setSpecular(ci::Color(0.9f, 0.9f, 0.9f));

	light = new ci::gl::Light(ci::gl::Light::POINT, 1);
	light->setAmbient(ci::Color(0.9f, 0.9f, 0.9f));
	light->setDiffuse(ci::Color(0.95f, 0.95f, 0.95f));
	light->setSpecular(ci::Color(0.99f, 0.99f, 0.99f));
#endif

	// マップの準備
	map_manager.Setup(world, stage);
	// カメラの準備
	main_camera.SetInterestPoint(map_manager.GetMapCenterPos());
	main_camera.Setup(ci::JsonTree(ci::app::loadAsset("LoadFile/StageData/World" + std::to_string(world)
		+ "/Stage" + std::to_string(stage) + "/MainCamera.json")));
	// メインキューブの準備
	player_cube.SetMapPos(map_manager.GetPlayerStartPos());
	player_cube.SetScale(map_manager.GetCubeScale());
	player_cube.Setup(ci::JsonTree(ci::app::loadAsset("LoadFile/StageData/World" + std::to_string(world)
		+ "/Stage" + std::to_string(stage) + "/MainCube.json")));
}

void GameMain::Update()
{
#ifdef _DEBUG
	if (Key::Get().IsPushKey(ci::app::KeyEvent::KEY_1))
		Setup();
#endif

	main_camera.Update();

	player_cube.Update();
	map_manager.Update();

	CollisionPlayerToMap();

	ClickAction();
	Failed();
	Goal();
}

void GameMain::Draw(const ci::CameraOrtho &camera_ortho)
{
	ci::gl::pushModelView();

	main_camera.Draw();

#ifdef _DEBUG
	
	sky.Draw();
	point_light->setPosition(map_manager.GetStageMatrix() * player_cube.GetTransform().pos);
	point_light->enable();
	light->setPosition(map_manager.GetStageMatrix() * (map_manager.GetMapCenterPos() + ci::Vec3f(0.0f, 1.0f, 0.0f)));
	light->enable();
#endif

	ci::gl::enable(GL_LIGHTING);

	map_manager.Draw();

	ci::gl::pushModelView();
	glMultMatrixf(map_manager.GetStageMatrix());
	player_cube.Draw();
	ci::gl::popModelView();

	ci::gl::disable(GL_LIGHTING);
	ci::gl::popModelView();
}

void GameMain::DrawObject()
{
}

void GameMain::DrawUI()
{
}

void GameMain::ClickAction()
{
	// 左クリックしていないときははじく
	if (!Mouse::Get().IsPushButton(ci::app::MouseEvent::LEFT_DOWN))
		return;

	ci::Ray ray = main_camera.CreateRayCameraToMouse();

	ray.setOrigin(map_manager.GetStageMatrix().inverted() * ray.getOrigin());
	ray.setDirection(map_manager.GetStageMatrix().inverted().transformVec(ray.getDirection()));
	
	float min_ray_distance = std::numeric_limits<float>().max();
	CubeBase *clicked_cube = nullptr;

	for (auto &cube : map_manager.GetCubes())
	{
		if (cube->GetType() == CubeType::NORMAL)
			continue;

		ci::AxisAlignedBox3f aabb = ci::AxisAlignedBox3f(
			cube->GetTransform().pos - cube->GetTransform().scale / 2.0f,
			cube->GetTransform().pos + cube->GetTransform().scale / 2.0f);

		float ray_distance_[2];
		if (aabb.intersect(ray, ray_distance_) == 0)
			continue;
		if (std::min(ray_distance_[0], ray_distance_[1]) >= min_ray_distance)
			continue;

		min_ray_distance = std::min(ray_distance_[0], ray_distance_[1]);
		clicked_cube = cube;
	}

	if (clicked_cube == nullptr)
		return;

	// ShrinkCubeが上方向に収縮する場合
	// プレイヤーキューブが上に存在するときはじく
	if (clicked_cube->GetType() == CubeType::SHRINK)
	{
		ShrinkCube *shrink_cube = static_cast<ShrinkCube*>(clicked_cube);
		if (shrink_cube->GetShrinkDirection() == ShrinkCube::ShrinkDirection::UP)
		{
			if (clicked_cube->GetMapPos() + ci::Vec3i(0, 1, 0) == player_cube.GetMapPos())
				return;
		}
	}
	// VanishCubeのis_vanishがtrueのとき
	// プレイヤーキューブと位置が同じ場合はじく
	else if (clicked_cube->GetType() == CubeType::VANISH)
	{
		VanishCube *vanish_cube = static_cast<VanishCube*>(clicked_cube);
		if (vanish_cube->GetIsVanish())
		{
			if (clicked_cube->GetMapPos() == player_cube.GetMapPos())
				return;
		}
	}

	map_manager.ClickCube(clicked_cube);
}

void GameMain::CollisionPlayerToMap()
{
	if (is_failed)
		return;
	// メインキューブがアクション中は次の行動の判定を見る必要がないためはじく
	if (!player_cube.GetIsStop())
		return;
	if (player_cube.GetIsMoving())
		return;
	if (player_cube.GetIsFalling())
		return;

	// プレイヤーキューブの
	// 下、進行方向
	// の順に調べて進む、落ちる、曲がる を決める
	SearchUnderCube(player_cube.GetMapPos());
}

void GameMain::SearchUnderCube(const ci::Vec3i & player_map_pos)
{
	CubeType type = map_manager.GetCubeType(player_map_pos + ci::Vec3i(0, -1, 0));

	if (type == CubeType::TYPEMAX)
		assert(!"error : cubeのタイプがおかしい");

	switch (type)
	{
	case CubeType::NONE:

		SetFallPos(player_map_pos);
		break;

	case CubeType::GOAL:

		is_goal = true;
		break;

	case CubeType::NORMAL:
	case CubeType::SHRINK:
	case CubeType::START:

		SearchMoveDirectionCube(player_map_pos,
			static_cast<int>(player_cube.GetMoveDirection()));
		break;

	case CubeType::VANISH:

	{
		VanishCube *cube = map_manager.GetCube<VanishCube>(player_map_pos + ci::Vec3i(0, -1, 0));
		if (cube->GetMapPos() == (ci::Vec3i::one() * -1))
			assert(!"error : 存在しないキューブです");

		if (cube->GetIsVanish())
			SetFallPos(player_map_pos);
		else
			SearchMoveDirectionCube(player_map_pos,
				static_cast<int>(player_cube.GetMoveDirection()));
	}
	break;
	case CubeType::SPRING:
		break;
	}
}

void GameMain::SearchMoveDirectionCube(const ci::Vec3i &player_map_pos, const int &move_direction)
{
	ci::Vec3i move_map_pos[] = {
		ci::Vec3i(0, 0, 1),
		ci::Vec3i(-1, 0, 0),
		ci::Vec3i(0, 0, -1),
		ci::Vec3i(1, 0, 0)
	};
	CubeType type = map_manager.GetCubeType(player_map_pos + move_map_pos[move_direction]);

	if (type == CubeType::TYPEMAX)
		assert(!"error : cubeのタイプがおかしい");

	switch (type)
	{
	case CubeType::NONE:

		player_cube.StartMotion();
		break;

	case CubeType::NORMAL:
	case CubeType::SHRINK:
	case CubeType::START:
	case CubeType::GOAL:
	case CubeType::SPRING:

		player_cube.Hit();
		break;

	case CubeType::VANISH:

	{
		VanishCube *cube = map_manager.GetCube<VanishCube>(player_map_pos + move_map_pos[move_direction]);
		if (cube->GetMapPos() == (ci::Vec3i::one() * -1))
			assert(!"error : 存在しないキューブです");

		if (cube->GetIsVanish())
			player_cube.StartMotion();
		else
			player_cube.Hit();
	}
		break;

	}
}

void GameMain::SetFallPos(const ci::Vec3i &player_map_pos)
{
	for (int y = player_map_pos.y; y >= 0; y--)
	{
		CubeType type = map_manager.GetCubeType(ci::Vec3i(player_map_pos.x, y, player_map_pos.z));
		if (type == CubeType::TYPEMAX)
			assert(!"error : cubeのタイプがおかしい");

		switch (type)
		{
		case CubeType::NONE:
			break;
		case CubeType::NORMAL:
		case CubeType::SHRINK:
		case CubeType::START:
		case CubeType::SPRING:

			player_cube.FallStart(ci::Vec3f(
				static_cast<float>(player_map_pos.x),
				static_cast<float>(y + 1),
				static_cast<float>(player_map_pos.z)));
			return;

		case CubeType::GOAL:

			player_cube.FallStart(ci::Vec3f(
				static_cast<float>(player_map_pos.x),
				static_cast<float>(y + 1),
				static_cast<float>(player_map_pos.z)));
			break;

		case CubeType::VANISH:

		{
			VanishCube *cube = map_manager.GetCube<VanishCube>(ci::Vec3i(player_map_pos.x, y, player_map_pos.z));
			if (cube->GetMapPos() == (ci::Vec3i::one() * -1))
				assert(!"error : 存在しないキューブです");

			if (!cube->GetIsVanish())
			{
				player_cube.FallStart(ci::Vec3f(
					static_cast<float>(player_map_pos.x),
					static_cast<float>(y + 1),
					static_cast<float>(player_map_pos.z)));

				return;
			}
		}

		}
	}

	is_failed = true;
	player_cube.FallStart(ci::Vec3f(
		static_cast<float>(player_map_pos.x),
		failed_fall_pos_y,
		static_cast<float>(player_map_pos.z)));
}

void GameMain::Failed()
{
	if (!is_failed)
		return;
	if (player_cube.GetIsFalling())
		return;

	is_failed = false;
	next_scene = SceneType::GAMEMAIN;
	is_end = true;
}

void GameMain::Goal()
{
	if (!is_goal)
		return;

#ifdef _DEBUG
	if (Mouse::Get().IsPushButton(ci::app::MouseEvent::RIGHT_DOWN))
	{
		is_goal = false;
		is_end = true;
		next_scene = SceneType::TITLE;
	}
#endif
}
