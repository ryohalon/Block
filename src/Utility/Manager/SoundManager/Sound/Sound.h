#pragma once
#include "cinder/audio/Context.h"
#include "cinder/audio/GainNode.h"
#include "cinder/audio/SamplePlayerNode.h"




class Sound
{
public:

	Sound();
	Sound(const ci::audio::SamplePlayerNodeRef &node, ci::audio::Context *context);
	~Sound();

	bool GetIsLoop() const { return is_loop; }
	void SetIsLoop(const bool &is_loop_) { is_loop = is_loop_; }
	ci::audio::SamplePlayerNodeRef GetSound() const { return sound; }

	void ChangeGain(const float &gain, ci::audio::Context *context);
	void Play();
	void Stop();
	void Loop();

private:

	ci::audio::SamplePlayerNodeRef sound;
	ci::audio::GainNodeRef gain;
	bool is_loop;

};