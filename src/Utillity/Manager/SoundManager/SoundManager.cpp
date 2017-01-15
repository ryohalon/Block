#include "SoundManager.h"

SoundManager::SoundManager()
{
	context = ci::audio::master();
	context->enable();
}

SoundManager::~SoundManager()
{

}

void SoundManager::Setup()
{
	Register(ci::app::getAssetPath("LoadFile/SoundPath.txt").string());
}

void SoundManager::Register(const std::string &file_path)
{
	std::ifstream list_path(file_path);
	std::string sound_path;
	std::string name;
	int type;


	std::function<ci::audio::SamplePlayerNodeRef()> CreateSound[] =
	{
		[&] {
		ci::audio::FilePlayerNodeRef file_player;
		file_player = context->makeNode(new ci::audio::FilePlayerNode());
		ci::audio::SourceFileRef source = ci::audio::load(ci::app::loadAsset(sound_path));
		file_player->setSourceFile(source);

		return file_player;
	},
		[&] {
		ci::audio::BufferPlayerNodeRef buffer_player;
		buffer_player = context->makeNode(new ci::audio::BufferPlayerNode());
		ci::audio::SourceFileRef source = ci::audio::load(ci::app::loadAsset(sound_path));
		buffer_player->loadBuffer(source);

		return buffer_player;
	}
	};


	while (!list_path.eof())
	{
		list_path >> type;
		list_path >> name;
		list_path >> sound_path;

		if (sounds.find(name) != sounds.cend())
			assert(!"name‚ª‚·‚Å‚ÉŽg‚í‚ê‚Ä‚¢‚Ü‚·");

		Sound sound = Sound(CreateSound[type](), context);
		sounds.insert(std::make_pair(name, sound));
	}
}

void SoundManager::Delete(const std::string & name)
{
	if (sounds.find(name) == sounds.cend())
		assert(!"[name]‚Ì–¼‘O‚Ì•t‚¢‚½[sound]‚ª“o˜^‚³‚ê‚Ä‚Ü‚¹‚ñ");

	sounds.erase(sounds.find(name));
}

void SoundManager::AllDelete()
{
	sounds.clear();
}

Sound& SoundManager::Find(const std::string & name)
{
	if (sounds.find(name) == sounds.cend())
		assert(!"[name]‚Ì–¼‘O‚Ì•t‚¢‚½[sound]‚ª“o˜^‚³‚ê‚Ä‚Ü‚¹‚ñ");

	return sounds.find(name)->second;
}

void SoundManager::AllStop()
{
	for (auto &sound : sounds)
		sound.second.Stop();
}
