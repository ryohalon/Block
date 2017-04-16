#include "GameMain.h"
#include "../../../SaveData/SaveData.h"
#include "../../../Object/GameObject/CubeBase/ShrinkCube/ShrinkCube.h"
#include "../../../Object/GameObject/CubeBase/VanishCube/VanishCube.h"
#include "../../../Object/GameObject/CubeBase/SpringCube/SpringCube.h"
#include "../../../Utility/Utility.h"
#include "../../../Utility/Input/Mouse/Mouse.h"
#include "../../../Utility/Manager/FadeManager/FadeManager.h"
#include "../../../Object/GameObject/UIBase/TextureUI/ButtonUI/ButtonUI.h"
#include "../../../Object/GameObject/UIBase/FontUI/FontUI.h"



GameMain::GameMain() :
	world(1),
	stage(1),
	is_failed(false),
	is_goal(false),
	pause(false),
	is_start(false),
	failed_fall_pos_y(-100.0f)
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
	world = params.getValueForKey<int>("world");
	stage = params.getValueForKey<int>("stage");

	sky.Setup();
	point_light = new ci::gl::Light(ci::gl::Light::POINT, 0);
	point_light->setAmbient(ci::Color(0.7f, 0.7f, 0.7f));
	point_light->setDiffuse(ci::Color(0.75f, 0.75f, 0.75f));
	point_light->setSpecular(ci::Color(0.9f, 0.9f, 0.9f));

	light = new ci::gl::Light(ci::gl::Light::POINT, 1);
	light->setAmbient(ci::Color(0.9f, 0.9f, 0.9f));
	light->setDiffuse(ci::Color(0.95f, 0.95f, 0.95f));
	light->setSpecular(ci::Color(0.99f, 0.99f, 0.99f));

	directional_light = new ci::gl::Light(ci::gl::Light::DIRECTIONAL, 2);
	directional_light->setAmbient(ci::Color(0.2f, 0.2f, 0.2f));
	directional_light->setDiffuse(ci::Color(0.3f, 0.3f, 0.3f));
	directional_light->setSpecular(ci::Color(0.5f, 0.5f, 0.5f));
	directional_light->setDirection(ci::Vec3f(0.0f, -0.5f, 0.5f));

	// マップの準備
	map_manager.Setup(world, stage);
	// カメラの準備
	main_camera.SetInterestPoint(map_manager.GetMapCenterPos());
	main_camera.Setup(ci::JsonTree(ci::app::loadAsset("LoadFile/StageData/World" + std::to_string(world)
		+ "/Stage" + std::to_string(stage) + "/MainCamera.json")));
	main_camera.SetMapCenterPos(map_manager.GetMapCenterPos());
	main_camera.SetMoveRange(map_manager.GetMapSize() * map_manager.GetCubeScale() + ci::Vec3f(30.0f, 30.0f, 30.0f));
	// メインキューブの準備
	player_cube.SetMapPos(map_manager.GetPlayerStartPos());
	player_cube.SetScale(map_manager.GetCubeScale());
	player_cube.Setup(ci::JsonTree(ci::app::loadAsset("LoadFile/StageData/World" + std::to_string(world)
		+ "/Stage" + std::to_string(stage) + "/MainCube.json")));

	cube_cursor.Setup();

	SoundManager::Get().GetSound("MetallicWink").SetIsLoop(true);
	SoundManager::Get().GetSound("MetallicWink").Loop();

	ci::JsonTree ui_params(ci::app::loadAsset("LoadFile/UIData/GameMain.json"));
	ui_manager.Setup(ui_params);
	ui_manager.SetFuncButtonUI("retry", [this]
	{
		SoundManager::Get().GetSound("Clear").Stop();
		SoundManager::Get().GetSound("GameOver").Stop();
		next_scene = SceneType::GAMEMAIN;
		FadeManager::Get().FadeOut(EasingManager::EasingType::LINEAR,
			ci::Colorf::black(),
			0.0f, 1.0f);
	});
	ui_manager.SetFuncButtonUI("back_stage_select", [this]
	{
		SoundManager::Get().GetSound("Clear").Stop();
		SoundManager::Get().GetSound("GameOver").Stop();
		next_scene = SceneType::STAGESELECT;
		FadeManager::Get().FadeOut(EasingManager::EasingType::LINEAR,
			ci::Colorf::black(),
			0.0f, 1.0f);
		SoundManager::Get().GetSound("MetallicWink").SetIsLoop(false);
		SoundManager::Get().GetSound("MetallicWink").Stop();
	});

	if (world == SaveData::Get().GetSaveData().size() &&
		stage == STAGENUM) {
		ui_manager.FindUI<ButtonUI>("next_stage")->SetColor(ci::ColorAf(0.5f, 0.5f, 0.5f));
	}
	else
	{
		if (SaveData::Get().GetSaveData()[world - 1][stage - 1] == SaveData::StageStatus::CLEAR)
		{
			ui_manager.SetFuncButtonUI("next_stage", [this]
			{
				stage = stage % STAGENUM + 1;
				world += (stage == 1) ? 1 : 0;
				ci::JsonTree params(ci::app::loadAsset("LoadFile/StageData/SelectStage.json"));
				params["world"] = ci::JsonTree("world", world);
				params["stage"] = ci::JsonTree("stage", stage);
				params.write(ci::app::getAssetPath("LoadFile/StageData/SelectStage.json"));

				SoundManager::Get().GetSound("Clear").Stop();
				SoundManager::Get().GetSound("GameOver").Stop();
				next_scene = SceneType::GAMEMAIN;
				FadeManager::Get().FadeOut(EasingManager::EasingType::LINEAR,
					ci::Colorf::black(),
					0.0f, 1.0f);
			});
		}
		else
		{
			ui_manager.FindUI<ButtonUI>("next_stage")->SetColor(ci::ColorAf(0.5f, 0.5f, 0.5f));
		}
	}
	ui_manager.SetFuncButtonUI("menu", [this]
	{
		ui_manager.SetActive("retry", true);
		ui_manager.SetActive("back_stage_select", true);
		ui_manager.SetActive("back_game", true);
		ui_manager.SetActive("menu_bg", true);
		ui_manager.SetActive("next_stage", true);
		pause = true;
	});
	ui_manager.SetFuncButtonUI("back_game", [this]
	{
		ui_manager.SetActive("retry", false);
		ui_manager.SetActive("back_stage_select", false);
		ui_manager.SetActive("back_game", false);
		ui_manager.SetActive("menu_bg", false);
		ui_manager.SetActive("next_stage", false);
		pause = false;
	});

	ui_manager.SetActive("menu_bg", false);
	ui_manager.SetActive("retry", false);
	ui_manager.SetActive("back_stage_select", false);
	ui_manager.SetActive("back_game", false);
	ui_manager.SetActive("next_stage", false);
	ui_manager.SetActive("clear", false);
	ui_manager.SetActive("failed", false);

	FadeManager::Get().FadeIn(EasingManager::EasingType::LINEAR,
		ci::Colorf::black(),
		0.0f, 1.0f);

	ci::Vec3f target_pos = map_manager.GetStageMatrix() * player_cube.GetTransform().pos;
	
	start_delay_time = 5.0f;
	main_camera.StartMoving(target_pos,
		-5.0f, 2.0f, start_delay_time - 2.0f);

	EasingManager::Get().Register(
		&(ui_manager.FindUI<FontUI>("start")->GetTransformP()->pos.x),
		EasingManager::EasingType::LINEAR,
		1.0f, 0.5f,
		ui_manager.FindUI<FontUI>("start")->GetTransform().pos.x, -200.0f).SetEndFunc([this]
	{
		EasingManager::Get().Register(&(ui_manager.FindUI<FontUI>("start")->GetTransformP()->pos.x),
			EasingManager::EasingType::LINEAR,
			0.0f, 3.0f,
			ui_manager.FindUI<FontUI>("start")->GetTransform().pos.x, 200.0f).SetEndFunc([this]
		{
			EasingManager::Get().Register(&(ui_manager.FindUI<FontUI>("start")->GetTransformP()->pos.x),
				EasingManager::EasingType::LINEAR,
				0.0f, 0.5f,
				ui_manager.FindUI<FontUI>("start")->GetTransform().pos.x, 800.0f).SetEndFunc([this] {
				ui_manager.SetActive("start", false);
				is_start = true;
			});
		});
	});
}

