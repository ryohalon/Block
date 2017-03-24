#include "SaveData.h"
#include "../Utility/Utility.h"

SaveData::SaveData()
{

}

SaveData::~SaveData()
{

}

void SaveData::LoadSaveData()
{
	std::string file_path = "LoadFile/SaveData/SaveData.csv";
	std::ifstream file(GetFilePath(file_path));
	std::string line;
	while (std::getline(file, line))
	{
		std::vector<int> world_save_data;
		for (int i = 0; i < static_cast<int>(line.size()); i += 2)
			world_save_data.push_back(boost::lexical_cast<int>(line[i]));

		save_datas.push_back(world_save_data);
		world_save_data.clear();
	}
}

void SaveData::ClearStage(int world, int stage)
{
	world--;
	stage--;
	save_datas[world][stage] = StageStatus::CLEAR;
	world += ((stage + 1) == 10) ? 1 : 0;
	stage = (stage + 1) % save_datas[0].size();
	if (save_datas[world][stage] == StageStatus::LOCK)
		save_datas[world][stage] = StageStatus::OPEN;
}

void SaveData::DeleteSaveData()
{
	save_datas[0][0] = StageStatus::OPEN;
	for (int i = 0; i < static_cast<int>(save_datas.size()); i++)
	{
		for (int k = 0; k < static_cast<int>(save_datas[i].size()); k++)
		{
			if (i == 0 && k == 0)
				continue;

			save_datas[i][k] = StageStatus::LOCK;
		}
	}

	std::string file_path = "LoadFile/SaveData/SaveData.csv";
	std::ofstream file(GetFilePath(file_path));
	for (int i = 0; i < static_cast<int>(save_datas.size()); i++)
	{
		for (int k = 0; k < static_cast<int>(save_datas[i].size()); k++)
		{
			file << save_datas[i][k];
			if (k < static_cast<int>(save_datas[i].size()) - 1)
				file << ',';
			if (k == static_cast<int>(save_datas[i].size()) - 1)
				file << std::endl;
		}
	}
}
