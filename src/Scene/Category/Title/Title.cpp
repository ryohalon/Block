#include "Title.h"

Title::Title()
{

}

Title::~Title()
{

}

void Title::Resize()
{

}

void Title::Setup()
{

}

void Title::Update()
{
	if (Mouse::Get().IsPushButton(ci::app::MouseEvent::LEFT_DOWN))
		is_end = true;
}

void Title::Draw()
{

}
