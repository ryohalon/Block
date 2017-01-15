#pragma once
#include "../../SceneBase.h"



class Title : public SceneBase
{
public:

	Title();
	~Title();

	void Resize() override;
	void Setup() override;
	void Update() override;
	void Draw() override;

private:


};