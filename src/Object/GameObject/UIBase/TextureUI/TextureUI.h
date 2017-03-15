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
		texture(nullptr)
	{}
	virtual ~TextureUI() {}

	virtual void Setup() {}
	virtual void Setup(const ci::JsonTree &params)
	{
		transform.pos = GetVec3f(params["pos"]);
		transform.scale = GetVec3f(params["scale"]);
		texture = &(TextureManager::Get().GetTexture(
			params.getValueForKey<std::string>("texture_name")));
	}
	virtual void Update() override {}
	virtual void Draw() override
	{
		ci::gl::pushModelView();

		(*texture).enableAndBind();
		DrawtexCoord(transform.pos.xy,
			transform.scale.xy);
		(*texture).unbind();

		ci::gl::popModelView();
	}

protected:

	ci::gl::Texture *texture;
};