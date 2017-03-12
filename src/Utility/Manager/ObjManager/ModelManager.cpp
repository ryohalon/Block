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
	std::string folder_name = "Resource/Model/";

	std::tr2::sys::directory_iterator directory_itr;

	for (std::tr2::sys::directory_iterator itr(GetFilePath(folder_name)), end; itr != end; itr++)
	{
		ci::app::console() << itr->path().string() << std::endl;
		std::string file_name = itr->path().string();
	}
}

void ModelManager::Register(const std::string & file_path, const std::string & name)
{

}

void ModelManager::AllDelete()
{

}
