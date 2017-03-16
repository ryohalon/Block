#pragma once
#include "../GameObject/UIBase/TextureUI/ButtonUI/StageUI/StageUI.h"


class UIManager : public Object
{
public:

	UIManager();
	~UIManager();

	void Setup();
	void Update();
	void Draw();

private:

	std::map<std::string, UIBase*> UIs;
};