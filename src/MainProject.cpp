#include "cinder/app/AppNative.h"
#include "Scene/SceneManager/SceneManager.h"



class MainProject : public ci::app::AppNative
{
private:

	enum WindowSize
	{
		WIDTH = 1024,
		HEIGHT = 786
	};

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
	SceneManager::Get().Update();

	Mouse::Get().FlushInput();
	Key::Get().FlushInput();
}

void MainProject::draw()
{
	SceneManager::Get().Draw();
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
