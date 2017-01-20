#pragma once
#include "../CubeBase.h"



class ShrinkCube : public CubeBase
{
public:

	ShrinkCube();
	~ShrinkCube();

	bool GetIsShrink() const { return is_shrink; }
	bool GetIsShrinking() const { return is_shrinking; }
	void SetIsShrink(const bool &is_shrink_) { is_shrink = is_shrink_; }
	void SetShrinkValue(const ci::Vec3f &shrink_value_) { shrink_value = shrink_value_; }
	void SetOriginScale(const ci::Vec3f &origin_scale_) { origin_scale = origin_scale_; }

	void AlreadyShrink();
	void ShrinkStart();

	void Setup() override;
	void Update() override;
	
private:

	void Shrinking();

	bool is_shrink;
	bool is_shrinking;
	ci::Vec3f shrink_value;
	ci::Vec3f origin_pos;
	ci::Vec3f origin_scale;
	ci::Vec3f start_shrinking_scale;
	ci::Vec3f end_shrinking_scale;
	float time, take_time;
};