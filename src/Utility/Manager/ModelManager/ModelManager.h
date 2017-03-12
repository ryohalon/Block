#pragma once
#include "Model/Model.h"
#include <map>



class ModelManager
{
public:

	ModelManager();
	~ModelManager();

	static ModelManager& Get()
	{
		static ModelManager model_manager;

		return model_manager;
	}

	void Setup();
	void AllDelete();
	void DeleteModel(const std::string &name);
	Model& GetModel(const std::string &name);

private:

	void Register(const std::string &file_path, const std::string &name);

	std::map <std::string, Model> models;

};