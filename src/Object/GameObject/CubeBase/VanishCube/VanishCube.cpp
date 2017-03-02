#include "VanishCube.h"

VanishCube::VanishCube() :
	is_vanish(false)
{

}

VanishCube::VanishCube(const ci::Vec3f & pos,
	const ci::Vec3f & angle,
	const ci::Vec3f & scale,
	const ci::gl::Material & material,
	const CubeType & type,
	const ci::Vec3i & map_pos,
	const bool & is_vanish) :
	CubeBase(pos, angle, scale, material, type, map_pos),
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
}