void GameMain::Update()
{
	SoundManager::Get().GetSound("MetallicWink").Loop();

	start_delay_time = std::max(0.0f, start_delay_time - TimeManager::Get().GetDeltaTime());
	if (start_delay_time != 0.0f)
		return;

	if (FadeManager::Get().IsFadeOutEnd())
	{
		is_end = true;
		return;
	}

	if (!FadeManager::Get().GetisFading() && is_start)
	{
		ui_manager.Update();

		if (!pause && !is_failed && !is_goal)
		{
			main_camera.Update();

			player_cube.Update();
			map_manager.Update();
			cube_cursor.Update();

			CollisionPlayerToMap();

			ClickAction();
		}
	}
}

void GameMain::Draw(const ci::CameraOrtho &camera_ortho)
{
	ci::gl::pushModelView();
	main_camera.Draw();
	DrawObject();
	ci::gl::popModelView();

	ci::gl::pushModelView();
	ci::gl::setMatrices(camera_ortho);
	DrawUI();
	ci::gl::popModelView();
}

void GameMain::Delete()
{
	ui_manager.AllDelete();
	map_manager.AllDelete();
}

void GameMain::DrawObject()
{
	sky.Draw();
	point_light->setPosition(map_manager.GetStageMatrix() * player_cube.GetTransform().pos);
	point_light->enable();
	light->setPosition(map_manager.GetStageMatrix() * (map_manager.GetMapCenterPos() + ci::Vec3f(0.0f, 1.0f, 0.0f)));
	light->enable();
	directional_light->enable();

	ci::gl::enable(GL_LIGHTING);

	map_manager.Draw();

	ci::gl::pushModelView();
	glMultMatrixf(map_manager.GetStageMatrix());
	player_cube.Draw();
	ci::gl::popModelView();

	ci::gl::disable(GL_LIGHTING);
	if (!is_failed && !is_goal)
		cube_cursor.Draw();
}

