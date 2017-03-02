#pragma once
#include "../CubeBase.h"


class VanishCube : public CubeBase
{
public:

	VanishCube();
	VanishCube(const ci::Vec3f &pos,
		const ci::Vec3f &angle,
		const ci::Vec3f &scale,
		const ci::gl::Material &material,
		const CubeType &type,
		const ci::Vec3i &map_pos,
		const bool &is_vanish);
	~VanishCube();

	bool GetIsVanish() const { return is_vanish; }
	void SetIsVanish(const bool &is_vanish_) { is_vanish = is_vanish_; }
	void ChangeVanish() { is_vanish = !is_vanish; }

	void Setup() override;
	void Update() override;
	void Draw() override;

	void Clicked();

private:

	bool is_vanish;
};