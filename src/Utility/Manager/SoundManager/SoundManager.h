#pragma once
#include "Sound/Sound.h"
#include <map>



class SoundManager
{
public:

	enum SoundType
	{
		FILEPLAYER,
		BUFFERPLAYER
	};

	SoundManager();
	~SoundManager();

	static SoundManager& Get()
	{
		static SoundManager sound_manager;

		return sound_manager;
	}

	void Setup();
	void Delete(const std::string &name);
	void AllDelete();
	Sound& GetSound(const std::string &name);
	void AllStop();
	void ChangeGain(const std::string &name, float gain);

private:

	void LoadBGM(std::string directory_path);
	void LoadSE(std::string directory_path);
	void Register(const std::string &file_path,
		const SoundType &type,
		const std::string &name);
	void SetupGain();

	std::map<std::string, Sound> sounds;
	ci::audio::Context *context;

};