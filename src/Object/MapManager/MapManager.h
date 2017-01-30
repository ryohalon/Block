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
		VANISH
	};

	MapManager();
	~MapManager();

	void Setup(const int &world,
		const int &stage);
	void Update();
	void Draw();

private:

	std::vector<CubeBase*> cubes;
	std::vector<std::vector<std::vector<int>>> cube_types;
	
};