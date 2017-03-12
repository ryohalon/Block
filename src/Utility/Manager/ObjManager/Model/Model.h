#pragma once
#include <cinder/ObjLoader.h>
#include <cinder/gl/Texture.h>
#include <cinder/app/App.h>
#include <cinder/ImageIo.h>



class Model
{
public:

	Model() {}
	~Model() {}

	void Setup(const std::string &file_path,
		const std::string &name)
	{
		ci::ObjLoader loader(ci::app::loadAsset(file_path + name + ".obj"));
		loader.load(&tri_mesh);

		mesh_texture = ci::gl::Texture(ci::loadImage(ci::app::loadAsset(file_path + name + ".png")));
	}

	ci::TriMesh tri_mesh;
	ci::gl::Texture mesh_texture;
};