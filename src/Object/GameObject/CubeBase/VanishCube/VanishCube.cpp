#include "VanishCube.h"

VanishCube::VanishCube() :
	is_vanish(false)
{

}

VanishCube::~VanishCube()
{

}

void VanishCube::Setup()
{

}

void VanishCube::Update()
{


	UpdateMatrix();
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
