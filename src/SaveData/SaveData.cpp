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
	if (save_data.size() != 0)
		return;

	std::string file_path = "LoadFile/SaveData/SaveData.csv";
	std::ifstream file(GetFilePath(file_path));
	std::string line;
	while (std::getline(file, line))
	{
		std::vector<int> world_save_data;
		for (int i = 0; i < line.size(); i += 2)
			world_save_data.push_back(boost::lexical_cast<int>(line[i]));

		save_data.push_back(world_save_data);
		world_save_data.clear();
	}
}

void SaveData::WriteCsv()
{
	std::string file_path = "LoadFile/SaveData/SaveData.csv";
	std::ofstream file(GetFilePath(file_path));
	for (int i = 0; i < static_cast<int>(save_data.size()); i++)
	{
		for (int k = 0; k < STAGENUM; k++)
		{
			file << save_data[i][k];
			if (k < STAGENUM - 1)
				file << ',';
		}

		file << std::endl;
	}
}

void SaveData::ClearStage(int world, int stage)
{
	world--;
	stage--;
	save_data[world][stage] = StageStatus::CLEAR;
	world += ((stage + 1) == STAGENUM) ? 1 : 0;
	stage = (stage + 1) % save_data[0].size();
	if (save_data[world][stage] == StageStatus::LOCK)
		save_data[world][stage] = StageStatus::OPEN;
}

void SaveData::DeleteSaveData()
{
	save_data[0][0] = StageStatus::OPEN;
	for (int i = 0; i < static_cast<int>(save_data.size()); i++)
	{
		for (int k = 0; k < static_cast<int>(save_data[i].size()); k++)
		{
			if (i == 0 && k == 0)
				continue;

			save_data[i][k] = StageStatus::LOCK;
		}
	}

	std::string file_path = "LoadFile/SaveData/SaveData.csv";
	std::ofstream file(GetFilePath(file_path));
	for (int i = 0; i < static_cast<int>(save_data.size()); i++)
	{
		for (int k = 0; k < STAGENUM; k++)
		{
			file << save_data[i][k];
			if (k < STAGENUM - 1)
				file << ',';
		}

		file << std::endl;
	}

	WriteCsv();
}
