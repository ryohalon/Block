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
		transform.pos = GetVec3f(params["pos"]);
		transform.scale = GetVec3f(params["scale"]);
		texture_name = params.getValueForKey<std::string>("texture_name");
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