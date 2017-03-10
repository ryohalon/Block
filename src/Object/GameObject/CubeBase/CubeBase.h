#pragma once
#include "../GameObject.h"



enum class CubeType
{
	NONE = -1,
	NORMAL,
	SHRINK,
	VANISH,
	AUTOMOVE,
	START,
	GOAL,
	SPRING,
	TYPEMAX
};

class CubeBase : public GameObject
{
public:

	CubeBase() :
		material(ci::gl::Material(ci::ColorA(0, 0, 0, 1))),
		type(CubeType::NONE),
		map_pos(ci::Vec3i::zero())
	{}
	CubeBase(const Transform &transform,
		const ci::gl::Material &material,
		const CubeType &type,
		const ci::Vec3i &map_pos):
		GameObject(transform),
		type(type),
		material(material),
		map_pos(map_pos)
	{}
	virtual ~CubeBase() {}

	ci::gl::Material GetMaterial() const { return material; }
	void SetMaterial(const ci::gl::Material &material_) { material = material_; }

	CubeType GetType() const { return type; }

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

	CubeType type;
	ci::Vec3i map_pos;
};