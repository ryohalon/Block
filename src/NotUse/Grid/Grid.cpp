#include "Grid.h"


Grid::Grid() :
	GameObject(),
	grid_range(1000.f),
	line_width(1.0f),
	line_num(200.0f)
{

}

Grid::Grid(const float &grid_range,
	const float &line_width,
	const float &line_range) :
	GameObject(),
	grid_range(grid_range),
	line_width(line_width),
	line_num(line_range)
{

}

Grid::~Grid()
{

}

void Grid::Setup()
{
	UpdateMatrix();

	ci::gl::lineWidth(line_width);
}

void Grid::Update()
{
	ci::gl::lineWidth(line_width);
}

void Grid::Draw()
{
	ci::gl::pushModelView();

	ci::gl::multModelView(matrix);

	ci::gl::color(ci::Color::black());
	
	for (int x = 0; x <= line_num; x++)
	{
		(x % 10 == 0) ?
			ci::gl::color(ci::Color(1.0f, 0.0f, 0.0f)) :
			ci::gl::color(ci::Color::black());

		ci::gl::drawLine(ci::Vec3f(grid_range / 2.0f - (grid_range / line_num) * x, 0.0f, grid_range / 2.0f),
			ci::Vec3f(grid_range / 2.0f - (grid_range / line_num) * x, 0.0f, -grid_range / 2.0f));
	}

	for (int z = 0; z <= line_num; z++)
	{
		(z % 10 == 0) ?
			ci::gl::color(ci::Color(1.0f, 0.0f, 0.0f)) :
			ci::gl::color(ci::Color::black());

		ci::gl::drawLine(ci::Vec3f(grid_range / 2.0f, 0.0f, grid_range / 2.0f - (grid_range / line_num) * z),
			ci::Vec3f(-grid_range / 2.0f, 0.0f, grid_range / 2.0f - (grid_range / line_num) * z));
	}

	ci::gl::color(ci::Color(0.0f, 1.0f, 0.0f));
	ci::gl::drawSphere(ci::Vec3f::zero(), 0.1f, 20);

	ci::gl::drawCoordinateFrame();

	ci::gl::popModelView();

}
