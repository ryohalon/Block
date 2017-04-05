#pragma once
#include "../Object.h"
#include "../GameObject/CubeBase/CubeBase.h"


class MapManager : public Object
{
public:

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
	std::vector<CubeBase*>& GetCubes() { return cubes; }

	template<typename T>
	T* GetCube(const ci::Vec3i &map_pos)
	{
		for (auto &cube : cubes)
		{
			if (map_pos != cube->GetMapPos())
				continue;

			return static_cast<T*>(cube);
		}

		return nullptr;
	}

	ci::Vec3i GetPlayerStartPos() const { return player_start_pos; }
	ci::Vec3f GetCubeScale() const { return cube_scale; }
	ci::Vec3f GetMapCenterPos() const { return map_center_pos; }
	float GetStageRotateAngle() const { return stage_rotate_angle; }
	ci::Matrix44f GetStageMatrix() const { return stage_matrix; }
	ci::Vec3f GetMapSize() {
		return ci::Vec3f(
			cube_types[0][0].size(),
			cube_types.size(),
			cube_types[0].size());
	}

	void Setup(const int &world, const int &stage);
	void CreateMap(const ci::JsonTree &params, std::fstream &file);
	void CubeSetup();
	void Update();
	void Draw();

	void Reset();
	void ClickCube(CubeBase *cube);

private:

	void RotateStart();
	void Rotating();

	std::vector<CubeBase*> cubes;
	std::vector<std::vector<std::vector<CubeType>>> cube_types;

	ci::Vec3i player_start_pos;
	ci::Vec3f cube_scale;
	ci::Vec3f map_center_pos;
	float stage_rotate_angle;
	float time, rotate_take_time;
	float start_rotate_angle,
		end_rotate_angle;
	float max_rotate_angle;
	bool is_rotating;
	ci::Matrix44f stage_matrix;
};