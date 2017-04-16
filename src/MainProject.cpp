#include "cinder/app/AppNative.h"
#include <cinder/Json.h>
#include "Scene/SceneManager/SceneManager.h"
#include "Utility/Input/Key/Key.h"
#include "Utility/Input/Mouse/Mouse.h"

class MainProject : public ci::app::AppNative
{
private:

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
	ci::JsonTree params(ci::app::loadAsset("LoadFile/WindowSize/WindowSize.json"));

	settings->setWindowSize(params.getValueForKey<int>("width"),
		params.getValueForKey<int>("height"));
	settings->setFullScreen(false);
	settings->setFrameRate(60);
}

void MainProject::setup()
{
	SceneManager::Get().Setup();
}

void MainProject::resize()
{
	SceneManager::Get().Resize();
}

void MainProject::update()
{
	SceneManager::Get().Update();
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
