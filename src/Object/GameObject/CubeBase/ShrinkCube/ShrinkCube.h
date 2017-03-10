#pragma once
#include "../CubeBase.h"



class ShrinkCube : public CubeBase
{
public:

	enum class ShrinkDirection
	{
		UP,
		FRONT,
		LEFT,
		BACK,
		RIGHT,
		UNDER
	};

	ShrinkCube();
	ShrinkCube(const CubeBase &cube_base,
		const bool &is_shrink,
		const ci::Vec3f &shrink_value,
		const float &take_time);
	~ShrinkCube();

	bool GetIsShrink() const { return is_shrink; }
	bool GetIsShrinking() const { return is_shrinking; }
	void SetIsShrink(const bool &is_shrink_) { is_shrink = is_shrink_; }
	ShrinkDirection GetShrinkDirection() const { return shrink_direction; }
	ci::Vec3f GetShrinkValue() const { return shrink_value; }
	void SetShrinkValue(const ci::Vec3f &shrink_value_) { shrink_value = shrink_value_; }
	ci::Vec3f GetOriginPos() const { return origin_pos; }
	void SetOriginPos(const ci::Vec3f &origin_pos_) { origin_pos = origin_pos_; }
	void SetOriginScale(const ci::Vec3f &origin_scale_) { origin_scale = origin_scale_; }

	void Setup() override;
	void Update() override;
	void Draw() override;
	
	void AlreadyShrink();
	void Clicked() override;

private:

	void ShrinkStart();
	void Shrinking();

	bool is_shrink;
	bool is_shrinking;
	ShrinkDirection shrink_direction;
	ci::Vec3f shrink_value;
	ci::Vec3f origin_pos;
	ci::Vec3f origin_scale;
	ci::Vec3f start_shrinking_scale;
	ci::Vec3f end_shrinking_scale;
	float time, take_time;
};