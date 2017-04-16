#pragma once
#include "../GameObject/UIBase/UIBase.h"


class UIManager : public Object
{
public:

	UIManager();
	~UIManager();

	void AllDelete();
	void SetFuncButtonUI(const std::string &name, const std::function<void()> &func);
	void SetActive(const std::string &name, const bool &is_active)
	{
		if (uis.find(name) == uis.cend())
			assert(!"[name] is not exist");

		uis[name]->SetActive(is_active);
	}
	template <typename T>
	T* FindUI(const std::string &name)
	{
		if (uis.find(name) == uis.cend())
			assert(!"[name] is not exist");

		return static_cast<T*>(uis[name]);
	}
	void AddUI(std::string name, UIBase *ui) {
		uis.insert(std::make_pair(name, ui));
	}

	void Setup(const ci::JsonTree &params);
	void Update();
	void Draw();

private:

	std::map<std::string, UIBase*> uis;
};