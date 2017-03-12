#include "ModelManager.h"
#include "../../Utility.h"
#include <filesystem>

ModelManager::ModelManager()
{

}

ModelManager::~ModelManager()
{

}

void ModelManager::Setup()
{
	ci::JsonTree params(ci::app::loadAsset("LoadFile/DirectoryData/DirectoryData.json"));
	std::string directory_path = params.getValueForKey<std::string>("model");

	for (std::tr2::sys::directory_iterator itr(GetFilePath(directory_path)), end; itr != end; itr++)
	{
		std::string directory_name = itr->path().string().substr(GetFilePath(directory_path).size(), itr->path().string().size() - 1);

		Register(directory_path + directory_name,
			directory_name);
	}
}


void ModelManager::AllDelete()
{
	models.clear();
}

void ModelManager::DeleteModel(const std::string & name)
{
#ifdef _DEBUG
	if (models.find(name) == models.cend())
		assert(!"error : [name] does not exist");
#endif

	models.erase(name);
}

Model & ModelManager::GetModel(const std::string & name)
{
#ifdef _DEBUG
	if (models.find(name) == models.cend())
		assert(!"error : [name] does not exist");
#endif
	
	return models[name];
}

void ModelManager::Register(const std::string & file_path, const std::string & name)
{
	Model model;
	model.Setup(file_path, name);
	models.insert(std::make_pair(name, model));
}