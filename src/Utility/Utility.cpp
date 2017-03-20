#include "Utility.h"
#include <cinder/app/App.h>



std::string GetFilePath(const std::string &path)
{
	ci::fs::path full_path = ci::app::getAssetPath(path);

	return full_path.string();
}

ci::Vec2f GetVec2f(const ci::JsonTree & params)
{
	ci::Vec2f vec;

	vec.x = params.getValueAtIndex<float>(0);
	vec.y = params.getValueAtIndex<float>(1);

	return vec;
}

ci::Vec2i GetVec2i(const ci::JsonTree & params)
{
	ci::Vec2i vec;

	vec.x = params.getValueAtIndex<int>(0);
	vec.y = params.getValueAtIndex<int>(1);

	return vec;
}

ci::Vec3f GetVec3f(const ci::JsonTree& params) 
{
	ci::Vec3f vec;

	vec.x = params.getValueAtIndex<float>(0);
	vec.y = params.getValueAtIndex<float>(1);
	vec.z = params.getValueAtIndex<float>(2);

	return vec;
}

ci::Vec3i GetVec3i(const ci::JsonTree& params)
{
	ci::Vec3i vec;

	vec.x = params.getValueAtIndex<int>(0);
	vec.y = params.getValueAtIndex<int>(1);
	vec.z = params.getValueAtIndex<int>(2);

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

void DrawtexCoord(const ci::Vec2f &pos,
	const ci::Vec2f &size,
	const ci::Vec2f &uv1,
	const ci::Vec2f &uv2)
{
	ci::gl::begin(GL_QUADS);
	ci::gl::texCoord(uv1);
	ci::gl::vertex(pos + ci::Vec2f(-size.x, size.y) / 2.0f);
	ci::gl::texCoord(uv2.x, uv1.y);
	ci::gl::vertex(pos + size / 2.0f);
	ci::gl::texCoord(uv2);
	ci::gl::vertex(pos + ci::Vec2f(size.x, -size.y) / 2.0f);
	ci::gl::texCoord(uv1.x, uv2.y);
	ci::gl::vertex(pos - size / 2.0f);
	ci::gl::end();
}