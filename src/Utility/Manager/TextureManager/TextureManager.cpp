#include "TextureManager.h"
#include <cinder/app/App.h>
#include <cinder/ImageIo.h>
#include "../../Utility.h"
#include <filesystem>


TextureManager::TextureManager()
{
	
}

TextureManager::~TextureManager()
{
	
}

void TextureManager::Setup()
{
	ci::JsonTree params(ci::app::loadAsset("LoadFile/DirectoryData/DirectoryData.json"));
	std::string directory_path = params.getValueForKey<std::string>("texture");

	for (std::tr2::sys::directory_iterator itr(GetFilePath(directory_path)), end; itr != end; itr++)
	{
		std::string file_name = itr->path().string().substr(GetFilePath(directory_path).size(), itr->path().string().size() - 1);

		// pngだけなので今は決め打ちにしている
		Register(directory_path + file_name,
			file_name.substr(0, file_name.size() - 4));
	}
}

void TextureManager::Register(const std::string &file_path, const std::string &name)
{
#ifdef _DEBUG
	if (textures.find(name) != textures.cend())
		assert(!"error :　[name] is already in use");
#endif

	textures.insert(std::make_pair(name,
		ci::gl::Texture(ci::loadImage(ci::app::loadAsset(file_path)))));
}

void TextureManager::Register(const std::string &file_path, const ci::gl::Texture::Format &format, const std::string &name)
{
#ifdef _DEBUG
	if (textures.find(name) != textures.cend())
		assert(!"error :　[name] is already in use");
#endif

	textures.insert(std::make_pair(name,
		ci::gl::Texture(ci::loadImage(ci::app::loadAsset(file_path)), format)));
}

ci::gl::Texture TextureManager::GetTexture(const std::string &name)
{
#ifdef _DEBUG
	if (textures.find(name) == textures.cend())
		assert(!"error :　[name] is already in use");
#endif
		
	return textures[name];
}

void TextureManager::Delete(const std::string & name)
{
#ifdef _DEBUG
	if (textures.find(name) == textures.cend())
		assert(!"error :　[name] is already in use");
#endif

	textures.erase(name);
}

void TextureManager::AllDelete()
{
	textures.clear();
}
