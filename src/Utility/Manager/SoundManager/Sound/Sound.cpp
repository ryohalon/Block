#include "Sound.h"

Sound::Sound() :
	sound(nullptr),
	is_loop(false)
{
	gain->setValue(1.0f);
}

Sound::Sound(const ci::audio::SamplePlayerNodeRef &node, ci::audio::Context * context)
{
	gain = context->makeNode(new ci::audio::GainNode());

	sound = node;
	gain->setValue(1.0f);
	sound >> gain >> context->getOutput();
}

Sound::~Sound()
{

}

void Sound::ChangeGain(const float &gain, ci::audio::Context *context)
{
	this->gain->setValue(std::max(gain, 0.0f));

	sound >> this->gain >> context->getOutput();
}

void Sound::Play()
{
	sound->start();
}

void Sound::Stop()
{
	if (sound->isEnabled())
		sound->stop();
}

void Sound::Loop()
{
	if (is_loop != true)
		return;

	if (!sound->isEnabled())
		sound->start();
}
