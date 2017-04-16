#include "UIManager.h"
#include "../GameObject/UIBase/FontUI/FontUI.h"
#include "../GameObject/UIBase/TextureUI/ButtonUI/ButtonUI.h"


UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

void UIManager::AllDelete()
{
	for (auto &ui : uis)
		delete ui.second;

	uis.clear();
}

void UIManager::SetFuncButtonUI(const std::string & name, const std::function<void()>& func)
{
	if (uis.find(name) == uis.cend())
		assert(!"[name] is not exist");

	ButtonUI *button_ui = static_cast<ButtonUI*>(uis[name]);
	button_ui->SetClickedFunc(func);
}

void UIManager::Setup(const ci::JsonTree & params)
{
	for (auto &ui_data : params)
	{
		std::string ui_type = ui_data.getValueForKey<std::string>("type");
		if (ui_type == "texture")
		{
			TextureUI *texture_ui = new TextureUI();
			texture_ui->Setup(ui_data);
			uis.insert(std::make_pair(ui_data.getValueForKey<std::string>("name"), texture_ui));
		}
		else if (ui_type == "font")
		{
			FontUI *font_ui = new FontUI();
			font_ui->Setup(ui_data);
			uis.insert(std::make_pair(ui_data.getValueForKey<std::string>("name"), font_ui));
		}
		else if (ui_type == "button")
		{
			ButtonUI *button_ui = new ButtonUI();
			button_ui->Setup(ui_data);
			uis.insert(std::make_pair(ui_data.getValueForKey<std::string>("name"), button_ui));
		}
	}
}

void UIManager::Update()
{
	for (auto &ui : uis)
		ui.second->Update();
}

void UIManager::Draw()
{
	for (auto &ui : uis)
		ui.second->Draw();
}
