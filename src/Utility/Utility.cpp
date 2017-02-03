#include "Utility.h"



std::string GetFilePath(const std::string &path)
{
	ci::fs::path full_path = ci::app::getAssetPath(path);

	ci::app::console() << full_path << std::endl;

	return full_path.string();
}

ci::Vec3f GetVec3f(const ci::JsonTree& params)
{
	ci::Vec3f vec;

	vec.x = params.getValueAtIndex<float>(0);
	vec.y = params.getValueAtIndex<float>(1);
	vec.z = params.getValueAtIndex<float>(2);

	return vec;
}

ci::Color GetColor(const ci::JsonTree& params) {
	ci::Color color;

	color.r = params.getValueAtIndex<float>(0);
	color.g = params.getValueAtIndex<float>(1);
	color.b = params.getValueAtIndex<float>(2);

	return color;
}

ci::Color GetColorA(const ci::JsonTree& params) {
	ci::ColorA colorA;

	colorA.r = params.getValueAtIndex<float>(0);
	colorA.g = params.getValueAtIndex<float>(1);
	colorA.b = params.getValueAtIndex<float>(2);
	colorA.a = params.getValueAtIndex<float>(3);

	return colorA;
}

ci::gl::Material GetMaterial(const ci::JsonTree &params)
{
	ci::gl::Material material =
		ci::gl::Material(GetColorA(params["ambient"]),
			GetColorA(params["diffuse"]),
			GetColorA(params["specular"]),
			params.getValueForKey<float>("shininess"),
			GetColorA(params["emission"]));

	return material;
}
