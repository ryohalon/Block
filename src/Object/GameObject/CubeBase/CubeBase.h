#pragma once
#include "../GameObject.h"



class CubeBase : public GameObject
{
public:

	CubeBase() :
		material(ci::gl::Material(ci::ColorA(0, 0, 0, 1)))
	{}
	CubeBase(const ci::Vec3f &pos,
		const ci::Vec3f &angle,
		const ci::Vec3f &scale,
		const ci::gl::Material &material):
		GameObject(Transform(pos, angle, scale)),
		material(material)
	{}
	virtual ~CubeBase() {}

	ci::gl::Material GetMaterial() const { return material; }
	void SetMaterial(const ci::gl::Material &material_) { material = material_; }

	virtual void Setup() override
	{
		UpdateMatrix();
	}
	virtual void Update() override {}
	virtual void Draw() override
	{
		ci::gl::pushModelView();

		glMultMatrixf(matrix);

		material.apply();
		ci::gl::drawCube(ci::Vec3f::zero(), ci::Vec3f::one());

		ci::gl::popModelView();
	}

protected:

	ci::gl::Material material;
};