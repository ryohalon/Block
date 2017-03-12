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
		ci::ObjLoader loader(ci::app::loadAsset(file_path + '/' + name + ".obj"));
		loader.load(&tri_mesh,
			boost::logic::indeterminate,
			boost::logic::indeterminate,
			false);

		mesh_texture = ci::gl::Texture(ci::loadImage(ci::app::loadAsset(file_path + '/' + name + ".png")));
	}

	const ci::TriMesh& GetTriMesh() const { return tri_mesh; }
	const ci::gl::Texture& GetTexture() const { return mesh_texture; }

private:

	ci::TriMesh tri_mesh;
	ci::gl::Texture mesh_texture;
};