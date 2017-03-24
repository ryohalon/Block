#pragma once
#include "../UIBase.h"
#include "../../../../Utility/Utility.h"

namespace cinder {
	namespace gl {
		class Texture;
	}
}


class TextureUI : public UIBase
{
public:

	TextureUI() :
		texture_name(""),
		color(ci::ColorAf::white())
	{}
	virtual ~TextureUI() {}

	virtual void Setup() {}
	virtual void Setup(const ci::JsonTree &params)
	{
		ci::Vec2f pos = GetVec2f(params["pos"]);
		ci::Vec2f size = GetVec2f(params["size"]);
		texture_name = params.getValueForKey<std::string>("texture_name");
		ci::Vec4f color_ = GetVec4f(params["color"]);

		transform.pos =
			ci::Vec3f(pos.x, pos.y, 0.0f);
		transform.scale =
			ci::Vec3f(size.x, size.y, 1.0f);
		color = ci::ColorAf(color_.x, color_.y, color_.z, color_.w);
	}
	virtual void Update() override {}
	virtual void Draw() override
	{
		ci::gl::color(color);
		TextureManager::Get().GetTexture(texture_name).enableAndBind();
		DrawtexCoord(transform.pos.xy(),
			transform.scale.xy());
		TextureManager::Get().GetTexture(texture_name).unbind();
	}

	virtual bool IsCollisionMouse(const ci::Vec2i &mouse_pos)
	{
		if (mouse_pos.x < transform.pos.x || mouse_pos.x > transform.pos.x + transform.scale.x)
			return false;
		if (mouse_pos.y < transform.pos.y || mouse_pos.y > transform.pos.y + transform.scale.y)
			return false;

		return true;
	}

protected:

	std::string texture_name;
	ci::ColorAf color;
};