#pragma once
#include "../GameObject.h"


class Grid : public GameObject
{
private:

	float grid_range;
	float line_width;
	float line_num;

public:

	Grid();
	Grid(const float &grid_range,
		const float &line_width,
		const float &line_range);
	~Grid();

	void SetGridRange(const float &grid_range) { this->grid_range = grid_range; }
	void SetLineWidth(const float &line_width) { this->line_width = line_width; }
	void SetLineNum(const float &line_num) { this->line_num = line_num; }

	void Setup() override;
	void Update() override;
	void Draw() override;
};