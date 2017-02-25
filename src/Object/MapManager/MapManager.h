#pragma once
#include "../Object.h"
#include "../GameObject/CubeBase/ShrinkCube/ShrinkCube.h"
#include "../GameObject/CubeBase/VanishCube/VanishCube.h"



class MapManager : public Object
{
public:

	enum class CubeType
	{
		NONE = -1,
		NORMAL,
		SHRINK,
		VANISH,
		TYPEMAX
	};

	MapManager();
	~MapManager();

	CubeType GetCubeType(const ci::Vec3i &map_pos)
	{
		if (map_pos.x < 0 || map_pos.x >= static_cast<int>(cube_types[0][0].size()) ||
			map_pos.z < 0 || map_pos.z >= static_cast<int>(cube_types[0].size()) ||
			map_pos.y < 0 || map_pos.y >= static_cast<int>(cube_types.size()))
			return CubeType::TYPEMAX;

		return cube_types[map_pos.y][map_pos.z][map_pos.x];
	}

	void Setup(const ci::JsonTree &params);
	void Update();
	void Draw();

	void ClickCube(const ci::Vec3i &map_pos);

private:

	std::vector<CubeBase*> cubes;
	std::vector<std::vector<std::vector<CubeType>>> cube_types;
	
};