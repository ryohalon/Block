#pragma once
#include "../../SceneBase.h"



class GameMain : public SceneBase
{
public:

	GameMain();
	~GameMain();

	void Resize() override;
	void Setup() override;
	void Update() override;
	void Draw() override;

private:


};