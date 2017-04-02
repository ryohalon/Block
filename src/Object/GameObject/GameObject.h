#pragma once
#include "cinder/Matrix.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Material.h"
#include "cinder/Json.h"
#include "../Object.h"
#include "../Component/Transform/Transform.h"
#include "../../Utility/Manager/SoundManager/SoundManager.h"
#include "../../Utility/Manager/TextureManager/TextureManager.h"



class GameObject : public Object
{
public:

	GameObject() :
		matrix(ci::Matrix44f::identity()),
		is_stop(true)
	{}
	GameObject(const Transform &transform) :
		transform(transform),
		matrix(ci::Matrix44f::identity()),
		is_stop(true)
	{

	}
	virtual ~GameObject() {}

	// EasingManagerÇégÇ§ÇΩÇﬂédï˚Ç»Ç≠çÏê¨
	Transform* GetTransformP() { return &transform; }
	Transform GetTransform() const { return transform; }
	ci::Matrix44f GetMatrix() const { return matrix; }
	bool GetIsStop() const { return is_stop; }

	void SetPos(const ci::Vec3f &pos_) { transform.pos = pos_; }
	void SetAngle(const ci::Vec3f &angle_) { transform.angle = angle_; }
	void SetScale(const ci::Vec3f &scale_) { transform.scale = scale_; }
	void SetMatrix(const ci::Matrix44f &matrix_) { matrix = matrix_; }
	void SetIsStop(const bool &is_stop_) { is_stop = is_stop_; }

	void UpdateMatrix()
	{
		ci::Matrix44f mtranslate = ci::Matrix44f::createTranslation(transform.pos);
		ci::Matrix44f mrotate = ci::Matrix44f::createRotation(transform.angle);
		ci::Matrix44f mscale = ci::Matrix44f::createScale(transform.scale);

		matrix = mtranslate * mrotate * mscale;
	}

	virtual void Setup() {};
	virtual void Setup(const ci::JsonTree &params) {}
	virtual void Update() {};
	virtual void Draw() {};

protected:

	Transform transform;
	ci::Matrix44f matrix;
	bool is_stop;
};