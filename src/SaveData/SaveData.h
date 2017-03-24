#pragma once
#include <vector>
#include <assert.h>



class SaveData
{
public:

	enum StageStatus
	{
		OPEN,
		CLEAR,
		LOCK
	};

	SaveData();
	~SaveData();

	static SaveData& Get()
	{
		static SaveData save_data;

		return save_data;
	}

	const std::vector<std::vector<int>>& GetSaveData() const { return save_datas; }
	int GetWorldNum() const { return save_datas.size(); }
	int GetStageNum() const { return save_datas[0].size(); }

	void LoadSaveData();
	void ClearStage(int world, int stage);
	void DeleteSaveData();

private:

	std::vector<std::vector<int>> save_datas;
};