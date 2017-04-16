#include "CubeCurosr.h"
#include "../../../Utility/Manager/TimeManager/TimeManager.h"
#include "../../../Utility/Manager/ModelManager/ModelManager.h"
#include "../../../Utility/Utility.h"

CubeCursor::CubeCursor() :
	time(0.0f),
	take_time(0.5f),
	cursor_pos(ci::Vec3f::yAxis() * 2.0f),
	default_cursor_pos_y(2.0f),
	move_range(0.3f)
{
}

CubeCursor::~CubeCursor()
{
}

void CubeCursor::Setup()
{
	material = ci::gl::Material(ci::ColorAf(0.0f, 0.8f, 0.8f, 0.7f),
		ci::ColorAf(0.0f, 0.7f, 0.7f, 0.7f),
		ci::ColorAf(0.0f, 0.9f, 0.9f, 0.7f),
		80.0f,
		ci::ColorAf(0.0f, 0.0f, 0.0f, 0.0f));

	transform.pos = ci::Vec3f::yAxis() * 1000.0f;
}

void CubeCursor::Update()
{
	time += TimeManager::Get().GetDeltaTime() / take_time;
	if (time >= static_cast<float>(M_PI) * 2.0f)
		time -= static_cast<float>(M_PI) * 2.0f;

	cursor_pos.y = std::sin(time) * move_range + default_cursor_pos_y;
}

void CubeCursor::Draw()
{
	ci::gl::pushModelView();
	glMultMatrixf(stage_matrix);

	ci::gl::drawStrokedCube(transform.pos, transform.scale);
	ci::gl::translate(transform.pos + cursor_pos);
	Model &model = ModelManager::Get().GetModel("Cursor");
	model.GetTexture().enableAndBind();
	ci::gl::draw(model.GetTriMesh());
	model.GetTexture().unbind();

	ci::gl::popModelView();
}
