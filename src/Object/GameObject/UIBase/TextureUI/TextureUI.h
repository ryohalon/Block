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
		texture_name("")
	{}
	virtual ~TextureUI() {}

	virtual void Setup() {}
	virtual void Setup(const ci::JsonTree &params)
	{
		default_pos = GetVec2f(params["pos"]);
		default_size = GetVec2f(params["size"]);
		texture_name = params.getValueForKey<std::string>("texture_name");

		transform.pos = ci::Vec3f(default_pos.x,
			default_pos.y,
			0.0f);
		transform.scale = ci::Vec3f(default_size.x,
			default_size.y,
			1.0f);
	}
	virtual void Update() override {}
	virtual void Draw() override
	{
		ci::gl::pushModelView();

		TextureManager::Get().GetTexture(texture_name).enableAndBind();
		DrawtexCoord(transform.pos.xy(),
			transform.scale.xy());
		TextureManager::Get().GetTexture(texture_name).unbind();

		ci::gl::popModelView();
	}

protected:

	std::string texture_name;
};