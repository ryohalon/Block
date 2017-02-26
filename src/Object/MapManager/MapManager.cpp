#include "MapManager.h"
#include "cinder/Filesystem.h"
#include "../../Utility/Utility.h"


MapManager::MapManager()
{

}

MapManager::~MapManager()
{

}

void MapManager::Setup(const int &world, const int &stage)
{
	std::string file_path = "LoadFile/StageData/World" + std::to_string(world)
		+ "/Stage" + std::to_string(stage) + "/";

	ci::JsonTree params = ci::JsonTree(ci::app::loadAsset(file_path + "Stage.json"));
	ci::Vec3f size = GetVec3f(params["cube_size"]);

	std::fstream file(GetFilePath(file_path) + "Stage.csv");
	std::string line;
	int y = 0;
	int z = 0;
	int x = 0;

	std::vector<std::vector<CubeType>> cube_types_zx;
	while (std::getline(file, line))
	{
		std::vector<CubeType> cube_types_x;

		std::string type = "";
		ci::app::console() << z << ": ";
		for (int i = 0; i < static_cast<int>(line.size()); i++)
		{
			if (line[i] != ',')
			{
				type += line[i];
				continue;
			}

			ci::app::console() << type << " ";

			cube_types_x.push_back(static_cast<CubeType>(boost::lexical_cast<int>(type)));
			if (type == "0")
			{
				cubes.push_back(new CubeBase(ci::Vec3f(size.x * x, size.y * y, size.z * z),
					ci::Vec3f::zero(),
					size,
					ci::gl::Material(GetMaterial(params["material"]["normal"])),
					CubeType::NORMAL,
					ci::Vec3i(x, y, z)));
			}
			else if (type == "1")
			{
				ci::JsonTree params_ = params["_" + std::to_string(y)]["_" + std::to_string(z)]["_" + std::to_string(x)];
				cubes.push_back(new ShrinkCube(ci::Vec3f(size.x * x, size.y * y, size.z * z),
					ci::Vec3f::zero(),
					size,
					ci::gl::Material(GetMaterial(params["material"]["shrink"])),
					CubeType::SHRINK,
					ci::Vec3i(x, y, z),
					params_.getValueForKey<bool>("is_shrink"),
					GetVec3f(params_["shrink_value"]),
					params_.getValueForKey<float>("take_time")));
			}

			type = "";
			x++;
		}

		ci::app::console() << std::endl;

		z++;
		x = 0;

		if (line.size() == 0)
		{
			cube_types.push_back(cube_types_zx);
			cube_types_zx.clear();
			y++;
			z = 0;
		}
		else
		{
			cube_types_zx.push_back(cube_types_x);
			cube_types_x.clear();
		}
	}

	for (auto &cube : cubes)
	{
		cube->Setup();

		if (cube->GetType() == CubeType::SHRINK)
		{
			ShrinkCube *shrink_cube = static_cast<ShrinkCube*>(cube);
			if (!shrink_cube->GetIsShrink())
				continue;

			ci::Vec3i shrink_value = ci::Vec3i(
				static_cast<int>(shrink_cube->GetShrinkValue().x),
				static_cast<int>(shrink_cube->GetShrinkValue().y),
				static_cast<int>(shrink_cube->GetShrinkValue().z));

			ci::Vec3i shrink_direction[] = {
				ci::Vec3i(0,1,0),
				ci::Vec3i(0,0,1),
				ci::Vec3i(1,0,0),
				ci::Vec3i(0,0,-1),
				ci::Vec3i(-1,0,0),
				ci::Vec3i(0,-1,0),
			};
			ci::Vec3i shrink_direction_ = ci::Vec3i::zero();
			do
			{
				shrink_direction_ += shrink_direction[static_cast<int>(shrink_cube->GetShrinkDirection())];

				ci::Vec3i pos = ci::Vec3i(
					static_cast<int>(shrink_cube->GetOriginPos().x) + shrink_direction_.x,
					static_cast<int>(shrink_cube->GetOriginPos().y) + shrink_direction_.y,
					static_cast<int>(shrink_cube->GetOriginPos().z) + shrink_direction_.z
				);

				cube_types[pos.y][pos.z][pos.x] = CubeType::SHRINK;

			} while (shrink_direction_ != shrink_value);
		}
	}

	for (auto &a : cube_types)
	{
		for (auto &b : a)
		{
			for (auto &c : b)
			{
				ci::app::console() << static_cast<int>(c) << ",";
			}
			ci::app::console() << std::endl;
		}
		ci::app::console() << std::endl;
	}
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

void MapManager::ClickCube(CubeBase *cube)
{
	cube->Clicked();
	if (cube->GetType() != CubeType::SHRINK)
		return;

	ShrinkCube *shrink_cube = static_cast<ShrinkCube*>(cube);
	ci::Vec3i shrink_value = ci::Vec3i(
		static_cast<int>(shrink_cube->GetShrinkValue().x),
		static_cast<int>(shrink_cube->GetShrinkValue().y),
		static_cast<int>(shrink_cube->GetShrinkValue().z));

	ci::Vec3i shrink_direction[] = {
		ci::Vec3i(0,1,0),
		ci::Vec3i(0,0,1),
		ci::Vec3i(1,0,0),
		ci::Vec3i(0,0,-1),
		ci::Vec3i(-1,0,0),
		ci::Vec3i(0,-1,0),
	};
	ci::Vec3i shrink_direction_ = ci::Vec3i::zero();

	do
	{
		shrink_direction_ += shrink_direction[static_cast<int>(shrink_cube->GetShrinkDirection())];

		ci::Vec3i pos = ci::Vec3i(
			static_cast<int>(shrink_cube->GetOriginPos().x) + shrink_direction_.x,
			static_cast<int>(shrink_cube->GetOriginPos().y) + shrink_direction_.y,
			static_cast<int>(shrink_cube->GetOriginPos().z) + shrink_direction_.z
		);

		cube_types[pos.y][pos.z][pos.x] = (shrink_cube->GetIsShrink()) ?
			CubeType::SHRINK :
			CubeType::NONE;

	} while (shrink_direction_ != shrink_value);
}
