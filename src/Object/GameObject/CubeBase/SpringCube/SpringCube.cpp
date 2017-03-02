#include "SpringCube.h"

SpringCube::SpringCube()
{

}

SpringCube::SpringCube(const ci::Vec3f & pos,
	const ci::Vec3f & angle,
	const ci::Vec3f & scale,
	const ci::gl::Material & material,
	const CubeType & type,
	const ci::Vec3i & map_pos,
	const ci::Vec2f & spring_power,
	const float & spring_take_time) :
	CubeBase(pos, angle, scale, material, type, map_pos),
	spring_power(spring_power),
	time(0.0f),
	spring_take_time(spring_take_time),
	is_spring(false)
{

}

SpringCube::~SpringCube()
{

}

void SpringCube::Setup()
{

}

void SpringCube::Update()
{

}

void SpringCube::Draw()
{

}
