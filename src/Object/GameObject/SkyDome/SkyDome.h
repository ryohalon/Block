#pragma once
#include "../GameObject.h"



class SkyDome : public GameObject
{
public:

	SkyDome();
	SkyDome(const ci::Vec3f &pos,
		const float &radius = 1000.0f,
		const int &segments = 100);
	~SkyDome();

	void Setup() override;
	void Update() override;
	void Draw() override;

private:

	int segments;

};