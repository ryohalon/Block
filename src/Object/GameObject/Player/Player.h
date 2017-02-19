#pragma once
#include "../CubeBase/AutoMoveCube/AutoMoveCube.h"


class Player
{
public:

	Player();
	~Player();

	void Setup(const ci::JsonTree &params);
	void Update();
	void Draw();

private:

	void LoadStatus();

	CubeBase *cube;
};