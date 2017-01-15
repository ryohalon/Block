#include "TextureManager.h"



TextureManager::TextureManager()
{
	
}

TextureManager::~TextureManager()
{
	
}

void TextureManager::Setup()
{
	Register(ci::app::getAssetPath("LoadFile/TexturePath.txt").string());
}

void TextureManager::Register(const std::string &file_path)
{
	std::ifstream list_path(file_path);
	std::string texture_path;
	std::string name;

	while (!list_path.eof())
	{
		list_path >> name;
		list_path >> texture_path;

		if (textures.find(name) != textures.cend())
			assert(!"error :Å@[name] is already in use");

		ci::app::console() << "path : " << texture_path << std::endl;

		textures.insert(std::make_pair(name,
			ci::gl::Texture(ci::loadImage(ci::app::loadAsset(texture_path)))));
	}
}

//void TextureManager::Register(const std::string &path, const ci::gl::Texture::Format &format, const std::string &name)
//{
//	if(textures.find(name) != textures.cend())
//		assert(!"error : [name] is already in use");
//
//	textures.insert(std::make_pair(path,
//		ci::gl::Texture(ci::loadImage(ci::app::loadAsset(path)), format)));
//}

ci::gl::Texture TextureManager::GetTexture(const std::string &name)
{
	if(textures.find(name) == textures.cend())
		assert(!"error : [name] does not exist");
		
	return textures.find(name)->second;
}

const ci::Vec2f& TextureManager::GetSize(const std::string &name)
{
	if(textures.find(name) == textures.cend())
		assert(!"error : [name] does not exist");
		
	return textures.find(name)->second.getSize();
}

void TextureManager::Delete(const std::string & name)
{
	if (textures.find(name) == textures.cend())
		assert(!"error : [name] does not exist");

	textures.erase(name);
}

void TextureManager::AllDelete()
{
	textures.clear();
}
