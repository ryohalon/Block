#include "GameMain.h"
#include "../../../Utility/Utility.h"
#include "../../../Utility/Input/Mouse/Mouse.h"


GameMain::GameMain()
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
	ci::app::console() << world << ',' << stage << std::endl;

	camera.Setup();
	sky.Setup();
#endif

	// マップの準備
	map_manager.Setup(ci::JsonTree(ci::app::loadAsset("LoadFile/StageData/World" + std::to_string(world)
		+ "/Stage" + std::to_string(stage) + "/Stage.json")));
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


}

void GameMain::Draw()
{
	ci::gl::pushModelView();

#ifdef _DEBUG
	camera.Draw();
	glCullFace(GL_FRONT);
	sky.Draw();
	glCullFace(GL_BACK);
#endif

	map_manager.Draw();
	main_cube.Draw();
	ci::gl::popModelView();
}

void GameMain::ClickAction()
{
	// 左クリックしていないときははじく
	if (!Mouse::Get().IsPushButton(ci::app::MouseEvent::LEFT_DOWN))
		return;

	// マップ上の特殊なキューブとのカメラからのRayで当たり判定をとって
	// 　一番近いキューブのアクションを起こす
	// 未実装


}

void GameMain::CollisionPlayerToMap()
{
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


}
