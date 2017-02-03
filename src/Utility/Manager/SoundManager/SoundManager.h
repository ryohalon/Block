#pragma once
#include "Sound/Sound.h"
#include <map>



class SoundManager
{
public:

	enum SoundType
	{
		FILEPLAYER = 0,
		BUFFERPLAYER = 1
	};

	SoundManager();
	~SoundManager();

	static SoundManager& Get()
	{
		static SoundManager sound_manager;

		return sound_manager;
	}

	void Setup();

	void Register(const std::string &file_path);
	void Delete(const std::string &name);
	void AllDelete();
	Sound& Find(const std::string &name);
	void AllStop();

private:

	std::map<std::string, Sound> sounds;
	ci::audio::Context *context;

};