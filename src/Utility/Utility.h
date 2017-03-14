#pragma once
#include <cinder/Json.h>
#include <cinder/Vector.h>
#include <cinder/Color.h>
#include <cinder/gl/Material.h>



std::string GetFilePath(const std::string &path);

ci::Vec3f GetVec3f(const ci::JsonTree& params);

ci::Vec3i GetVec3i(const ci::JsonTree& params);

ci::Color GetColor(const ci::JsonTree& params);

ci::Color GetColorA(const ci::JsonTree& params);

ci::gl::Material GetMaterial(const ci::JsonTree &params);

void DrawtexCoord(const ci::Vec2f &pos = ci::Vec2f::zero(),
	const ci::Vec2f &size = ci::Vec2f::one(),
	const ci::Vec2f &uv1 = ci::Vec2f::zero(),
	const ci::Vec2f &uv2 = ci::Vec2f::one());