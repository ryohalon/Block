#pragma once
namespace cinder
{
	template<typename T>
	class Vec3;
	typedef Vec3<float>		Vec3f;
}
namespace ci = cinder;

namespace Collision
{
	// Cube : Cube
	bool IsHitCubeToCube(const ci::Vec3f& pos1,
		const ci::Vec3f& size1,
		const ci::Vec3f& pos2,
		const ci::Vec3f& size2);

	// sphere : sphere
	bool IsHitSphereToSphere(const ci::Vec3f &pos1,
		const float &radius1,
		const ci::Vec3f &pos2,
		const float &radius2);
}