#pragma once
#include "../UIBase.h"
#include <cinder/app/App.h>



class FontUI : public UIBase
{
public:

	FontUI() :
	str(""),
	color(ci::ColorAf::black())
	{}
	~FontUI() {}

	void SetStr(const std::string &str_) { str = str_; }
	void SetColor(const ci::ColorAf &color_) { color = color_; }
	void SetFont(const ci::Font &font_) { font = font_; }

	void Setup() override {}
	void Setup(const ci::JsonTree &params) override
	{
		ci::Vec2f pos = GetVec2f(params["pos"]);

		transform.pos =
			ci::Vec3f(pos.x, pos.y, 0.0f);
		str = params.getValueForKey < std::string>("str");
		color = GetColorAf(params["color"]);
		std::string font_path = "Resource/Font/" + params.getValueForKey<std::string>("font_type");
		font = ci::Font(ci::app::loadAsset(font_path), params.getValueForKey<int>("size"));
	}
	void Draw() override
	{
		ci::gl::pushModelView();
		ci::gl::translate(transform.pos.xy());
		ci::gl::translate(ci::Vec3f(0.0f, -font.getSize() / 4, 0.0f));
		ci::gl::translate(ci::Vec3f(0.0f, font.getSize() / 2, 0.0f));
		ci::gl::rotate(ci::Vec3f(180.0f, 0.0f, 0.0f));
		ci::gl::translate(ci::Vec3f(0.0f, -font.getSize() / 2, 0.0f));
		ci::gl::color(color);
		ci::gl::drawStringCentered(str, ci::Vec2f::zero(), color, font);
		ci::gl::popModelView();
	}

	private:

		std::string str;
		ci::ColorAf color;
		ci::Font font;
};