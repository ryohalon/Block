#pragma once
#include <cinder/gl/Texture.h>
#include <map>


class TextureManager
{
public:

	TextureManager();
	~TextureManager();

	static TextureManager& Get()
	{
		static TextureManager texture_manager;
		
		return texture_manager;
	}

	void Setup();

	void Register(const std::string &file_path, const std::string &name);
	void Register(const std::string &file_path,
		const ci::gl::Texture::Format &format,
		const std::string &name);
	ci::gl::Texture GetTexture(const std::string &name);
	
	void Delete(const std::string &name);
	void AllDelete();

private:

	std::map<std::string, ci::gl::Texture> textures;

};