#pragma once
#include "../CubeBase.h"


class SpringCube : public CubeBase
{
public:

	SpringCube();
	SpringCube(const CubeBase &cube_base,
		const ci::Vec2f &spring_power,
		const float &spring_take_time);
	~SpringCube();

	void Setup() override;
	void Update() override;
	void Draw() override;

private:

	ci::Vec2f spring_power;
	float time, spring_take_time;
	bool is_spring;
};