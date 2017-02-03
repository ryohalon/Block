#pragma once
#include "cinder/Easing.h"
#include "cinder/Vector.h"



namespace Easing
{
	static float Linear(float t, float b, float e) {
		return (e - b) * t + b;
	}

	static float BackIn(float t, float b, float e) {
		float s = 1.70158f;
		return (e - b) * t * t * ((s + 1) * t - s) + b;
	}

	static float BackOut(float t, float b, float e) {
		float s = 1.70158f;
		t -= 1.0;
		return (e - b) * (t * t * ((s + 1) * t + s) + 1) + b;
	}

	static float BackInOut(float t, float b, float e) {
		float s = 1.70158f * 1.525f;
		if ((t /= 0.5) < 1) return (e - b) / 2 * (t * t * ((s + 1) * t - s)) + b;
		t -= 2;
		return (e - b) / 2 * (t * t * ((s + 1) * t + s) + 2) + b;
	}

	static float BounceOut(float t, float b, float e) {
		if (t < (1 / 2.75f)) {
			return (e - b) * (7.5625f * t * t) + b;
		}
		else if (t < (2 / 2.75f)) {
			t -= (1.5f / 2.75f);
			return (e - b) * (7.5625f * t * t + 0.75f) + b;
		}
		else if (t < (2.5 / 2.75)) {
			t -= (2.25f / 2.75f);
			return (e - b) * (7.5625f * t * t + 0.9375f) + b;
		}
		else {
			t -= (2.625f / 2.75f);
			return (e - b) * (7.5625f * t * t + 0.984375f) + b;
		}
	}

	static float BounceIn(float t, float b, float e) {
		return (e - b) - BounceOut(1.0f - t, 0.f, e - b) + b;
	}

	static float BounceInOut(float t, float b, float e) {
		if (t < 0.5f) return BounceIn(t * 2.f, 0.f, e - b) * 0.5f + b;
		else         return BounceOut(t * 2.f - 1.0f, 0.f, e - b) * 0.5f + (e - b) * 0.5f + b;
	}

	static float CircIn(float t, float b, float e) {
		return -(e - b) * (std::sqrt(1 - t * t) - 1) + b;
	}

	static float CircOut(float t, float b, float e) {
		t -= 1.0;
		return (e - b) * std::sqrt(1 - t * t) + b;
	}

	static float CircInOut(float t, float b, float e) {
		if ((t /= 0.5) < 1) return -(e - b) / 2 * (std::sqrt(1 - t * t) - 1) + b;
		t -= 2;
		return (e - b) / 2 * (std::sqrt(1 - t * t) + 1) + b;
	}

	static float CubicIn(float t, float b, float e) {
		return (e - b) * t * t * t + b;
	}

	static float CubicOut(float t, float b, float e) {
		t -= 1.0;
		return (e - b) * (t * t * t + 1) + b;
	}

	static float CubicInOut(float t, float b, float e) {
		if ((t /= 0.5) < 1) return (e - b) / 2 * t * t * t + b;
		t -= 2;
		return (e - b) / 2 * (t * t * t + 2) + b;
	}

	static float ElasticIn(float t, float b, float e) {
		if (t == 0) return b;
		if (t == 1) return e;

		float p = 0.3f;
		float a = e - b;
		float s = p / 4.f;
		t -= 1.f;
		return -(a * std::pow(2.f, 10.f * t) * std::sin((t - s) * (2.f * float(M_PI)) / p)) + b;
	}

	static float ElasticOut(float t, float b, float e) {
		if (t == 0) return b;
		if (t == 1) return e;

		float p = 0.3f;
		float a = e - b;
		float s = p / 4.f;
		return (a * std::pow(2.f, -10.f * t) * std::sin((t - s) * (2.f * float(M_PI)) / p) + a + b);
	}

	static float ElasticInOut(float t, float b, float e) {
		if (t == 0) return b;
		if ((t /= 0.5) == 2) return e;

		float p = 0.3f * 1.5f;
		float a = e - b;
		float s = p / 4.f;
		if (t < 1.f) {
			t -= 1.f;
			return -0.5f * (a * std::pow(2.f, 10.f * t) * std::sin((t - s) * (2.f * float(M_PI)) / p)) + b;
		}
		t -= 1;
		return a * std::pow(2.f, -10.f * t) * std::sin((t - s) * (2.f * float(M_PI)) / p) * 0.5f + a + b;
	}

	static float ExpoIn(float t, float b, float e) {
		return (t == 0) ? b : (e - b) * std::pow(2.f, 10.f * (t - 1.f)) + b;
	}

	static float ExpoOut(float t, float b, float e) {
		return (t == 1.f) ? e : (e - b) * (-std::pow(2.f, -10.f * t) + 1.f) + b;
	}

	static float ExpoInOut(float t, float b, float e) {
		if (t == 0) return b;
		if (t == 1) return e;
		if ((t /= 0.5f) < 1) return (e - b) / 2.f * std::pow(2.f, 10.f * (t - 1.f)) + b;
		return (e - b) / 2.f * (-std::pow(2.f, -10.f* --t) + 2.f) + b;
	}

	static float QuadIn(float t, float b, float e) {
		return (e - b) * t * t + b;
	}

	static float QuadOut(float t, float b, float e) {
		return -(e - b) * t * (t - 2) + b;
	}

	static float QuadInOut(float t, float b, float e) {
		if ((t /= 0.5) < 1) return (e - b) / 2 * t * t + b;
		--t;
		return -(e - b) / 2 * (t * (t - 2) - 1) + b;
	}

	static float QuartIn(float t, float b, float e) {
		return (e - b) * t * t * t * t + b;
	}

	static float QuartOut(float t, float b, float e) {
		t -= 1.0;
		return -(e - b) * (t * t * t * t - 1) + b;
	}

	static float QuartInOut(float t, float b, float e) {
		if ((t /= 0.5) < 1) return (e - b) / 2 * t * t * t * t + b;
		t -= 2;
		return -(e - b) / 2 * (t * t * t * t - 2) + b;
	}

	static float QuintIn(float t, float b, float e) {
		return (e - b) * t * t * t * t * t + b;
	}

	static float QuintOut(float t, float b, float e) {
		t -= 1.0;
		return (e - b) * (t * t * t * t * t + 1) + b;
	}

	static float QuintInOut(float t, float b, float e) {
		if ((t /= 0.5) < 1) return (e - b) / 2 * t * t * t * t * t + b;
		t -= 2;
		return (e - b) / 2 * (t * t * t * t * t + 2) + b;
	}

	static float SineIn(float t, float b, float e) {
		return -(e - b) * std::cos(t * (float(M_PI) / 2.f)) + (e - b) + b;
	}

	static float SineOut(float t, float b, float e) {
		return (e - b) * std::sin(t * (float(M_PI) / 2.f)) + b;
	}

	static float SineInOut(float t, float b, float e) {
		return -(e - b) / 2.f * (std::cos(float(M_PI) * t) - 1.f) + b;
	}
};