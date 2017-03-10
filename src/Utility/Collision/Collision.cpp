#include "Collision.h"
#include <cinder/Vector.h>

namespace Collision
{
	bool IsHitCubeToCube(const ci::Vec3f & pos1, const ci::Vec3f & size1, const ci::Vec3f & pos2, const ci::Vec3f & size2)
	{
		return ((pos1.x + size1.x / 2 >= pos2.x - size2.x / 2) &&
			(pos1.x - size1.x / 2 <= pos2.x + size2.x / 2) &&
			(pos1.y + size1.y / 2 >= pos2.y - size2.y / 2) &&
			(pos1.y - size1.y / 2 <= pos2.y + size2.y / 2) &&
			(pos1.z + size1.z / 2 >= pos2.z - size2.z / 2) &&
			(pos1.z - size1.z / 2 <= pos2.z + size2.z / 2));
	}

	bool IsHitSphereToSphere(const ci::Vec3f &pos1,
		const float &radius1,
		const ci::Vec3f &pos2,
		const float &radius2)
	{
		float x = (pos2.x - pos1.x) * (pos2.x - pos1.x);
		float y = (pos2.y - pos1.y) * (pos2.y - pos1.y);
		float z = (pos2.z - pos1.z) * (pos2.z - pos1.z);
		float total = x + y + z;

		float r = (radius1 + radius2) * (radius1 + radius2);

		return total <= r;
	}
}
