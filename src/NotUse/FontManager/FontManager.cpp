#include "FontManager.h"

FontManager::FontManager() :
	pos(Vec2f(0.0f, 0.0f)),
	scale(Vec3f(1.0f, 1.0f, 1.0f)),
	text(u8"sample"),
	color(Color(1.0f, 1.0f, 1.0f))
{

}

FontManager::FontManager(std::string & font_type,
	float & font_size,
	Vec2f& pos = Vec2f::zero(),
	Vec3f& scale = Vec3f(1.0f, 1.0f, 1.0f),
	std::string text = u8"sample",
	ColorA& color = ColorA(1.0f, 1.0f, 1.0f)) :
	font(Font(font_type, font_size)),
	pos(pos),
	scale(scale),
	text(text),
	color(color)
{

}

FontManager::~FontManager()
{

}

void FontManager::DesignationFont(std::string font_type, float font_size)
{
	font = Font(font_type, font_size);
}

void FontManager::Setup()
{

}

void FontManager::Draw()
{
	gl::pushModelView();

	gl::scale(scale);

	gl::drawString(text, pos, color, font);

	gl::popModelView();
}
