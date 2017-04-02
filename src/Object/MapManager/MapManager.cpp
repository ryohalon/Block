#include "MapManager.h"
#include "../GameObject/CubeBase/ShrinkCube/ShrinkCube.h"
#include "../GameObject/CubeBase/VanishCube/VanishCube.h"
#include "../../Utility/Utility.h"
#include "../../Utility/Input/Key/Key.h"
#include "../../Utility/Manager/TimeManager/TimeManager.h"
#include "../../Utility/Manager/EasingManager/Easing/Easing.h"
#include <cinder/app/App.h>



MapManager::MapManager() :
	start_rotate_angle(0.0f),
	end_rotate_angle(0.0f),
	max_rotate_angle(static_cast<float>(M_PI) / 2.0f),
	is_rotating(false),
	stage_matrix(ci::Matrix44f::identity())
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
	cube_scale = ci::Vec3f::one() * params.getValueForKey<float>("cube_scale");
	rotate_take_time = params.getValueForKey<float>("rotate_take_time");
	stage_rotate_angle = M_PI * 2.0f / params.getValueForKey<float>("stage_rotate_angle");

	CreateMap(params, std::fstream(GetFilePath(file_path) + "Stage.csv"));

	map_center_pos = ci::Vec3f(
		static_cast<float>(cube_types[0][0].size() - 1) * cube_scale.x / 2.0f,
		static_cast<float>(cube_types.size() - 1) * cube_scale.y / 2.0f,
		static_cast<float>(cube_types[0].size() - 1) * cube_scale.z / 2.0f);
	ci::Matrix44f mtranslate = ci::Matrix44f::createTranslation(map_center_pos);
	ci::Matrix44f mrotate = ci::Matrix44f::createRotation(ci::Vec3f::yAxis() * stage_rotate_angle);
	stage_matrix = mtranslate * mrotate * mtranslate.inverted();

	CubeSetup();
}

void MapManager::CreateMap(const ci::JsonTree & params, std::fstream &file)
{
	std::string line;
	int y = 0;
	int z = 0;
	int x = 0;

	std::vector<std::vector<CubeType>> cube_types_zx;
	while (std::getline(file, line))
	{
		std::vector<CubeType> cube_types_x;

		std::string type = "";
		for (int i = 0; i < static_cast<int>(line.size()); i++)
		{
			if (line[i] != ',')
			{
				type += line[i];
				continue;
			}

			CubeType type_ = static_cast<CubeType>(boost::lexical_cast<int>(type));
			cube_types_x.push_back(type_);

			Transform transform = Transform(cube_scale * 
				ci::Vec3f(static_cast<float>(x),
					static_cast<float>(y),
					static_cast<float>(z)),
				ci::Vec3f::zero(),
				cube_scale);

			switch (type_)
			{
			case CubeType::NORMAL:

				cubes.push_back(new CubeBase(transform,
					ci::gl::Material(GetMaterial(params["material"]["normal"])),
					CubeType::NORMAL,
					ci::Vec3i(x, y, z)));
				break;
			case CubeType::SHRINK:

			{
				ci::JsonTree params_ = params["_" + std::to_string(y)]["_" + std::to_string(z)]["_" + std::to_string(x)];
				cubes.push_back(new ShrinkCube(CubeBase(transform,
					ci::gl::Material(GetMaterial(params["material"]["shrink"])),
					CubeType::SHRINK,
					ci::Vec3i(x, y, z)),
					params_.getValueForKey<bool>("is_shrink"),
					GetVec3f(params_["shrink_value"]),
					params_.getValueForKey<float>("take_time")));
			}
			break;
			case CubeType::START:

				player_start_pos = ci::Vec3i(x, y + 1, z);
				cubes.push_back(new CubeBase(transform,
					ci::gl::Material(GetMaterial(params["material"]["start"])),
					CubeType::NORMAL,
					ci::Vec3i(x, y, z)));
				break;
			case CubeType::GOAL:

				cubes.push_back(new CubeBase(transform,
					ci::gl::Material(GetMaterial(params["material"]["goal"])),
					CubeType::NORMAL,
					ci::Vec3i(x, y, z)));
				break;
			case CubeType::VANISH:

				cubes.push_back(new VanishCube(CubeBase(transform,
					ci::gl::Material(GetMaterial(params["material"]["vanish"])),
					CubeType::VANISH,
					ci::Vec3i(x, y, z)),
					params["_" + std::to_string(y)]
					["_" + std::to_string(z)]
				["_" + std::to_string(x)].getValueForKey<bool>("is_vanish")));
				break;
			}

			type = "";
			x++;
		}

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
}

void MapManager::CubeSetup()
{
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
}

void MapManager::Update()
{
	for (auto &cube : cubes)
		cube->Update();

	Rotating();

	if (Key::Get().IsPushKey(ci::app::KeyEvent::KEY_q) ||
		Key::Get().IsPushKey(ci::app::KeyEvent::KEY_e))
	{
		RotateStart();
	}
}

void MapManager::Draw()
{
	ci::gl::pushModelView();

	glMultMatrixf(stage_matrix);

	for (auto &cube : cubes)
		cube->Draw();

	ci::gl::popModelView();
}

void MapManager::Reset()
{

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

void MapManager::RotateStart()
{
	if (is_rotating)
		return;

	start_rotate_angle = stage_rotate_angle;

	if (Key::Get().IsPushKey(ci::app::KeyEvent::KEY_e))
		end_rotate_angle = stage_rotate_angle - max_rotate_angle;
	else if (Key::Get().IsPushKey(ci::app::KeyEvent::KEY_q))
		end_rotate_angle = stage_rotate_angle + max_rotate_angle;

	time = 0.0f;
	is_rotating = true;
}

void MapManager::Rotating()
{
	if (!is_rotating)
		return;

	time = std::min(1.0f, TimeManager::Get().GetDeltaTime() / rotate_take_time + time);
	stage_rotate_angle = Easing::Linear(time, start_rotate_angle, end_rotate_angle);
	ci::Matrix44f mtranslate = ci::Matrix44f::createTranslation(map_center_pos);
	ci::Matrix44f mrotate = ci::Matrix44f::createRotation(ci::Vec3f::yAxis() * stage_rotate_angle);
	stage_matrix = mtranslate * mrotate * mtranslate.inverted();

	if (time < 1.0f)
		return;

	time = 0.0f;
	is_rotating = false;
}
