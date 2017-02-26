#include "GameMain.h"
#include "../../../Utility/Utility.h"
#include "../../../Utility/Input/Mouse/Mouse.h"


GameMain::GameMain() :
	is_failed(false),
	failed_fall_pos_y(-10.0f)
{

}

GameMain::~GameMain()
{

}

void GameMain::Resize()
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

	camera.Setup();
	/*camera.Setup(ci::Vec3f(-5.0f, 10.0f, -5.0f),
		ci::Vec3f(5.0f, -5.0f, 5.0f),
		45.0f, 0.1f, 2000.0f);*/
	sky.Setup();
	point_light = new ci::gl::Light(0, ci::gl::Light::POINT);
	point_light->setAmbient(ci::Color(0.5f, 0.5f, 0.5f));
	point_light->setDiffuse(ci::Color(0.6f, 0.6f, 0.6f));
	point_light->setSpecular(ci::Color(0.8f, 0.8f, 0.8f));
#endif

	// マップの準備
	map_manager.Setup(world, stage);
	// メインキューブの準備
	main_cube.Setup(ci::JsonTree(ci::app::loadAsset("LoadFile/StageData/World" + std::to_string(world)
		+ "/Stage" + std::to_string(stage) + "/MainCube.json")));
}

void GameMain::Update()
{
#ifdef _DEBUG
	camera.Update();
#endif

	main_cube.Update();
	map_manager.Update();

	CollisionPlayerToMap();

	ClickAction();
}

void GameMain::Draw()
{
	ci::gl::pushModelView();

#ifdef _DEBUG
	camera.Draw();
	glCullFace(GL_FRONT);
	sky.Draw();
	glCullFace(GL_BACK);
	point_light->setPosition(main_cube.GetTransform().pos);
	point_light->enable();
#endif

	ci::gl::enable(GL_LIGHTING);

	map_manager.Draw();
	main_cube.Draw();


	ci::gl::disable(GL_LIGHTING);
	ci::gl::popModelView();
}

void GameMain::ClickAction()
{
	// 左クリックしていないときははじく
	if (!Mouse::Get().IsPushButton(ci::app::MouseEvent::LEFT_DOWN))
		return;

	// マウス座標を(0,0)~(1,1)の範囲に正規化する
	//		マウスの座標はYの下方向がプラス
	//      表示座標はYの上方向がプラス
	//      向きが逆なので、補正します
	ci::Vec2f mouse_pos_window_ratio = ci::Vec2f(
		static_cast<float>(Mouse::Get().GetMousePosition().x) / ci::app::getWindowSize().x,
		1.0f - static_cast<float>(Mouse::Get().GetMousePosition().y) / ci::app::getWindowSize().y);

	ci::Ray ray = camera.GetCamera().generateRay(
		mouse_pos_window_ratio.x,
		mouse_pos_window_ratio.y,
		ci::app::getWindowAspectRatio());

	float min_ray_distance = std::numeric_limits<float>().max();
	CubeBase *clicked_cube = nullptr;

	ci::app::console() << "ratio : " << mouse_pos_window_ratio << std::endl
		<< "min_ray_distance :" << min_ray_distance << std::endl;

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

	if (clicked_cube->GetType() == CubeType::SHRINK)
	{
		ShrinkCube *shrink_cube = static_cast<ShrinkCube*>(clicked_cube);
		if (shrink_cube->GetShrinkDirection() == ShrinkCube::ShrinkDirection::UP)
		{
			if (clicked_cube->GetMapPos() + ci::Vec3i(0, 1, 0) == main_cube.GetMapPos())
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
	if (!main_cube.GetIsStop())
		return;
	if (main_cube.GetIsMoving())
		return;
	if (main_cube.GetIsFalling())
		return;

	// まず真下のマップ情報を見る
	// 　何もなかった場合 : 
	// 　　下にキューブがある場合 : そのキューブの上まで落ちる
	// 　　下にキューブがない場合 : 画面外まで落ちてゲームオーバーにする　この後のリスタート処理はどうするかは未定
	// 　キューブがある場合 :
	// 　　普通のキューブ : メインキューブの移動方向のキューブを調べる
	// 　　　何もない場合 : 移動
	// 　　　キューブがある場合 : 
	// 　　　　普通のキューブ : 移動方向の変更　そのあとすぐ移動するか、1フレーム後にするかは未定
	// 　　Vanish : オン、オフで変わる
	// 　　　オン : ないものとして処理する
	// 　　　オフ : 普通のキューブとして処理する

	SearchUnderCube(main_cube.GetMapPos());
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
	case CubeType::NORMAL:

		SearchMoveDirectionCube(player_map_pos,
			static_cast<int>(main_cube.GetMoveDirection()));
		break;
	case CubeType::SHRINK:

		SearchMoveDirectionCube(player_map_pos,
			static_cast<int>(main_cube.GetMoveDirection()));
		break;
	case CubeType::VANISH:

		VanishCube *cube = map_manager.GetCube<VanishCube>(player_map_pos + ci::Vec3i(0, -1, 0));
		if (cube->GetMapPos() == (ci::Vec3i::one() * -1))
			assert(!"error : 存在しないキューブです");

		if (cube->GetIsVanish())
			SetFallPos(player_map_pos);
		else
			SearchMoveDirectionCube(player_map_pos,
				static_cast<int>(main_cube.GetMoveDirection()));

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
		main_cube.MoveStart();
		break;
	case CubeType::NORMAL:
		main_cube.Hit();
		break;
	case CubeType::SHRINK:
		main_cube.Hit();
		break;
	case CubeType::VANISH:

		VanishCube *cube = map_manager.GetCube<VanishCube>(player_map_pos + ci::Vec3i(0, -1, 0));
		if (cube->GetMapPos() == (ci::Vec3i::one() * -1))
			assert(!"error : 存在しないキューブです");

		if (cube->GetIsVanish())
			main_cube.MoveStart();
		else
			main_cube.Hit();


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
			main_cube.FallStart(ci::Vec3f(
				static_cast<float>(player_map_pos.x),
				static_cast<float>(y + 1),
				static_cast<float>(player_map_pos.z)));
			return;
		case CubeType::SHRINK:
			main_cube.FallStart(ci::Vec3f(
				static_cast<float>(player_map_pos.x),
				static_cast<float>(y + 1),
				static_cast<float>(player_map_pos.z)));
			return;
		case CubeType::VANISH:

			VanishCube *cube = map_manager.GetCube<VanishCube>(player_map_pos + ci::Vec3i(0, -1, 0));
			if (cube->GetMapPos() == (ci::Vec3i::one() * -1))
				assert(!"error : 存在しないキューブです");

			if (!cube->GetIsVanish())
				main_cube.FallStart(ci::Vec3f(
					static_cast<float>(player_map_pos.x),
					static_cast<float>(y + 1),
					static_cast<float>(player_map_pos.z)));

			break;
		}
	}

	is_failed = true;
	main_cube.FallStart(ci::Vec3f(
		static_cast<float>(player_map_pos.x),
		failed_fall_pos_y,
		static_cast<float>(player_map_pos.z)));
}
