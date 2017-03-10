#include "SpringCube.h"

SpringCube::SpringCube()
{

}

SpringCube::SpringCube(const CubeBase & cube_base,
	const ci::Vec2f & spring_power,
	const float & spring_take_time) :
	CubeBase(cube_base),
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
