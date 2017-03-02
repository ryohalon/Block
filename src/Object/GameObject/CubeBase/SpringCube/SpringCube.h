#pragma once
#include "../CubeBase.h"


class SpringCube : public CubeBase
{
public:

	SpringCube();
	SpringCube(const ci::Vec3f &pos,
		const ci::Vec3f &angle,
		const ci::Vec3f &scale,
		const ci::gl::Material &material,
		const CubeType &type,
		const ci::Vec3i &map_pos,
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