void GameMain::DrawUI()
{
	ci::gl::translate(ci::Vec3f(0.0f, 0.0f, -10.0f));
	ui_manager.Draw();
}

void GameMain::ClickAction()
{
	ci::Ray ray = main_camera.CreateRayCameraToMouse();

	ray.setOrigin(map_manager.GetStageMatrix().inverted() * ray.getOrigin());
	ray.setDirection(map_manager.GetStageMatrix().inverted().transformVec(ray.getDirection()));

	float min_ray_distance = std::numeric_limits<float>().max();
	CubeBase *clicked_cube = nullptr;

	for (auto &cube : map_manager.GetCubes())
	{
		/*if (cube->GetType() == CubeType::NORMAL)
			continue;*/

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


	cube_cursor.SetStageMatrix(map_manager.GetStageMatrix());

	if (clicked_cube == nullptr)
		return;

	cube_cursor.SetPos(clicked_cube->GetTransform().pos);
	cube_cursor.SetScale(clicked_cube->GetTransform().scale);

	// 左クリックしていないときははじく
	if (!Mouse::Get().IsPushButton(ci::app::MouseEvent::LEFT_DOWN))
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
	if (is_failed || is_goal)
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

		SaveData::Get().ClearStage(world, stage);
		SaveData::Get().WriteCsv();
		SoundManager::Get().GetSound("MetallicWink").SetIsLoop(false);
		SoundManager::Get().GetSound("MetallicWink").Stop();
		SoundManager::Get().GetSound("Clear").Play();
		is_goal = true;

		{
			ci::Vec3f target_pos = map_manager.GetStageMatrix() * player_cube.GetTransform().pos;
			main_camera.EndMoving(target_pos,
				-5.0f, 0.0f, 2.0f);
		}

		ui_manager.SetActive("menu", false);
		ui_manager.SetActive("menu_font", false);
		ui_manager.SetActive("clear", true);
		EasingManager::Get().Register(
			&(ui_manager.FindUI<FontUI>("clear")->GetTransformP()->scale.x),
			EasingManager::EasingType::QUARTIN,
			0.0f, 2.0f,
			0.0f, ui_manager.FindUI<FontUI>("clear")->GetTransform().scale.x);
		EasingManager::Get().Register(
			&(ui_manager.FindUI<FontUI>("clear")->GetTransformP()->scale.y),
			EasingManager::EasingType::QUARTIN,
			0.0f, 2.0f,
			0.0f, ui_manager.FindUI<FontUI>("clear")->GetTransform().scale.y).SetEndFunc([this] {
			Goal();
		});
		ui_manager.FindUI<FontUI>("clear")->SetScale(ci::Vec3f::zero());
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
	SoundManager::Get().GetSound("MetallicWink").SetIsLoop(false);
	SoundManager::Get().GetSound("MetallicWink").Stop();
	SoundManager::Get().GetSound("GameOver").Play();

	ci::Vec3f target_pos = map_manager.GetStageMatrix() * player_cube.GetTransform().pos;
	main_camera.EndMoving(target_pos,
	-5.0f, 0.0f, 3.5f);

	ui_manager.SetActive("menu", false);
	ui_manager.SetActive("menu_font", false);
	ui_manager.SetActive("failed", true);
	EasingManager::Get().Register(
		&(ui_manager.FindUI<FontUI>("failed")->GetTransformP()->pos.y),
		EasingManager::EasingType::BOUNCEOUT,
		0.0f, 3.5f,
		600.0f, ui_manager.FindUI<FontUI>("failed")->GetTransform().pos.y).SetEndFunc([this] {
		Failed();
	});
	ui_manager.FindUI<FontUI>("failed")->SetPos(ui_manager.FindUI<FontUI>("failed")->GetTransform().pos + ci::Vec3f::yAxis() * 600.0f);
}

void GameMain::Failed()
{
	ui_manager.SetActive("retry", true);
	ui_manager.SetActive("back_stage_select", true);
	ui_manager.SetActive("menu_bg", true);
	ui_manager.SetActive("menu", false);
	ui_manager.SetActive("menu_font", false);
}

void GameMain::Goal()
{
	ui_manager.SetActive("retry", true);
	ui_manager.SetActive("back_stage_select", true);
	ui_manager.SetActive("menu_bg", true);
	ui_manager.SetActive("menu", false);
	ui_manager.SetActive("menu_font", false);
	ui_manager.SetActive("next_stage", true);
}
