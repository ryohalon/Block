#include "MapManager.h"
#include "cinder/Filesystem.h"
#include "../../Utility/Utility.h"


MapManager::MapManager()
{

}

MapManager::~MapManager()
{

}

void MapManager::Setup(const ci::JsonTree & params)
{
	ci::Vec3f size = GetVec3f(params["cube_size"]);

	ci::JsonTree cube_type = params["cube_type"];
	for (int y = 0; y < cube_type.getNumChildren(); y++)
	{
		std::vector<std::vector<int>> cube_types_zx;
		for (int z = 0; z < cube_type[y].getNumChildren(); z++)
		{
			std::vector<int> cube_types_x;
			for (int x = 0; x < cube_type[y][z].getNumChildren(); x++)
			{
				int type = cube_type[y][z].getValueAtIndex<int>(x);
				cube_types_x.push_back(type);

				switch (static_cast<CubeType>(type))
				{
				case CubeType::NORMAL:

					cubes.push_back(new CubeBase(ci::Vec3f(size.x * x, size.y * y, size.z * z),
						ci::Vec3f::zero(),
						size,
						ci::gl::Material(GetMaterial(params["material"]["normal"])),
						ci::Vec3i(x, y, z)));
					break;

				case CubeType::SHRINK:
				{
					ci::JsonTree params_ = params["_" + std::to_string(y)]["_" + std::to_string(z)]["_" + std::to_string(x)];
					cubes.push_back(new ShrinkCube(ci::Vec3f(size.x * x, size.y * y, size.z * z),
						ci::Vec3f::zero(),
						size,
						ci::gl::Material(GetMaterial(params["material"]["shrink"])),
						ci::Vec3i(x, y, z),
						params_.getValueForKey<bool>("is_shrink"),
						GetVec3f(params_["shrink_value"]),
						params_.getValueForKey<float>("take_time")));
				}

					break;
				case CubeType::VANISH:
					break;
				case CubeType::NONE:
					break;
				}
			}

			cube_types_zx.push_back(cube_types_x);
			cube_types_x.clear();
		}

		cube_types.push_back(cube_types_zx);
		cube_types_zx.clear();
	}

	for (auto &cube : cubes)
		cube->Setup();
}

void MapManager::Update()
{
	for (auto &cube : cubes)
		cube->Update();
}

void MapManager::Draw()
{
	ci::gl::pushModelView();

	for (auto &cube : cubes)
		cube->Draw();

	ci::gl::popModelView();
}
