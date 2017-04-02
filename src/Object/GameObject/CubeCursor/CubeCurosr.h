#pragma once
#include "../GameObject.h"



class CubeCursor : public GameObject
{
public:
	
	CubeCursor();
	~CubeCursor();

	void SetStageMatrix(const ci::Matrix44f &stage_matrix_) { stage_matrix = stage_matrix_; }

	void Setup() override;
	void Update() override;
	void Draw() override;

private:

	float time;
	ci::Vec3f cursor_pos;
	float default_cursor_pos_y;
	ci::Matrix44f stage_matrix;
	ci::gl::Material material;
};