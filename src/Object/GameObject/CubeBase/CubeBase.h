#pragma once
#include "../GameObject.h"



class CubeBase : public GameObject
{
public:

	CubeBase() :
		material(ci::gl::Material(ci::ColorA(0, 0, 0, 1))),
		map_pos(ci::Vec3i::zero())
	{}
	CubeBase(const ci::Vec3f &pos,
		const ci::Vec3f &angle,
		const ci::Vec3f &scale,
		const ci::gl::Material &material,
		const ci::Vec3i &map_pos):
		GameObject(Transform(pos, angle, scale)),
		material(material),
		map_pos(map_pos)
	{}
	virtual ~CubeBase() {}

	ci::gl::Material GetMaterial() const { return material; }
	void SetMaterial(const ci::gl::Material &material_) { material = material_; }

	ci::Vec3i GetMapPos() const { return map_pos; }
	void SetMapPos(const ci::Vec3i &map_pos_) { map_pos = map_pos_; }

	virtual void Setup() override
	{
		UpdateMatrix();
	}
	virtual void Setup(const ci::JsonTree &params) override {}
	virtual void Update() override {}
	virtual void Draw() override
	{
		ci::gl::pushModelView();

		glMultMatrixf(matrix);

		material.apply();
		ci::gl::drawCube(ci::Vec3f::zero(), ci::Vec3f::one());

		ci::gl::popModelView();
	}

	virtual void Clicked() {}

protected:

	ci::gl::Material material;

	ci::Vec3i map_pos;
};