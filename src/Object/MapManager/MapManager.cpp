#include "MapManager.h"
#include "cinder/Filesystem.h"

std::string GetFilePath(const std::string &path)
{
	ci::fs::path full_path = ci::app::getAssetPath(path);

	ci::app::console() << full_path << std::endl;

	return full_path.string();
}

ci::Vec3f GetVec3f(const ci::JsonTree& params)
{
	ci::Vec3f vec;

	vec.x = params.getValueAtIndex<float>(0);
	vec.y = params.getValueAtIndex<float>(1);
	vec.z = params.getValueAtIndex<float>(2);

	return vec;
}

ci::Color GetColor(const ci::JsonTree& params) {
	ci::Color color;

	color.r = params.getValueAtIndex<float>(0);
	color.g = params.getValueAtIndex<float>(1);
	color.b = params.getValueAtIndex<float>(2);

	return color;
}

ci::Color GetColorA(const ci::JsonTree& params) {
	ci::ColorA colorA;

	colorA.r = params.getValueAtIndex<float>(0);
	colorA.g = params.getValueAtIndex<float>(1);
	colorA.b = params.getValueAtIndex<float>(2);
	colorA.a = params.getValueAtIndex<float>(3);

	return colorA;
}

ci::gl::Material GetMaterial(const ci::JsonTree &params)
{
	ci::gl::Material material =
		ci::gl::Material(GetColorA(params["Ambient"]),
			GetColorA(params["Diffuse"]),
			GetColorA(params["Specular"]),
			params.getValueForKey<float>("Shininess"),
			GetColorA(params["Emission"]));

	return material;
}

MapManager::MapManager()
{

}

MapManager::~MapManager()
{

}

void MapManager::Setup(const int & world, const int & stage)
{
	ci::JsonTree params(ci::app::loadAsset("LoadFile/StageData/World" + std::to_string(world)
		+ "/Stage" + std::to_string(stage) + "/Stage.json"));

	ci::Vec3f size = GetVec3f(params["CubeSize"]);

	ci::JsonTree cube_type = params["CubeType"];
	for (int y = 0; y < cube_type.getNumChildren(); y++)
	{
		std::vector<std::vector<int>> cube_types_zx;
		for (int z = 0; z < cube_type[y].getNumChildren(); z++)
		{
			std::vector<int> cube_types_x;
			for (int x = 0; x < cube_type[y][z].getNumChildren(); x++)
			{
				int type = params[y][z].getValueAtIndex<int>(x);
				cube_types_x.push_back(type);

				switch (static_cast<CubeType>(type))
				{
				case CubeType::NORMAL:
					cubes.push_back(new CubeBase(ci::Vec3f(size.x * x, size.y * y, size.z * z),
						ci::Vec3f::zero(),
						size,
						ci::gl::Material(GetMaterial(params["Material"]["Normal"]))));
						break;
				case CubeType::SHRINK:
					break;
				case CubeType::VANISH:
					break;
				case CubeType::NONE:
					break;
				}
			}
		}
	}
}

void MapManager::Update()
{

}

void MapManager::Draw()
{

}
