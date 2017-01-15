#pragma once
#include "../../SceneBase.h"



class Option : public SceneBase
{
public:

	Option();
	~Option();

	void Resize() override;
	void Setup() override;
	void Update() override;
	void Draw() override;

private:


};