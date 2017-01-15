#pragma once
#include "cinder/Font.h"
#include "cinder/gl/gl.h"


using namespace ci;


class FontManager
{
private:

	Font font;
	Vec2f pos;
	Vec3f scale;
	std::string text;
	ColorA color;

public:

	FontManager();
	FontManager(std::string& font_type,
		float& font_size,
		Vec2f& pos,
		Vec3f& scale,
		std::string text,
		ColorA& color);
	~FontManager();

	Vec2f GetPos() const { return pos; }
	void SetPos(Vec2f& pos) { this->pos = pos; }
	Vec3f GetScale() const { return scale; }
	void SetScale(Vec3f& scale) { this->scale = scale; }
	std::string GetText() const { return text; }
	void SetText(std::string text) { this->text = text; }
	void SetColor(ColorA color) { this->color = color; }

	void DesignationFont(std::string font_type, float font_size);

	void Setup();
	void Draw();
};