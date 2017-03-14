#include "SoundManager.h"
#include "../../Utility.h"
#include <cinder/app/App.h>
#include <filesystem>

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
	ci::JsonTree params(ci::app::loadAsset("LoadFile/DirectoryData/DirectoryData.json"));
	std::string directory_path = params.getValueForKey<std::string>("sound");

	LoadBGM(directory_path);
	LoadSE(directory_path);
}

void SoundManager::LoadBGM(std::string directory_path)
{
	directory_path += "BGM/";
	for (std::tr2::sys::directory_iterator end, itr(GetFilePath(directory_path)); itr != end; itr++)
	{
		std::string file_name = itr->path().string().substr(GetFilePath(directory_path).size(), itr->path().string().size() - 1);

		// wav‚¾‚¯‚È‚Ì‚Å¡‚ÍŒˆ‚ß‘Å‚¿‚É‚µ‚Ä‚¢‚é
		Register(directory_path + file_name,
			SoundType::FILEPLAYER,
			file_name.substr(0, file_name.size() - 4));
	}
}

void SoundManager::LoadSE(std::string directory_path)
{
	directory_path += "SE/";
	for (std::tr2::sys::directory_iterator end, itr(GetFilePath(directory_path)); itr != end; itr++)
	{
		std::string file_name = itr->path().string().substr(GetFilePath(directory_path).size(), itr->path().string().size() - 1);

		Register(directory_path + file_name,
			SoundType::FILEPLAYER,
			file_name.substr(0, file_name.size() - 4));
	}
}

void SoundManager::Register(const std::string & file_path,
	const SoundType &type,
	const std::string & name)
{
	std::function<ci::audio::SamplePlayerNodeRef()> CreateSound[] =
	{
		[&] {
		ci::audio::FilePlayerNodeRef file_player;
		file_player = context->makeNode(new ci::audio::FilePlayerNode());
		ci::audio::SourceFileRef source = ci::audio::load(ci::app::loadAsset(file_path));
		file_player->setSourceFile(source);

		return file_player;
	},
		[&] {
		ci::audio::BufferPlayerNodeRef buffer_player;
		buffer_player = context->makeNode(new ci::audio::BufferPlayerNode());
		ci::audio::SourceFileRef source = ci::audio::load(ci::app::loadAsset(file_path));
		buffer_player->loadBuffer(source);

		return buffer_player;
	}
	};

	Sound sound(CreateSound[type](), context);
	sounds.insert(std::make_pair(name, sound));
}

void SoundManager::Delete(const std::string & name)
{
#ifdef _DEBUG
	if (sounds.find(name) == sounds.cend())
		assert(!"[name]‚Ì–¼‘O‚Ì•t‚¢‚½[sound]‚ª“o˜^‚³‚ê‚Ä‚Ü‚¹‚ñ");
#endif

	sounds.erase(sounds.find(name));
}

void SoundManager::AllDelete()
{
	sounds.clear();
}

Sound & SoundManager::GetSound(const std::string & name)
{
#ifdef _DEBUG
	if (sounds.find(name) == sounds.cend())
		assert(!"[name]‚Ì–¼‘O‚Ì•t‚¢‚½[sound]‚ª“o˜^‚³‚ê‚Ä‚Ü‚¹‚ñ");
#endif

	return sounds[name];
}

void SoundManager::AllStop()
{
	for (auto &sound : sounds)
		sound.second.Stop();
}
