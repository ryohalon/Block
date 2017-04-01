#include "VanishCube.h"

VanishCube::VanishCube() :
	is_vanish(false)
{

}

VanishCube::VanishCube(const CubeBase & cube_base,
	const bool & is_vanish) :
	CubeBase(cube_base),
	is_vanish(is_vanish)
{

}

VanishCube::~VanishCube()
{

}

void VanishCube::Setup()
{
	UpdateMatrix();
}

void VanishCube::Update()
{
	
}

void VanishCube::Draw()
{
	ci::gl::pushModelView();

	glMultMatrixf(matrix);

	material.apply();

	if (is_vanish)
		ci::gl::drawStrokedCube(ci::Vec3f::zero(), ci::Vec3f::one());
	else
		ci::gl::drawCube(ci::Vec3f::zero(), ci::Vec3f::one());

	ci::gl::popModelView();
}

void VanishCube::Clicked()
{
	is_vanish = !is_vanish;
	
	SoundManager::Get().GetSound("Vanish").Play();
}
