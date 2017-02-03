#pragma once
#include <cinder/Json.h>
#include <cinder/Vector.h>
#include <cinder/Color.h>
#include <cinder/gl/Material.h>
#include <cinder/app/App.h>



std::string GetFilePath(const std::string &path);

ci::Vec3f GetVec3f(const ci::JsonTree& params);

ci::Color GetColor(const ci::JsonTree& params);

ci::Color GetColorA(const ci::JsonTree& params);

ci::gl::Material GetMaterial(const ci::JsonTree &params);