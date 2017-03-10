#pragma once
#include "../CubeBase.h"


class VanishCube : public CubeBase
{
public:

	VanishCube();
	VanishCube(const CubeBase &cube_base,
		const bool &is_vanish);
	~VanishCube();

	bool GetIsVanish() const { return is_vanish; }
	void SetIsVanish(const bool &is_vanish_) { is_vanish = is_vanish_; }

	void Setup() override;
	void Update() override;
	void Draw() override;

	void Clicked() override;

private:

	bool is_vanish;
};