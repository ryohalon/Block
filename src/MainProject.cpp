#include "cinder/app/AppNative.h"
#include "Scene/SceneManager/SceneManager.h"
#include "NotUse/MainCamera/MainCamera.h"
#include "Object/GameObject/SkyDome/SkyDome.h"
#include "Object/GameObject/CubeBase/AutoMoveCube/AutoMoveCube.h"
#include "Object/GameObject/CubeBase/ShrinkCube/ShrinkCube.h"



class MainProject : public ci::app::AppNative
{
private:

	enum WindowSize
	{
		WIDTH = 1024,
		HEIGHT = 786
	};

	AutoMoveCube auto_move_cube;
	MainCamera camera;
	std::vector<CubeBase*> cubes;
	SkyDome sky_dome;
	

public:
	void prepareSettings(Settings *settings) override;
	void setup() override;
	void resize() override;
	void update() override;
	void draw() override;
	void mouseMove(ci::app::MouseEvent event) override;
	void mouseDrag(ci::app::MouseEvent event) override;
	void mouseWheel(ci::app::MouseEvent event) override;
	void mouseDown(ci::app::MouseEvent event) override;
	void mouseUp(ci::app::MouseEvent event) override;
	void keyDown(ci::app::KeyEvent event) override;
	void keyUp(ci::app::KeyEvent event) override;
};

void MainProject::prepareSettings(Settings * settings)
{
	settings->setWindowSize(WindowSize::WIDTH, WindowSize::HEIGHT);
	settings->setFullScreen(false);
}

void MainProject::setup()
{
	//SoundManager::Get().Setup();
	TextureManager::Get().Setup();

	SceneManager::Get().Setup();

	auto_move_cube.Setup();
	sky_dome.Setup();
	camera.Setup();
	for (int i = 0; i < 30; i++)
	{
		for (int k = 0; k < 30; k++)
		{
			CubeBase *cube = new CubeBase();
			cube->SetPos(ci::Vec3f(k, -1.0f, i));
			cube->SetScale(ci::Vec3f::one() * 0.9f);
			cube->SetColor(ci::ColorA(0.1f, 0.1f, 1.0f));
			cube->Setup();
			cubes.push_back(cube);
		}
	}

	ShrinkCube *shrink_cube = new ShrinkCube();
	shrink_cube->SetPos(ci::Vec3f(30.0f, -1.0f, 30.0f));
	shrink_cube->SetScale(ci::Vec3f::one() * 0.9f);
	shrink_cube->SetOriginScale(ci::Vec3f::one() * 0.9f);
	shrink_cube->SetShrinkValue(ci::Vec3f(0.9f, 0.9f, 2.0f));
	shrink_cube->SetColor(ci::ColorA(0.1f, 1.0f, 0.1f));
	shrink_cube->Setup();
	//shrink_cube->AlreadyShrink();
	cubes.push_back(shrink_cube);

	ci::gl::enableAlphaBlending();
	ci::gl::enableDepthRead();
	ci::gl::enableDepthWrite();
	glCullFace(GL_BACK);
}

void MainProject::resize()
{
	SceneManager::Get().Resize();
}

void MainProject::update()
{
	TimeManager::Get().Update(
		static_cast<float>(getElapsedSeconds()),
		static_cast<int>(getElapsedFrames()));

	//SceneManager::Get().Update();

	camera.Update();
	auto_move_cube.Update();
	for (auto &cube : cubes)
		cube->Update();

	Mouse::Get().FlushInput();
	Key::Get().FlushInput();
}

void MainProject::draw()
{
	//SceneManager::Get().Draw();

	ci::gl::clear();
	ci::gl::pushModelView();
	camera.Draw();

	sky_dome.Draw();

	auto_move_cube.Draw();
	for (auto &cube : cubes)
		cube->Draw();

	ci::gl::popModelView();
}

void MainProject::mouseMove(ci::app::MouseEvent event)
{
	Mouse::Get().UpdateMousePosition(event);
}

void MainProject::mouseDrag(ci::app::MouseEvent event)
{
	Mouse::Get().UpdateMousePosition(event);
}

void MainProject::mouseWheel(ci::app::MouseEvent event)
{
	Mouse::Get().UpdateMouseWheelValue(event);
}

void MainProject::mouseDown(ci::app::MouseEvent event)
{
	Mouse::Get().PushButton(event);
}

void MainProject::mouseUp(ci::app::MouseEvent event)
{
	Mouse::Get().PullButton(event);
}

void MainProject::keyDown(ci::app::KeyEvent event)
{
	Key::Get().PushKey(event);
}

void MainProject::keyUp(ci::app::KeyEvent event)
{
	Key::Get().PullKey(event);
}

CINDER_APP_NATIVE(MainProject, ci::app::RendererGl)
