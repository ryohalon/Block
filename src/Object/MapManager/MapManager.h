#pragma once
#include "../Object.h"
#include "../GameObject/CubeBase/ShrinkCube/ShrinkCube.h"
#include "../GameObject/CubeBase/VanishCube/VanishCube.h"



class MapManager : public Object
{
public:

	enum class CubeType
	{
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

	std::vector<CubeBase*> map;
	
};